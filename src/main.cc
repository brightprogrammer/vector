// local includes
#include "shared_trace.h"
#include "types.hh"
#include "loss.hh"
#include "graph.hh"
#include "settings.hh"
#include "knowledge.hh"
#include "fuzzer.hh"
#include "tui.hh"

// stdc++
#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <atomic>
#include <functional>
#include <cstring>
#include <chrono>
#include <vector>
#include <csignal>
#include <memory>
#include <mutex>
#include <final/final.h>

// Global flag to stop fuzzing threads
std::atomic<bool> g_should_stop_fuzzing{false};

// Global execution counter (accessed from fuzzer.cc)
std::atomic<u32> g_total_executions{0};

// Global crash counter (accessed from fuzzer.cc)
std::atomic<u32> g_crash_count{0};

// Forward declaration
struct ThreadStats;


// Thread-safe stats structure (simplified for console output)
struct ThreadStats {
    std::mutex mutex;
    u32 executions{0};
    u32 crashes{0};
    u32 unique_traces{0};
    std::string status{"Stopped"};
    std::string error_message{""};
    FuzzInput current_input;  // Current input being tested by this thread
    
    void Update(u32 execs, u32 crs, u32 traces, const std::string& st) {
        std::lock_guard<std::mutex> lock(mutex);
        executions = execs;
        crashes = crs;
        unique_traces = traces;
        status = st;
    }
    
    void UpdateInput(const FuzzInput& input) {
        std::lock_guard<std::mutex> lock(mutex);
        current_input = input;
    }
    
    FuzzInput GetInput() {
        std::lock_guard<std::mutex> lock(mutex);
        return current_input;
    }
    
    void Get(u32& execs, u32& crs, u32& traces, std::string& st, std::string& err) {
        std::lock_guard<std::mutex> lock(mutex);
        execs = executions;
        crs = crashes;
        traces = unique_traces;
        st = status;
        err = error_message;
    }
};

