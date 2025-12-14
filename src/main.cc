// command line support
#include <CLI11.hpp>

// local includes
#include "shared_trace.h"
#include "types.hh"
#include "loss.hh"
#include "graph.hh"
#include "settings.hh"
#include "knowledge.hh"
#include "fuzzer.hh"

// finalcut TUI support
#include <final/final.h>
namespace fc = finalcut;

// stdc++
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <cstring>
#include <thread>
#include <mutex>
#include <atomic>
#include <sstream>
#include <iomanip>

using finalcut::FPoint;
using finalcut::FSize;
using finalcut::FColor;

// Global state for UI updates
struct FuzzerStats {
    std::atomic<u32> total_executions{0};
    std::atomic<u32> unique_traces{0};
    std::atomic<u32> crashes{0};
    std::atomic<u32> graph_nodes{0};
    std::atomic<bool> should_stop{false};
    std::mutex stats_mutex;
};

static FuzzerStats g_stats;

// Global flag to stop fuzzing threads
std::atomic<bool> g_should_stop_fuzzing{false};

// Global crash counter (accessed from fuzzer.cc)
std::atomic<u32> g_crash_count{0};

//----------------------------------------------------------------------
// class FuzzerDialog
//----------------------------------------------------------------------

class FuzzerDialog final : public fc::FDialog
{
public:
    // Constructor
    explicit FuzzerDialog(fc::FWidget* parent, FuzzerKnowledge& knowledge);
    
    // Destructor
    ~FuzzerDialog() override;
    
    // Update UI with current stats
    void updateStats();
    
    // Set fuzzing state
    void setFuzzing(bool running) { fuzzing = running; }
    bool isFuzzing() const { return fuzzing; }

private:
    // Methods
    void initLayout() override;
    void adjustSize() override;
    
    // Event handlers
    void onTimer(fc::FTimerEvent*) override;
    void onClose(fc::FCloseEvent*) override;
    
    // Callback methods
    void cb_start();
    void cb_stop();
    void cb_quit();
    
    // Data members
    FuzzerKnowledge& knowledge;
    bool fuzzing{false};
    std::vector<std::thread> fuzzer_threads;
    
    // UI widgets
    fc::FLabel title_label{this};
    fc::FLabel stats_label{this};
    fc::FLabel executions_label{this};
    fc::FLabel traces_label{this};
    fc::FLabel crashes_label{this};
    fc::FLabel nodes_label{this};
    fc::FLabel status_label{this};
    fc::FButton start_btn{this};
    fc::FButton stop_btn{this};
    fc::FButton quit_btn{this};
    
    // Value labels
    fc::FLabel executions_value{this};
    fc::FLabel traces_value{this};
    fc::FLabel crashes_value{this};
    fc::FLabel nodes_value{this};
    fc::FLabel status_value{this};
};

//----------------------------------------------------------------------
FuzzerDialog::FuzzerDialog(fc::FWidget* parent, FuzzerKnowledge& k)
    : fc::FDialog{parent}, knowledge(k)
{
    setText("Vector Fuzzer");
    
    // Configure labels
    title_label.setText("Vector: Directional Fuzzing Framework");
    title_label.setEmphasis();
    
    stats_label.setText("Statistics:");
    stats_label.setEmphasis();
    
    executions_label.setText("Total Executions:");
    traces_label.setText("Unique Traces:");
    crashes_label.setText("Crashes Found:");
    nodes_label.setText("Graph Nodes:");
    status_label.setText("Status:");
    
    executions_value.setText("0");
    traces_value.setText("0");
    crashes_value.setText("0");
    nodes_value.setText("0");
    status_value.setText("Stopped");
    
    // Configure buttons
    start_btn.setText("&Start");
    start_btn.setStatusbarMessage("Start fuzzing");
    
    stop_btn.setText("S&top");
    stop_btn.setStatusbarMessage("Stop fuzzing");
    stop_btn.setDisable();
    
    quit_btn.setText("&Quit");
    quit_btn.setStatusbarMessage("Exit application");
    
    // Connect callbacks
    start_btn.addCallback("clicked", this, &FuzzerDialog::cb_start);
    stop_btn.addCallback("clicked", this, &FuzzerDialog::cb_stop);
    quit_btn.addCallback("clicked", this, &FuzzerDialog::cb_quit);
}

//----------------------------------------------------------------------
FuzzerDialog::~FuzzerDialog()
{
    // Stop fuzzing if running
    if (fuzzing) {
        fuzzing = false;
        // Wait for threads to finish
        for (auto& t : fuzzer_threads) {
            if (t.joinable()) {
                t.join();
            }
        }
    }
    delOwnTimers();
}

//----------------------------------------------------------------------
void FuzzerDialog::initLayout()
{
    FDialog::setGeometry(FPoint{5, 3}, FSize{70, 20});
    
    // Title
    title_label.setGeometry(FPoint{2, 1}, FSize{66, 1});
    
    // Statistics section
    stats_label.setGeometry(FPoint{2, 3}, FSize{20, 1});
    executions_label.setGeometry(FPoint{4, 5}, FSize{20, 1});
    executions_value.setGeometry(FPoint{25, 5}, FSize{10, 1});
    traces_label.setGeometry(FPoint{4, 6}, FSize{20, 1});
    traces_value.setGeometry(FPoint{25, 6}, FSize{10, 1});
    crashes_label.setGeometry(FPoint{4, 7}, FSize{20, 1});
    crashes_value.setGeometry(FPoint{25, 7}, FSize{10, 1});
    nodes_label.setGeometry(FPoint{4, 8}, FSize{20, 1});
    nodes_value.setGeometry(FPoint{25, 8}, FSize{10, 1});
    status_label.setGeometry(FPoint{4, 10}, FSize{20, 1});
    status_value.setGeometry(FPoint{25, 10}, FSize{20, 1});
    
    // Buttons
    start_btn.setGeometry(FPoint{15, 15}, FSize{10, 1});
    stop_btn.setGeometry(FPoint{28, 15}, FSize{10, 1});
    quit_btn.setGeometry(FPoint{45, 15}, FSize{10, 1});
    
    FDialog::initLayout();
}

