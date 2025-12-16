// System includes first (before C++ headers to avoid conflicts)
#include <sys/wait.h>
#include <signal.h>
#ifdef __linux__
#include <pthread.h>
#endif

// local includes
#include "shared_trace.h"
#include "types.hh"
#include "loss.hh"
#include "graph.hh"
#include "settings.hh"
#include "knowledge.hh"
#include "fuzzer.hh"
#include "tui.hh"
#include "seed.hh"

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
#include <fstream>
#include <final/final.h>

// Global flag to stop fuzzing threads
std::atomic<bool> g_should_stop_fuzzing{false};

// Global execution counter (accessed from fuzzer.cc)
std::atomic<u32> g_total_executions{0};

// Global crash counter (accessed from fuzzer.cc)
std::atomic<u32> g_crash_count{0};

int main(int argc, char* argv[])
{
    // Declare knowledge_ptr
    FuzzerKnowledge* knowledge_ptr = nullptr;
    
    Settings settings(argc, argv);
    
    // Try to load existing knowledge checkpoint
    std::string checkpoint_path = settings.work_dir + "/knowledge_checkpoint.knowledge";
    
    // Check if checkpoint file exists before trying to load
    std::ifstream checkpoint_check(checkpoint_path, std::ios::binary);
    bool checkpoint_exists = checkpoint_check.good();
    checkpoint_check.close();
    
    if (checkpoint_exists) {
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
    } else {
        // No checkpoint found, create new
        knowledge_ptr = new FuzzerKnowledge(settings);
    }
    
    FuzzerKnowledge& knowledge = *knowledge_ptr;
    
    // Load seed inputs if seed path is provided
    if (!settings.seed_path.empty()) {
        std::cout << "[*] Loading seeds from: " << settings.seed_path << std::endl;
        u32 seeds_loaded = LoadSeedsFromDirectory(settings.seed_path, knowledge, settings);
        std::cout << "[*] Loaded " << seeds_loaded << " seed inputs into history" << std::endl;
    }
        
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
        
        // Create TUI window - reads directly from knowledge when timer fires
        // Use a separate scope to ensure TUI is destroyed before app
        {
            FuzzerTUI tui_window{&app, knowledge, settings};
            tui_window.show();
            
            // Spawn fuzzer threads
            // Store fuzzer instances so we can kill their child processes
            std::vector<std::thread> fuzzer_threads;
            std::vector<FuzzerThread*> fuzzer_instances(settings.thread_count, nullptr);
            
            for (u32 i = 0; i < settings.thread_count; ++i) {
                fuzzer_threads.emplace_back([&knowledge, i, &fuzzer_instances]() {
                    FuzzerThread fuzzer(knowledge, i);
                    fuzzer_instances[i] = &fuzzer;
                    
                    // Run initialization
                    fuzzer.InitializationRun();
                    
                    // Main fuzzing loop - Run() checks g_should_stop_fuzzing
                    fuzzer.Run();
                    
                    fuzzer_instances[i] = nullptr;
                });
            }
            
            // Run finalcut event loop in main thread
            // TUI timer will call RefreshDisplay() which reads directly from knowledge
            app.exec();
            
            // Signal threads to stop
            g_should_stop_fuzzing = true;
            
            // Immediately kill all child processes that threads might be waiting on
            // This allows threads to exit waitpid() quickly
            for (FuzzerThread* fuzzer : fuzzer_instances) {
                if (fuzzer) {
                    pid_t child_pid = fuzzer->current_child_pid.load();
                    if (child_pid > 0) {
                        kill(child_pid, SIGKILL);
                        waitpid(child_pid, NULL, 0);  // Clean up zombie
                    }
                }
            }
            
            // Forcefully terminate threads immediately (Linux only)
            // On Linux, we can use pthread_cancel to forcefully stop threads
            // This interrupts blocking calls and causes threads to exit
            for (size_t i = 0; i < fuzzer_threads.size(); ++i) {
                auto& t = fuzzer_threads[i];
                if (t.joinable()) {
#ifdef __linux__
                    // Cancel the thread forcefully - this will interrupt blocking calls
                    pthread_t native = t.native_handle();
                    pthread_cancel(native);
#endif
                }
            }
            
            // Now join all threads (they should exit quickly after cancellation)
            for (auto& t : fuzzer_threads) {
                if (t.joinable()) {
                    t.join();
                }
            }
            
            // Clear thread vector (threads are already joined)
            fuzzer_threads.clear();
            
            // Note: TUI is already closed (when Escape was pressed, close() was called)
            // and app.exec() has returned, so we don't need to close/quit again
            
            // Cleanup knowledge BEFORE destroying TUI to avoid issues
            // CRITICAL: We must ensure NO threads are holding mutex locks when we delete knowledge
            // Mutex destructors will throw if the mutex is locked, causing std::terminate()
            if (knowledge_ptr) {
                // Try to acquire both mutexes to ensure they're not locked
                // This will block if a thread still has them, but threads should have exited by now
                // Use try_lock to avoid blocking forever if something is wrong
                bool knowledge_locked = false;
                bool graph_locked = false;
                
                // Try to lock knowledge mutex (non-blocking)
                knowledge_locked = knowledge_ptr->knowledge_mutex.try_lock();
                if (knowledge_locked) {
                    knowledge_ptr->knowledge_mutex.unlock();
                }
                
                // Try to lock graph mutex (non-blocking)
                graph_locked = knowledge_ptr->graph.graph_mutex.try_lock();
                if (graph_locked) {
                    knowledge_ptr->graph.graph_mutex.unlock();
                }
                
                // Verify both mutexes are unlocked before deletion
                // If either is still locked, threads haven't finished (shouldn't happen after join)
                // Mutex destructors will throw if locked, causing std::terminate()
                if (!knowledge_locked || !graph_locked) {
                    std::cerr << "[!] Warning: Mutexes still locked after threads joined. "
                              << "This should not happen. Proceeding anyway..." << std::endl;
                }
                
                // Delete knowledge - mutexes should be unlocked
                // If they're still locked, the destructor will throw
                delete knowledge_ptr;
                knowledge_ptr = nullptr;
            }
            
            // TUI will be destroyed here when it goes out of scope
            // It's already been closed, so the destructor should be safe
        }
        
        // App will be destroyed here when it goes out of scope
        // All cleanup is complete, so destructors should run safely
        
        return 0;
}
