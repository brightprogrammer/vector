#include "tui.hh"
#include "settings.hh"
#include <final/final.h>
#include <sstream>
#include <iomanip>

FuzzerTUI::FuzzerTUI(finalcut::FWidget* parent, TUIData& data, const Settings& settings)
    : finalcut::FDialog{parent}, tui_data(data), settings(settings) {
    setText("Vector Fuzzer - Status");
    setResizeable(true);
    setMinimizable(false);
    
    // Get terminal size and make dialog fullscreen
    finalcut::FSize term_size = getParentWidget()->getTermGeometry().getSize();
    setGeometry(finalcut::FPoint{1, 1}, finalcut::FSize{term_size.getWidth(), term_size.getHeight()});
    
    // Create stats view (overall statistics)
    stats_view = new finalcut::FTextView{this};
    stats_view->setGeometry(finalcut::FPoint{2, 2}, finalcut::FSize{term_size.getWidth() - 4, 8});
    stats_view->unsetFocusable();
    
    // Create threads view (per-thread info) - takes most of the space
    u32 threads_height = term_size.getHeight() - 20;  // Leave space for stats and latest
    threads_view = new finalcut::FListView{this};
    threads_view->setGeometry(finalcut::FPoint{2, 11}, finalcut::FSize{term_size.getWidth() - 4, threads_height});
    threads_view->unsetFocusable();
    
    // Add columns to the threads table
    threads_view->addColumn("Thread");
    threads_view->addColumn("Execs");
    threads_view->addColumn("Crashes");
    threads_view->addColumn("Status");
    threads_view->addColumn("Size");
    threads_view->addColumn("First Bytes");
    threads_view->addColumn("Last Bytes");
    
    // Set column alignments
    threads_view->setColumnAlignment(1, finalcut::Align::Right);  // Execs
    threads_view->setColumnAlignment(2, finalcut::Align::Right);  // Crashes
    threads_view->setColumnAlignment(4, finalcut::Align::Right);  // Size
    
    // Create latest view (latest execution)
    latest_view = new finalcut::FTextView{this};
    latest_view->setGeometry(finalcut::FPoint{2, (int)(11 + threads_height + 1)}, finalcut::FSize{term_size.getWidth() - 4, 6});
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
    ev->accept();
}

void FuzzerTUI::onKeyPress(finalcut::FKeyEvent* ev) {
    if (ev->key() == finalcut::FKey::Escape) {
        is_running.store(false);
        close();
        ev->accept();
    } else if (ev->key() == finalcut::FKey('q') || ev->key() == finalcut::FKey('Q')) {
        is_running.store(false);
        close();
        ev->accept();
    } else {
        finalcut::FDialog::onKeyPress(ev);
    }
}

void FuzzerTUI::onTimer(finalcut::FTimerEvent* ev) {
    // This is called from the main UI thread, so it's safe to update widgets
    RefreshDisplay();
    finalcut::FDialog::onTimer(ev);
}

void FuzzerTUI::RefreshDisplay() {
    // Update geometry based on current terminal size
    finalcut::FSize term_size = getParentWidget()->getTermGeometry().getSize();
    setGeometry(finalcut::FPoint{1, 1}, finalcut::FSize{term_size.getWidth(), term_size.getHeight()});
    
    // Get snapshot of TUI data
    auto snap = tui_data.GetSnapshot();
    
    // Update stats view - use simple text labels instead of box-drawing
    stats_view->clear();
    stats_view->setGeometry(finalcut::FPoint{2, 2}, finalcut::FSize{term_size.getWidth() - 4, 8});
    std::ostringstream stats_oss;
    stats_oss << "Overall Statistics:\n";
    stats_oss << "  Total Executions: " << snap.total_executions << "\n";
    stats_oss << "  Total Crashes:    " << snap.total_crashes << "\n";
    stats_oss << "  Unique Traces:    " << snap.unique_traces << "\n";
    stats_oss << "  Graph Nodes:      " << snap.graph_nodes << "\n";
    stats_oss << "  Graph Edges:      " << snap.graph_edges << "\n";
    stats_view->append(stats_oss.str());
    
    // Update threads view
    threads_view->clear();
    u32 threads_height = term_size.getHeight() - 20;
    threads_view->setGeometry(finalcut::FPoint{2, 11}, finalcut::FSize{term_size.getWidth() - 4, threads_height});
    
    // Helper function to format bytes: ASCII printable as characters, others as \xHH
    auto formatBytes = [](const std::vector<u8>& bytes) -> std::string {
        if (bytes.empty()) return "(none)";
        std::ostringstream oss;
        for (size_t i = 0; i < bytes.size() && i < 8; ++i) {
            u8 b = bytes[i];
            // Check if printable ASCII (32-126, space to tilde)
            if (b >= 32 && b <= 126) {
                oss << (char)b;
            } else {
                // Non-printable: show as \xHH
                oss << "\\x" << std::hex << std::setw(2) << std::setfill('0') << (u32)b;
            }
        }
        return oss.str();
    };
    
    // Populate table with thread data
    for (const auto& t : snap.threads) {
        finalcut::FStringList row;
        row.push_back(finalcut::FString(std::to_string(t.thread_id)));
        row.push_back(finalcut::FString(std::to_string(t.executions)));  // THIS IS THE EXECUTION COUNT
        row.push_back(finalcut::FString(std::to_string(t.crashes)));
        row.push_back(finalcut::FString(t.status));
        row.push_back(finalcut::FString(std::to_string(t.input_size)));
        row.push_back(finalcut::FString(formatBytes(t.input_first_bytes)));
        row.push_back(finalcut::FString(formatBytes(t.input_last_bytes)));
        
        threads_view->insert(row);
    }
    
    // Force FListView to refresh/redraw
    threads_view->redraw();
    
    // Update latest view
    latest_view->clear();
    latest_view->setGeometry(finalcut::FPoint{2, (int)(11 + threads_height + 1)}, finalcut::FSize{term_size.getWidth() - 4, 6});
    std::ostringstream latest_oss;
    latest_oss << "Latest Execution:\n";
    latest_oss << "  Trace Hash:   0x" << std::hex << std::setw(8) << std::setfill('0') 
        << snap.latest_trace_hash << std::dec << std::setfill(' ') << "\n";
    latest_oss << "  Trace Length: " << snap.latest_trace_length << " basic blocks\n";
    latest_oss << "  Input Size:   " << snap.latest_input_size << " bytes\n";
    latest_view->append(latest_oss.str());
    
    redraw();
}