int main(int argc, char* argv[])
{
    try {
        Settings settings(argc, argv);
        
        // Try to load existing knowledge checkpoint
        FuzzerKnowledge* knowledge_ptr = nullptr;
        std::string checkpoint_path = settings.work_dir + "/knowledge_checkpoint.knowledge";
        
        try {
            // DeserializeKnowledge uses output parameter to avoid copying mutexes
            FuzzerKnowledge loaded_knowledge(settings);
            DeserializeKnowledge(checkpoint_path, loaded_knowledge);
            // Use loaded knowledge if settings match
            if (loaded_knowledge.settings.target_program == settings.target_program) {
                // Create new knowledge with current settings
                knowledge_ptr = new FuzzerKnowledge(settings);
                // Manually copy history and graph (mutexes will be newly initialized)
                knowledge_ptr->history = loaded_knowledge.history;
                knowledge_ptr->history_index = loaded_knowledge.history_index;
                knowledge_ptr->graph.CopyGraphData(loaded_knowledge.graph);
            } else {
                // Settings don't match, create new
                knowledge_ptr = new FuzzerKnowledge(settings);
            }
        } catch (...) {
            // No checkpoint found or error loading, create new
            knowledge_ptr = new FuzzerKnowledge(settings);
        }
        
        FuzzerKnowledge& knowledge = *knowledge_ptr;
        
        // Initialize thread stats
        std::vector<std::unique_ptr<ThreadStats>> thread_stats;
        thread_stats.reserve(settings.thread_count);
        for (u32 i = 0; i < settings.thread_count; ++i) {
            thread_stats.push_back(std::make_unique<ThreadStats>());
        }
        
        // Initialize TUI data structure
        TUIData tui_data;
        
        // Reset stop flag
        g_should_stop_fuzzing = false;
        
        // Set up signal handler for graceful shutdown
        std::signal(SIGINT, [](int) {
            g_should_stop_fuzzing = true;
        });
        std::signal(SIGTERM, [](int) {
            g_should_stop_fuzzing = true;
        });
        
        // Initialize finalcut application
        finalcut::FApplication app{argc, argv};
        
        // Create TUI window
        FuzzerTUI tui_window{&app, tui_data, settings};
        tui_window.show();
        
        // Spawn fuzzer threads
        std::vector<std::thread> fuzzer_threads;
        for (u32 i = 0; i < settings.thread_count; ++i) {
            fuzzer_threads.emplace_back([&knowledge, i, &thread_stats, &tui_data]() {
                auto& stats = *thread_stats[i];
                u32 local_executions = 0;
                u32 local_crashes = 0;
                
                try {
                    stats.Update(local_executions, local_crashes, 0, "Initializing");
                    tui_data.UpdateThread(i, local_executions, local_crashes, "Initializing", 0);
                    
                    FuzzerThread fuzzer(knowledge, i, stats);
                    
                    // Run initialization (this will update thread_stats internally)
                    fuzzer.InitializationRun();
                    // Get the actual execution count from thread_stats (InitializationRun updates it)
                    u32 actual_execs, actual_crashes, actual_traces;
                    std::string actual_status, actual_err;
                    stats.Get(actual_execs, actual_crashes, actual_traces, actual_status, actual_err);
                    stats.Update(actual_execs, actual_crashes, actual_traces, "Running");
                    tui_data.UpdateThread(i, actual_execs, actual_crashes, "Running", fuzzer.thread_input_size);
                    
                    // Main fuzzing loop - Run() checks g_should_stop_fuzzing
                    fuzzer.Run();
                    
                    stats.Update(local_executions, local_crashes, 0, "Stopped");
                    tui_data.UpdateThread(i, local_executions, local_crashes, "Stopped", fuzzer.thread_input_size);
                } catch (const std::exception& e) {
                    std::cerr << "[!] Thread " << i << " error: " << e.what() << std::endl;
                    stats.Update(local_executions, local_crashes, 0, "Error");
                    tui_data.UpdateThread(i, local_executions, local_crashes, "Error", 0);
                } catch (...) {
                    std::cerr << "[!] Thread " << i << " unknown error" << std::endl;
                    stats.Update(local_executions, local_crashes, 0, "Error");
                    tui_data.UpdateThread(i, local_executions, local_crashes, "Error", 0);
                }
            });
        }
        
        // TUI update thread
        std::thread tui_update_thread([&knowledge, &tui_data, &tui_window, &settings, &app, &thread_stats]() {
            u32 last_history_size = 0;
            while (!g_should_stop_fuzzing.load() && tui_window.isRunning()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(settings.ui_update_freq));
                
                // Update overall statistics
                std::vector<FuzzExecution> history_snapshot = knowledge.GetHistorySnapshot();
                u32 current_history_size = 0;
                u32 latest_idx = 0;
                u32 graph_nodes = 0;
                u32 graph_edges = 0;
                
                for (u32 i = 0; i < history_snapshot.size(); ++i) {
                    if (!history_snapshot[i].trace.empty()) {
                        current_history_size++;
                        latest_idx = i;
                    }
                }
                
                // Calculate graph stats
                {
                    std::lock_guard<std::mutex> lock(knowledge.knowledge_mutex);
                    graph_nodes = knowledge.graph.graph.size();
                    for (const auto& entry : knowledge.graph.graph) {
                        graph_edges += entry.second.size();
                    }
                }
                
                // Update TUI data
                tui_data.UpdateOverall(
                    g_total_executions.load(),
                    g_crash_count.load(),
                    current_history_size,
                    graph_nodes,
                    graph_edges
                );
                
                // Update thread info with current inputs
                for (u32 i = 0; i < thread_stats.size(); ++i) {
                    FuzzInput current_input = thread_stats[i]->GetInput();
                    std::vector<u8> first_bytes, last_bytes;
                    
                    // Extract first 8 bytes
                    if (current_input.size() > 0) {
                        u32 first_count = std::min((u32)8, (u32)current_input.size());
                        first_bytes.assign(current_input.begin(), current_input.begin() + first_count);
                    }
                    
                    // Extract last 8 bytes
                    if (current_input.size() > 0) {
                        u32 last_count = std::min((u32)8, (u32)current_input.size());
                        u32 start_idx = current_input.size() > last_count ? current_input.size() - last_count : 0;
                        last_bytes.assign(current_input.begin() + start_idx, current_input.end());
                    }
                    
                    // Get current stats
                    u32 execs, crashes, traces;
                    std::string status, err;
                    thread_stats[i]->Get(execs, crashes, traces, status, err);
                    
                    // Get thread input size from knowledge (we'll need to track this differently)
                    // For now, use input size from current_input
                    u32 input_size = current_input.size();
                    tui_data.UpdateThread(i, execs, crashes, status, input_size, first_bytes, last_bytes);
                }
                
                if (current_history_size > last_history_size) {
                    // New execution added
                    const FuzzExecution& latest = history_snapshot[latest_idx];
                    // Compute trace hash for display
                    u32 trace_hash = 0;
                    for (u32 addr : latest.trace) {
                        trace_hash ^= addr;
                        trace_hash = (trace_hash << 1) | (trace_hash >> 31);  // Rotate left
                    }
                    tui_data.UpdateLatest(trace_hash, latest.trace.size(), latest.input.size());
                    last_history_size = current_history_size;
                }
                
                // Don't call RefreshDisplay from background thread - it's called from timer in main thread
            }
        });
        
        // Run finalcut event loop in main thread
        app.exec();
        
        // Signal threads to stop
        g_should_stop_fuzzing = true;
        
        // Wait for threads to finish
        for (auto& t : fuzzer_threads) {
            if (t.joinable()) {
                t.join();
            }
        }
        
        // Wait for TUI update thread
        if (tui_update_thread.joinable()) {
            tui_update_thread.join();
        }
        
        // Cleanup
        delete knowledge_ptr;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
