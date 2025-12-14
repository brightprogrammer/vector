#ifndef VECTOR_FUZZER_TUI_HH
#define VECTOR_FUZZER_TUI_HH

#include "types.hh"
#include "knowledge.hh"
#include "settings.hh"
#include <final/final.h>
#include <vector>
#include <string>
#include <mutex>
#include <atomic>
#include <memory>

// Forward declaration
struct ThreadStats;

///
/// Thread-safe data structure for TUI updates
///
struct TUIData {
    mutable std::mutex mutex;
    
    // Overall statistics
    u32 total_executions{0};
    u32 total_crashes{0};
    u32 unique_traces{0};
    u32 graph_nodes{0};
    u32 graph_edges{0};
    
    // Per-thread statistics
    struct ThreadInfo {
        u32 thread_id;
        u32 executions{0};
        u32 crashes{0};
        std::string status{"Stopped"};
        u32 input_size{0};
        std::vector<u8> input_first_bytes;  // First few bytes of current input
        std::vector<u8> input_last_bytes;   // Last few bytes of current input
    };
    std::vector<ThreadInfo> threads;
    
    // Latest execution info
    u32 latest_trace_hash{0};
    u32 latest_trace_length{0};
    u32 latest_input_size{0};
    
    // Update methods
    void UpdateOverall(u32 execs, u32 crashes, u32 traces, u32 nodes, u32 edges) {
        std::lock_guard<std::mutex> lock(mutex);
        total_executions = execs;
        total_crashes = crashes;
        unique_traces = traces;
        graph_nodes = nodes;
        graph_edges = edges;
    }
    
    void UpdateLatest(u32 hash, u32 trace_len, u32 input_sz) {
        std::lock_guard<std::mutex> lock(mutex);
        latest_trace_hash = hash;
        latest_trace_length = trace_len;
        latest_input_size = input_sz;
    }
    
    void UpdateThread(u32 thread_id, u32 execs, u32 crashes, const std::string& status, u32 input_size, const std::vector<u8>& first_bytes = {}, const std::vector<u8>& last_bytes = {}) {
        std::lock_guard<std::mutex> lock(mutex);
        // Find or create thread info
        for (auto& t : threads) {
            if (t.thread_id == thread_id) {
                t.executions = execs;
                t.crashes = crashes;
                t.status = status;
                t.input_size = input_size;
                t.input_first_bytes = first_bytes;
                t.input_last_bytes = last_bytes;
                return;
            }
        }
        // Thread not found, add it
        ThreadInfo info;
        info.thread_id = thread_id;
        info.executions = execs;
        info.crashes = crashes;
        info.status = status;
        info.input_size = input_size;
        info.input_first_bytes = first_bytes;
        info.input_last_bytes = last_bytes;
        threads.push_back(info);
    }
    
    // Snapshot method for reading
    struct Snapshot {
        u32 total_executions;
        u32 total_crashes;
        u32 unique_traces;
        u32 graph_nodes;
        u32 graph_edges;
        u32 latest_trace_hash;
        u32 latest_trace_length;
        u32 latest_input_size;
        std::vector<ThreadInfo> threads;
    };
    
    Snapshot GetSnapshot() const {
        std::lock_guard<std::mutex> lock(mutex);
        Snapshot snap;
        snap.total_executions = total_executions;
        snap.total_crashes = total_crashes;
        snap.unique_traces = unique_traces;
        snap.graph_nodes = graph_nodes;
        snap.graph_edges = graph_edges;
        snap.latest_trace_hash = latest_trace_hash;
        snap.latest_trace_length = latest_trace_length;
        snap.latest_input_size = latest_input_size;
        snap.threads = threads;
        return snap;
    }
};

///
/// Main TUI window class using finalcut
///
class FuzzerTUI : public finalcut::FDialog {
public:
    explicit FuzzerTUI(finalcut::FWidget* parent, TUIData& data, const Settings& settings);
    ~FuzzerTUI() override = default;
    
    // Update the display with latest data
    void RefreshDisplay();
    
    // Set whether TUI should continue running
    void SetRunning(bool running) { is_running = running; }
    bool isRunning() const { return is_running.load(); }
    
protected:
    void onShow(finalcut::FShowEvent* ev) override;
    void onClose(finalcut::FCloseEvent* ev) override;
    void onKeyPress(finalcut::FKeyEvent* ev) override;
    void onTimer(finalcut::FTimerEvent* ev) override;
    
private:
    TUIData& tui_data;
    const Settings& settings;
    std::atomic<bool> is_running{true};
    
    // UI components
    finalcut::FTextView* stats_view{nullptr};
    finalcut::FListView* threads_view{nullptr};
    finalcut::FTextView* latest_view{nullptr};
    
};

#endif // VECTOR_FUZZER_TUI_HH

