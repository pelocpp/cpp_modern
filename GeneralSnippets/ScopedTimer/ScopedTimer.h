// ===========================================================================
// ScopedTimer.h
// ===========================================================================

#pragma once

#include <iostream>
#include <chrono>

class ScopedTimer
{
public:
    enum class Resolution { Milli, Micro, Nano };

private:
    std::chrono::steady_clock::time_point m_begin;
    enum class Resolution m_resolution;

public:
    ScopedTimer() : ScopedTimer{ Resolution::Milli }
    {
        startWatch();
    }

    ScopedTimer(enum class Resolution resolution) : m_resolution{ resolution }
    {
        startWatch();
    }

    ~ScopedTimer() {

        switch (m_resolution)
        {
        case Resolution::Milli:
            stopWatchMilli(std::cout);
            break;
        case Resolution::Micro:
            stopWatchMicro(std::cout);
            break;
        case Resolution::Nano:
            stopWatchNano(std::cout);
            break;
        }
    }

    // no copying or moving
    ScopedTimer(const ScopedTimer&) = delete;
    ScopedTimer& operator=(const ScopedTimer&) = delete;

    ScopedTimer(ScopedTimer&&) = delete;
    ScopedTimer& operator=(ScopedTimer&&) = delete;

private:
    void startWatch() {
        m_begin = std::chrono::steady_clock::now();
    }

    void stopWatchMilli(std::ostream& os) const {
        std::chrono::steady_clock::time_point end{ std::chrono::steady_clock::now() };
        auto duration{ std::chrono::duration_cast<std::chrono::milliseconds>(end - m_begin).count() };
        os << "Elapsed time: " << duration << " milliseconds." << std::endl;
    }

    void stopWatchMicro(std::ostream& os) const {
        std::chrono::steady_clock::time_point end{ std::chrono::steady_clock::now() };
        auto duration{ std::chrono::duration_cast<std::chrono::microseconds>(end - m_begin).count() };
        os << "Elapsed time: " << duration << " microseconds." << std::endl;
    }

    void stopWatchNano(std::ostream& os) const {
        std::chrono::steady_clock::time_point end{ std::chrono::steady_clock::now() };
        auto duration{ std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_begin).count() };
        os << "Elapsed time: " << duration << " nanoseconds." << std::endl;
    }
};

// ===========================================================================
// End-of-File
// ===========================================================================
