#include "tui.hh"
#include "settings.hh"
#include <final/final.h>
#include <sstream>
#include <iomanip>
#include <exception>

FuzzerTUI::FuzzerTUI(finalcut::FWidget* parent, FuzzerKnowledge& knowledge, const Settings& settings)
    : finalcut::FDialog{parent}, knowledge(knowledge), settings(settings) {
    setText("Vector Fuzzer - Status");
    setResizeable(true);
    setMinimizable(false);
    
    // Get terminal size and make dialog fullscreen
    finalcut::FSize term_size = getParentWidget()->getTermGeometry().getSize();
    setGeometry(finalcut::FPoint{1, 1}, finalcut::FSize{term_size.getWidth(), term_size.getHeight()});
    
    // Create stats view (overall statistics)
    stats_view = new finalcut::FTextView{this};
    stats_view->setGeometry(finalcut::FPoint{2, 2}, finalcut::FSize{term_size.getWidth() - 4, term_size.getHeight() - 10});
    stats_view->unsetFocusable();
    
    // Create latest view (latest execution)
    latest_view = new finalcut::FTextView{this};
    latest_view->setGeometry(finalcut::FPoint{2, (int)(term_size.getHeight() - 8)}, finalcut::FSize{term_size.getWidth() - 4, 6});
    latest_view->unsetFocusable();
    
    // Add timer to periodically refresh display from main thread
    addTimer(settings.ui_update_freq);
}

void FuzzerTUI::onShow(finalcut::FShowEvent* ev) {
    finalcut::FDialog::onShow(ev);
    RefreshDisplay();
}

void FuzzerTUI::onClose(finalcut::FCloseEvent* ev) {
    is_running.store(false);
    // Stop timer to prevent RefreshDisplay() from being called during destruction
    delAllTimers();
    ev->accept();
}

void FuzzerTUI::onKeyPress(finalcut::FKeyEvent* ev) {
    if (ev->key() == finalcut::FKey::Escape) {
        is_running.store(false);
        // Stop timer before closing
        delAllTimers();
        close();
        ev->accept();
    } else if (ev->key() == finalcut::FKey('q') || ev->key() == finalcut::FKey('Q')) {
        is_running.store(false);
        // Stop timer before closing
        delAllTimers();
        close();
        ev->accept();
    } else {
        finalcut::FDialog::onKeyPress(ev);
    }
}

void FuzzerTUI::onTimer(finalcut::FTimerEvent* ev) {
    // This is called from the main UI thread, so it's safe to update widgets
    // Only refresh if we're still running
    if (is_running.load()) {
        RefreshDisplay();
    }
    finalcut::FDialog::onTimer(ev);
}

void FuzzerTUI::RefreshDisplay() {
    // Don't update if we're closing
    if (!is_running.load()) {
        return;
    }
    
    // Update geometry based on current terminal size
    finalcut::FSize term_size = getParentWidget()->getTermGeometry().getSize();
    setGeometry(finalcut::FPoint{1, 1}, finalcut::FSize{term_size.getWidth(), term_size.getHeight()});
    
    // Read data directly from knowledge with locks (async - called from timer in main thread)
    u32 current_history_size = 0;
    u32 latest_idx = 0;
    u32 graph_nodes = 0;
    u32 graph_edges = 0;
    u32 latest_trace_hash = 0;
    u32 latest_trace_length = 0;
    u32 latest_input_size = 0;
    
    {
        std::lock_guard<std::mutex> lock(knowledge.knowledge_mutex);
        
        // Count valid executions in history
        for (u32 i = 0; i < knowledge.history.size(); ++i) {
            if (!knowledge.history[i].trace.empty()) {
                current_history_size++;
                latest_idx = i;
            }
        }
        
        // Calculate graph stats
        graph_nodes = knowledge.graph.graph.size();
        for (const auto& entry : knowledge.graph.graph) {
            graph_edges += entry.second.size();
        }
        
        // Get latest execution info if history changed
        if (current_history_size > last_history_size && current_history_size > 0) {
            const FuzzExecution& latest = knowledge.history[latest_idx];
            // Compute trace hash for display
            for (u32 addr : latest.trace) {
                latest_trace_hash ^= addr;
                latest_trace_hash = (latest_trace_hash << 1) | (latest_trace_hash >> 31);  // Rotate left
            }
            latest_trace_length = latest.trace.size();
            latest_input_size = latest.input.size();
            last_history_size = current_history_size;
        }
    }
    
    // Update stats view
    stats_view->clear();
    stats_view->setGeometry(finalcut::FPoint{2, 2}, finalcut::FSize{term_size.getWidth() - 4, term_size.getHeight() - 10});
    std::ostringstream stats_oss;
    stats_oss << "Overall Statistics:\n";
    extern std::atomic<u32> g_total_executions;
    extern std::atomic<u32> g_crash_count;
    stats_oss << "  Total Executions: " << g_total_executions.load() << "\n";
    stats_oss << "  Total Crashes:    " << g_crash_count.load() << "\n";
    stats_oss << "  Unique Traces:    " << current_history_size << "\n";
    stats_oss << "  Graph Nodes:      " << graph_nodes << "\n";
    stats_oss << "  Graph Edges:      " << graph_edges << "\n";
    stats_view->append(stats_oss.str());
    
    // Update latest view
    latest_view->clear();
    latest_view->setGeometry(finalcut::FPoint{2, (int)(term_size.getHeight() - 8)}, finalcut::FSize{term_size.getWidth() - 4, 6});
    std::ostringstream latest_oss;
    latest_oss << "Latest Execution:\n";
    latest_oss << "  Trace Hash:   0x" << std::hex << std::setw(8) << std::setfill('0') 
        << latest_trace_hash << std::dec << std::setfill(' ') << "\n";
    latest_oss << "  Trace Length: " << latest_trace_length << " basic blocks\n";
    latest_oss << "  Input Size:   " << latest_input_size << " bytes\n";
    latest_view->append(latest_oss.str());
    
    redraw();
}

FuzzerTUI::~FuzzerTUI() {
    // Stop timer first to prevent any callbacks during destruction
    delAllTimers();
    
    // Set running flag to false to prevent RefreshDisplay() from running
    is_running.store(false);
    
    // Clear widget pointers - parent will handle actual deletion
    // Don't delete them here as finalcut manages widget lifetime
    stats_view = nullptr;
    latest_view = nullptr;
    
    // Base class destructor will be called automatically
}



