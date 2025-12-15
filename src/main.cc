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
#include <final/final.h>

// Global flag to stop fuzzing threads
std::atomic<bool> g_should_stop_fuzzing{false};

// Global execution counter (accessed from fuzzer.cc)
std::atomic<u32> g_total_executions{0};

// Global crash counter (accessed from fuzzer.cc)
std::atomic<u32> g_crash_count{0};

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
        
        // Load seed inputs if seed path is provided
        if (!settings.seed_path.empty()) {
            try {
                std::cout << "[*] Loading seeds from: " << settings.seed_path << std::endl;
                u32 seeds_loaded = LoadSeedsFromDirectory(settings.seed_path, knowledge, settings);
                std::cout << "[*] Loaded " << seeds_loaded << " seed inputs into history" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "[!] Warning: Failed to load seeds: " << e.what() << std::endl;
                std::cerr << "[!] Continuing without seeds..." << std::endl;
            }
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
        FuzzerTUI tui_window{&app, knowledge, settings};
        tui_window.show();
        
        // Spawn fuzzer threads
        std::vector<std::thread> fuzzer_threads;
        for (u32 i = 0; i < settings.thread_count; ++i) {
            fuzzer_threads.emplace_back([&knowledge, i]() {
                try {
                    FuzzerThread fuzzer(knowledge, i);
                    
                    // Run initialization
                    fuzzer.InitializationRun();
                    
                    // Main fuzzing loop - Run() checks g_should_stop_fuzzing
                    fuzzer.Run();
                } catch (const std::exception& e) {
                    std::cerr << "[!] Thread " << i << " error: " << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "[!] Thread " << i << " unknown error" << std::endl;
                }
            });
        }
        
        // Run finalcut event loop in main thread
        // TUI timer will call RefreshDisplay() which reads directly from knowledge
        app.exec();
        
        // Signal threads to stop
        g_should_stop_fuzzing = true;
        
        // Wait for threads to finish
        for (auto& t : fuzzer_threads) {
            if (t.joinable()) {
                t.join();
            }
        }
        
        // Cleanup
        delete knowledge_ptr;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
