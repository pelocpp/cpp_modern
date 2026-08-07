// ===============================================================================
// ScopedTimer.ixx // Class for measuring runtime
// ===============================================================================

export module scoped_timer;

import std;

export class ScopedTimer
{
public:
    enum class Resolution { Milli, Micro, Nano };

private:
    std::chrono::steady_clock::time_point m_begin;
    enum Resolution m_resolution;

public:
    ScopedTimer() : ScopedTimer{ Resolution::Milli }
    {
        startWatch();
    }

    ScopedTimer(enum Resolution resolution) : m_resolution{ resolution }
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

    ScopedTimer(ScopedTimer&&) noexcept = delete;
    ScopedTimer& operator=(ScopedTimer&&) noexcept = delete;

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

// ===============================================================================
// End-of-File
// ===============================================================================
