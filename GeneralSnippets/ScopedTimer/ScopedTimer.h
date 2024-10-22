// ===========================================================================
// ScopedTimer.h
// ===========================================================================

#include <iostream>
#include <chrono>

class ScopedTimer
{
private:
    static inline std::chrono::steady_clock::time_point s_begin;

public:
    ScopedTimer() {
        startWatch();
    }

    ~ScopedTimer() {
        stopWatchMilli(std::cout);
    }

    // no copying or moving
    ScopedTimer(const ScopedTimer&) = delete;
    ScopedTimer& operator=(const ScopedTimer&) = delete;

    ScopedTimer(ScopedTimer&&) = delete;
    ScopedTimer& operator=(ScopedTimer&&) = delete;

private:
    static void startWatch() {
        s_begin = std::chrono::steady_clock::now();
    }

    static void stopWatchMilli(std::ostream& os) {
        std::chrono::steady_clock::time_point end{ std::chrono::steady_clock::now() };
        auto duration{ std::chrono::duration_cast<std::chrono::milliseconds>(end - s_begin).count() };
        os << "Elapsed time: " << duration << " milliseconds." << std::endl;
    }

    static void stopWatchMicro(std::ostream& os) {
        std::chrono::steady_clock::time_point end{ std::chrono::steady_clock::now() };
        auto duration{ std::chrono::duration_cast<std::chrono::microseconds>(end - s_begin).count() };
        os << "Elapsed time: " << duration << " microseconds." << std::endl;
    }
};

// ===========================================================================
// End-of-File
// ===========================================================================
