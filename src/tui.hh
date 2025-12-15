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

///
/// Main TUI window class using finalcut
///
class FuzzerTUI : public finalcut::FDialog {
public:
    explicit FuzzerTUI(finalcut::FWidget* parent, FuzzerKnowledge& knowledge, const Settings& settings);
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
    FuzzerKnowledge& knowledge;
    const Settings& settings;
    std::atomic<bool> is_running{true};
    u32 last_history_size{0};
    
    // UI components
    finalcut::FTextView* stats_view{nullptr};
    finalcut::FTextView* latest_view{nullptr};
    
};

#endif // VECTOR_FUZZER_TUI_HH

