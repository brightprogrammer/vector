// local includes
#include "shared_trace.h"
#include "types.hh"
#include "loss.hh"
#include "graph.hh"
#include "settings.hh"
#include "knowledge.hh"
#include "fuzzer.hh"

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

// Global flag to stop fuzzing threads
std::atomic<bool> g_should_stop_fuzzing{false};

// Global execution counter (accessed from fuzzer.cc)
std::atomic<u32> g_total_executions{0};

// Global crash counter (accessed from fuzzer.cc)
std::atomic<u32> g_crash_count{0};

// Forward declaration
struct ThreadStats;

// Simple hash function for ExecTrace (for display purposes)
static u32 ComputeTraceHash(const ExecTrace& trace) {
    u32 hash = 0;
    for (u32 addr : trace) {
        hash ^= addr;
        hash = (hash << 1) | (hash >> 31);  // Rotate left
    }
    return hash;
}

// Print summary when new execution is added
static void PrintKnowledgeUpdate(const FuzzerKnowledge& knowledge, const FuzzExecution& execution) {
    u32 trace_hash = ComputeTraceHash(execution.trace);
    u32 graph_nodes = knowledge.graph.graph.size();
    u32 graph_edges = 0;
    for (const auto& entry : knowledge.graph.graph) {
        graph_edges += entry.second.size();
    }
    
    // Count unique traces in history
    u32 unique_traces = 0;
    for (const auto& exec : knowledge.history) {
        if (!exec.trace.empty()) {
            unique_traces++;
        }
    }
    
    std::cout << "[+] New execution added:" << std::endl;
    std::cout << "    Trace hash: 0x" << std::hex << std::setw(8) << std::setfill('0') << trace_hash << std::dec << std::endl;
    std::cout << "    Trace length: " << execution.trace.size() << " basic blocks" << std::endl;
    std::cout << "    Input size: " << execution.input.size() << " bytes" << std::endl;
    std::cout << "    Graph nodes: " << graph_nodes << std::endl;
    std::cout << "    Graph edges: " << graph_edges << std::endl;
    std::cout << "    Unique traces: " << unique_traces << std::endl;
    std::cout << "    Total executions: " << g_total_executions.load() << std::endl;
    std::cout << "    Crashes found: " << g_crash_count.load() << std::endl;
    std::cout << std::endl;
}

// Thread-safe stats structure (simplified for console output)
struct ThreadStats {
    std::mutex mutex;
    u32 executions{0};
    u32 crashes{0};
    u32 unique_traces{0};
    std::string status{"Stopped"};
    std::string error_message{""};
    
    void Update(u32 execs, u32 crs, u32 traces, const std::string& st) {
        std::lock_guard<std::mutex> lock(mutex);
        executions = execs;
        crashes = crs;
        unique_traces = traces;
        status = st;
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
        
        std::cout << "Vector: Directional Fuzzing Framework" << std::endl;
        std::cout << "=====================================" << std::endl;
        std::cout << "Target: " << settings.target_program << std::endl;
        std::cout << "Threads: " << settings.thread_count << std::endl;
        std::cout << "Work directory: " << settings.work_dir << std::endl;
        std::cout << std::endl;
        
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
                std::cout << "[*] Loaded existing knowledge checkpoint" << std::endl;
                std::cout << "    Unique traces: " << loaded_knowledge.history.size() << std::endl;
                std::cout << std::endl;
            } else {
                // Settings don't match, create new
                knowledge_ptr = new FuzzerKnowledge(settings);
                std::cout << "[*] Created new knowledge (settings mismatch)" << std::endl;
            }
        } catch (...) {
            // No checkpoint found or error loading, create new
            knowledge_ptr = new FuzzerKnowledge(settings);
            std::cout << "[*] Created new knowledge" << std::endl;
        }
        
        FuzzerKnowledge& knowledge = *knowledge_ptr;
        
        // Hook into AddExecutionIfDifferent to print updates
        // We'll modify knowledge.cc to call a callback, or we can check periodically
        // For now, let's add a wrapper or modify the approach
        
        // Initialize thread stats
        std::vector<std::unique_ptr<ThreadStats>> thread_stats;
        thread_stats.reserve(settings.thread_count);
        for (u32 i = 0; i < settings.thread_count; ++i) {
            thread_stats.push_back(std::make_unique<ThreadStats>());
        }
        
        // Reset stop flag
        g_should_stop_fuzzing = false;
        
        // Set up signal handler for graceful shutdown
        std::signal(SIGINT, [](int) {
            std::cout << std::endl << "[*] Received SIGINT, stopping fuzzer..." << std::endl;
            g_should_stop_fuzzing = true;
        });
        std::signal(SIGTERM, [](int) {
            std::cout << std::endl << "[*] Received SIGTERM, stopping fuzzer..." << std::endl;
            g_should_stop_fuzzing = true;
        });
        
        std::cout << "[*] Starting fuzzer threads..." << std::endl;
        std::cout << std::endl;
        
        // Spawn fuzzer threads
        std::vector<std::thread> fuzzer_threads;
        for (u32 i = 0; i < settings.thread_count; ++i) {
            fuzzer_threads.emplace_back([&knowledge, i, &thread_stats]() {
                auto& stats = *thread_stats[i];
                u32 local_executions = 0;
                u32 local_crashes = 0;
                u32 local_unique_traces = 0;
                
                try {
                    stats.Update(local_executions, local_crashes, local_unique_traces, "Initializing");
                    
                    FuzzerThread fuzzer(knowledge, i, stats);
                    
                    // Run initialization
                    fuzzer.InitializationRun();
                    local_executions += 2;
                    stats.Update(local_executions, local_crashes, local_unique_traces, "Running");
                    
                    // Main fuzzing loop - Run() checks g_should_stop_fuzzing
                    fuzzer.Run();
                    
                    stats.Update(local_executions, local_crashes, local_unique_traces, "Stopped");
                } catch (const std::exception& e) {
                    std::cerr << "[!] Thread " << i << " error: " << e.what() << std::endl;
                    stats.Update(local_executions, local_crashes, local_unique_traces, "Error");
                } catch (...) {
                    std::cerr << "[!] Thread " << i << " unknown error" << std::endl;
                    stats.Update(local_executions, local_crashes, local_unique_traces, "Error");
                }
            });
        }
        
        // Monitor knowledge updates and print summaries
        u32 last_history_size = 0;
        while (!g_should_stop_fuzzing.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
            // Check if new executions were added
            // Thread-safe: use snapshot
            std::vector<FuzzExecution> history_snapshot = knowledge.GetHistorySnapshot();
            u32 current_history_size = 0;
            u32 latest_idx = 0;
            for (u32 i = 0; i < history_snapshot.size(); ++i) {
                if (!history_snapshot[i].trace.empty()) {
                    current_history_size++;
                    latest_idx = i;
                }
            }
            
            if (current_history_size > last_history_size) {
                // New execution added - print summary
                const FuzzExecution& latest = history_snapshot[latest_idx];
                PrintKnowledgeUpdate(knowledge, latest);
                last_history_size = current_history_size;
            }
        }
        
        // Wait for threads to finish
        std::cout << "[*] Stopping fuzzer threads..." << std::endl;
        for (auto& t : fuzzer_threads) {
            if (t.joinable()) {
                t.join();
            }
        }
        
        std::cout << "[*] Fuzzing complete" << std::endl;
        
        // Cleanup
        delete knowledge_ptr;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