//----------------------------------------------------------------------
void FuzzerDialog::adjustSize()
{
    FDialog::adjustSize();
}

//----------------------------------------------------------------------
void FuzzerDialog::onTimer(fc::FTimerEvent*)
{
    updateStats();
}

//----------------------------------------------------------------------
void FuzzerDialog::onClose(fc::FCloseEvent* ev)
{
    if (fuzzing) {
        // Ask for confirmation if fuzzing is running
        fc::FMessageBox::error(this, "Please stop fuzzing before closing");
        ev->ignore();
        return;
    }
    fc::FApplication::closeConfirmationDialog(this, ev);
}

//----------------------------------------------------------------------
void FuzzerDialog::updateStats()
{
    // Count unique traces in history
    u32 unique_count = 0;
    for (const auto& exec : knowledge.history) {
        if (!exec.trace.empty()) {
            unique_count++;
        }
    }
    
    // Update graph nodes count
    u32 node_count = knowledge.graph.graph.size();
    
    // Update UI labels
    executions_value.setText(std::to_string(g_stats.total_executions.load()));
    traces_value.setText(std::to_string(unique_count));
    crashes_value.setText(std::to_string(g_crash_count.load()));
    nodes_value.setText(std::to_string(node_count));
    
    if (fuzzing) {
        status_value.setText("Running");
        status_value.setForegroundColor(FColor::Green);
    } else {
        status_value.setText("Stopped");
        status_value.setForegroundColor(FColor::Red);
    }
    
    // Redraw labels
    executions_value.redraw();
    traces_value.redraw();
    crashes_value.redraw();
    nodes_value.redraw();
    status_value.redraw();
}

//----------------------------------------------------------------------
void FuzzerDialog::cb_start()
{
    if (fuzzing) {
        return;
    }
    
    fuzzing = true;
    g_should_stop_fuzzing = false; // Reset stop flag
    start_btn.setDisable();
    stop_btn.setEnable();
    status_value.setText("Starting...");
    status_value.redraw();
    
    // Start fuzzer threads
    fuzzer_threads.clear();
    for (u32 i = 0; i < knowledge.settings.thread_count; ++i) {
        fuzzer_threads.emplace_back([this, i]() {
            try {
                FuzzerThread fuzzer(knowledge, i);
                // Run initialization
                fuzzer.InitializationRun();
                g_stats.total_executions += 2; // Initialization adds 2 executions
                
                // Main fuzzing loop - Run() checks g_should_stop_fuzzing
                fuzzer.Run();
            } catch (const std::exception& e) {
                // Thread error
                fuzzing = false; // Stop all threads on error
            }
        });
    }
    
    // Start update timer (update every 500ms)
    addTimer(500);
    
    status_value.setText("Running");
    status_value.setForegroundColor(FColor::Green);
    status_value.redraw();
}

//----------------------------------------------------------------------
void FuzzerDialog::cb_stop()
{
    if (!fuzzing) {
        return;
    }
    
    fuzzing = false;
    g_should_stop_fuzzing = true; // Signal threads to stop
    stop_btn.setDisable();
    start_btn.setEnable();
    
    // Wait for threads to finish (with timeout)
    for (auto& t : fuzzer_threads) {
        if (t.joinable()) {
            t.join();
        }
    }
    fuzzer_threads.clear();
    
    delOwnTimers();
    
    status_value.setText("Stopped");
    status_value.setForegroundColor(FColor::Red);
    status_value.redraw();
}

//----------------------------------------------------------------------
void FuzzerDialog::cb_quit()
{
    if (fuzzing) {
        cb_stop();
    }
    close();
}

//----------------------------------------------------------------------
//                               main part
//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
    try {
        Settings settings(argc, argv);
        
        // Try to load existing knowledge checkpoint
        FuzzerKnowledge* knowledge_ptr = nullptr;
        std::string checkpoint_path = settings.work_dir + "/knowledge_checkpoint.knowledge";
        
        try {
            FuzzerKnowledge loaded_knowledge = DeserializeKnowledge(checkpoint_path);
            // Use loaded knowledge if settings match
            if (loaded_knowledge.settings.target_program == settings.target_program) {
                // Update settings to match current command line
                loaded_knowledge.settings = settings;
                knowledge_ptr = new FuzzerKnowledge(loaded_knowledge.settings);
                *knowledge_ptr = loaded_knowledge;
            } else {
                // Settings don't match, create new
                knowledge_ptr = new FuzzerKnowledge(settings);
            }
        } catch (...) {
            // No checkpoint found or error loading, create new
            knowledge_ptr = new FuzzerKnowledge(settings);
        }
        
        FuzzerKnowledge& knowledge = *knowledge_ptr;
        
        // Create the application object
        fc::FApplication app{argc, argv};
        
        // Create fuzzer dialog
        FuzzerDialog dialog{&app, knowledge};
        
        // Set dialog as main widget
        fc::FWidget::setMainWidget(&dialog);
        
        // Show and start the application
        dialog.show();
        int result = app.exec();
        
        // Cleanup
        delete knowledge_ptr;
        
        return result;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
