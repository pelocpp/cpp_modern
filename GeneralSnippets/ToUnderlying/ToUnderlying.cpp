// =====================================================================================
// ToUnderlying.cpp
// =====================================================================================

module modern_cpp:to_underlying;

namespace ToUnderlying {

    enum class Color : char {
        Red   = 'R',
        Green = 'G',
        Blue  = 'B'
    };

    enum class Weekdays : int {
        Monday     = 1,
        Tuesday    = 2,
        Wednesday  = 3,
        Thursday   = 4,
        Friday     = 5,
        Saturday   = 6,
        Sunday     = 7,
    };

    static void test_01()
    {
        Color color{ Color::Blue };
        auto colorCode{ std::to_underlying(color) };
        static_assert(std::is_same<decltype(colorCode), char>::value);
        std::println("Color Code: {}", colorCode);

        Weekdays day{ Weekdays::Friday };
        int dayCode{ std::to_underlying(day) };
        static_assert(std::is_same<decltype(dayCode), int>::value);
        std::println("Weekday Code: {}", dayCode);
    }
}

void main_to_underlying()
{
    using namespace ToUnderlying;

    test_01(); 
}

// =====================================================================================
// End-of-File
// =====================================================================================
