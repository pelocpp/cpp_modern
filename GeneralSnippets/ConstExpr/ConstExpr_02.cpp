// =====================================================================================
// ConstExpr_02.cpp
// =====================================================================================

module modern_cpp:const_expr;

namespace ConstExpr {

    constexpr bool DEBUG_ENABLED = true;

    enum class LogLevel
    {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    constexpr char const* toString(const LogLevel level)
    {
        switch (level)
        {
        case LogLevel::TRACE:
            return "TRACE";
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::ERROR:
            return "ERROR";
        }
    }

    template <LogLevel level, typename TContent>
    inline void log(const TContent& content)
    {
        if constexpr (DEBUG_ENABLED || level > LogLevel::DEBUG)
        {
            constexpr auto level_string = toString(level);
            std::cout << "[" << level_string << "] " << content << std::endl;
        }
    }

    void test_01() {

        log<LogLevel::TRACE>("Just a test");
        log<LogLevel::INFO>(12345);
    }
}

void main_constexpr_02()
{
    using namespace ConstExpr;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
