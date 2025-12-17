// =====================================================================================
// Println.cpp // std::print // std::println
// =====================================================================================


module;

#include <cstdint>

module modern_cpp:println;

// defines for custom formatting
// #define StdFormatter_01_Basic_Formatter_API
// #define StdFormatter_02_Parsing_Format_String
// #define StdFormatter_03_Delegating_Formatting_to_Standard_Formatters
// #define StdFormatter_04_Inheriting_From_Standard_Formatters
// #define StdFormatter_05_Using_Standard_Formatters_for_Strings
// #define StdFormatter_06_Using_Standard_Formatters_for_StdVector
// #define StdFormatter_07_Custom_Parsing_01
// #define StdFormatter_07_Custom_Parsing_02
// #define StdFormatter_07_Custom_Parsing_03

namespace StdPrintln {

    static void test_01()
    {
        std::println("Hello, world!");
    }

    static void test_02()
    {
        int value{ 123 };
        std::println("Value: {}", value);
    }

    static void test_03()
    {
        int firstValue{ 123 };
        int secondValue{ 456 };

        std::println("First Value: {}, Second Value: {}", firstValue, secondValue);
        std::println("First Value: {0}, Second Value: {1}", firstValue, secondValue);
    }

    // fill and align
    static void test_04()
    {
        int value{ 123 };

        std::println("{}", value);             // "123"
        std::println("{0}", value);            // "123"
        std::println("{:10}", value);          // "       123"
        std::println("!{:_<10}!", value);      // "!123_______!"
        std::println("!{:_>10}!", value);      // "!_______123!"
    }

    // fill, align and precision
    static void test_05()
    {
        int value{ 123 };

        std::println("{}", value);             // "123"
        std::println("{:d}", value);           // "123"
        std::println("{:010}", value);         // "0000000123"
        std::println("{:010d}", value);        // "0000000123"
        std::println("{:0}", value);           // "123"
        std::println("{:+}", value);           // "+123"
        std::println("{:+}", -value);          // "-123"
        std::println("{:+10}", value);         // "      +123"
        std::println("{:+10}", -value);        // "      -123"
        std::println("{:+010}", value);        // "+000000123"
        std::println("{:+010}", -value);       // "-000000123"
    }

    // fill, align and precision
    static void test_06()
    {
        float pi{ 3.1415926535f };

        std::println("{}", pi);                // "3.1415927"
        std::println("{0}", pi);               // "3.1415927"
        std::println("{:15f}", pi);            // "       3.141593"    (width = 15)
        std::println("{:{}f}", pi, 15);        // "       3.141593"    (width = 15)
        std::println("{:.12f}", pi);           // "3.141592741013"     (precision = 12)
        std::println("{:.{}f}", pi, 3);        // "3.142"              (precision = 3)
        std::println("{:15.12f}", pi);         // " 3.141592741013"    (width = 15, precision = 12)
        std::println("{:{}.{}f}", pi, 15, 12); // " 3.141592741013"    (width = 15, precision = 12)
    }

    // fill, align and precision
    static void test_07()
    {
        double pi{ 3.1415926535f };

        std::println("{}", pi);                // "3.1415927"
        std::println("{0}", pi);               // "3.1415927"
        std::println("{:15g}", pi);            // "       3.141593"    (width = 15)
        std::println("{:{}g}", pi, 15);        // "       3.141593"    (width = 15)
        std::println("{:.12g}", pi);           // "3.141592741013"     (precision = 12)
        std::println("{:.{}g}", pi, 3);        // "3.142"              (precision = 3)
        std::println("{:15.12g}", pi);         // " 3.141592741013"    (width = 15, precision = 12)
        std::println("{:{}.{}g}", pi, 15, 12); // " 3.141592741013"    (width = 15, precision = 12)
    }

    // Sign, #, and different formats 
    static void test_08()
    {
        std::println("Hexadecimal:  {:x}", 6);      // "Hexadecimal:  6"
        std::println("Hexadecimal:  {:x}", 30);     // "Hexadecimal: 1e"
        std::println("Hexadecimal:  {:X}", 30);     // "Hexadecimal: 1E"
        std::println("Hexadecimal:  {:#x}", 30);    // "Hexadecimal: 0x1e"
        std::println("Hexadecimal:  {:#X}", 30);    // "Hexadecimal: 0X1E"
        std::println("Hexadecimal:  {:15x}", 6);    // "Hexadecimal:               6"   (width = 15)
        std::println("Hexadecimal:  {:#15X}", 30);  // "Hexadecimal:            0X1E"   (width = 15)

        std::println("Octal:        {:o} ", 12);    // "Octal:       14"
        std::println("Octal:        {:#o} ", 12);   // "Octal:       014"
        std::println("Octal:        {:#o}", 4);     // "Octal:       04"

        std::println("Binary:       {:b} ", 31);    // "Binary:      11111"
        std::println("Binary:       {:#b} ", 31);   // "Binary:      0b11111"
        std::println("Binary:       {:#B}", 7);     // "Binary:      0B111"
        std::println("Binary:       {:#15b} ", 31); // "Binary:              0b11111"   (width = 15)
        std::println("Binary:       {:#15B}", 7);   // "Binary:                0B111"   (width = 15)
    }

    // printing address of a variable  
    static void test_09()
    {
        int n = 123;
        int* ip = &n;

        std::println("&n: {:#X}", reinterpret_cast<intptr_t>(ip));
        std::println("&n: {:#x}", reinterpret_cast<intptr_t>(&n));
    }
}

// =====================================================================================
// =====================================================================================

namespace Formatting_Examples_Revised
{
    class SimpleClass
    {
    private:
        int m_value;

    public:
        SimpleClass() : SimpleClass{ 0 } {}

        explicit SimpleClass(int value) : m_value{ value } {}

        int getValue() const { return m_value; }
    };
}

#ifdef StdFormatter_01_Basic_Formatter_API

// Basic Formatter API

namespace std
{
    using namespace Formatting_Examples_Revised;

    template<>
    struct formatter<SimpleClass>
    {
        // parse the format string for this type
        constexpr auto parse(std::format_parse_context& ctx) {
            return ctx.begin(); // should return position of '}' (hopefully)
        }

        // format by always writing its value:
        auto format(const SimpleClass& obj, std::format_context& ctx) const {
            return std::format_to(ctx.out(), "{}", obj.getValue());
        }
    };
}

static void test_10()
{
    using namespace Formatting_Examples_Revised;

    SimpleClass obj{ 123 };

    std::println("Value: {}", obj);

    std::println("Two Values: {0} - {0}", obj);
}

#endif // StdFormatter_01_Basic_Formatter_API

// ===========================================================================
// ===========================================================================

#ifdef StdFormatter_02_Parsing_Format_String

namespace std
{
    using namespace Formatting_Examples_Revised;

    template<>
    class formatter<SimpleClass>
    {
    private:
        int m_width; // specified width of the field

    public:
        constexpr formatter() : m_width{ 0 } {}

        // parse the format string for this type
        constexpr auto parse(std::format_parse_context& ctx)
        {
            auto pos{ ctx.begin() };
            while (pos != ctx.end() && *pos != '}') {
                if (*pos < '0' || *pos > '9') {
                    throw std::format_error{ std::format("invalid format '{}'", *pos) };
                }

                m_width = m_width * 10 + (*pos - '0'); // new digit for the width
                ++pos;
            }
            return pos; // should return position of '}'
        }

        // format by always writing its value
        auto format(const SimpleClass& obj, std::format_context& ctx) const {
            return std::format_to(ctx.out(), "{:{}}", obj.getValue(), m_width);
        }
    };
}

static void test_11()
{
    using namespace Formatting_Examples_Revised;

    try {
        SimpleClass obj{ 123 };
        std::println("{}", obj.getValue());
        std::println("Value: {}", obj);
        std::println("Twice: {0} {0}", obj);
        std::println("With width:       '{:6}'", obj);
        std::println("Twice with width: '{0:6}' = '{1:6}'", obj, obj);
    }
    catch (std::format_error& e) {
        std::println(std::cerr, "Format Error: {}", e.what());
    }
}

#endif // StdFormatter_02_Parsing_Format_String

// ===========================================================================
// ===========================================================================

#ifdef StdFormatter_03_Delegating_Formatting_to_Standard_Formatters

namespace std
{
    using namespace Formatting_Examples_Revised;

    // delegating formatting to standard formatters
    template<>
    class formatter<SimpleClass>
    {
    private:
        // use a standard int formatter that does the work:
        std::formatter<int> m_formatter;

    public:
        // delegate parsing to the standard formatter:
        constexpr auto parse(std::format_parse_context& ctx) {
            return m_formatter.parse(ctx);
        }

        // delegate formatting of the value to the standard formatter:
        auto format(const SimpleClass& obj, std::format_context& ctx) const {
            return m_formatter.format(obj.getValue(), ctx);
        }
    };
}

static void test_12()
{
    using namespace Formatting_Examples_Revised;

    try {
        SimpleClass obj{ 123 };
        std::println("{}", obj.getValue());
        std::println("Value: {}", obj);
        std::println("Twice: {0} {0}", obj);
        std::println("With width: '{:>20}'", obj);
        std::println("With all:   '{:.^20}'", obj);
    }
    catch (std::format_error& e) {
        std::println(std::cerr, "Format Error: {}", e.what());
    }
}

#endif // StdFormatter_03_Delegating_Formatting_to_Standard_Formatters

// ===========================================================================
// ===========================================================================

#ifdef StdFormatter_04_Inheriting_From_Standard_Formatters

namespace std
{
    using namespace Formatting_Examples_Revised;

    // inheriting From Standard Formatters
    template<>
    struct std::formatter<SimpleClass> : std::formatter<int>
    {
        auto format(const SimpleClass& obj, std::format_context& ctx) const {
            // delegate formatting of the value to the standard formatter
            return std::formatter<int>::format(obj.getValue(), ctx);
        }
    };
}

static void test_13()
{
    using namespace Formatting_Examples_Revised;

    try {
        SimpleClass obj{ 123 };
        std::println("{}", obj.getValue());
        std::println("Value: {}", obj);
        std::println("Twice: {0} {0}", obj);
        std::println("With width: '{:>20}'", obj);
        std::println("With all:   '{:.^20}'", obj);
    }
    catch (std::format_error& e) {
        std::println(std::cerr, "Format Error: {}", e.what());
    }
}

#endif // StdFormatter_04_Inheriting_From_Standard_Formatters

// ===========================================================================
// ===========================================================================

#ifdef StdFormatter_05_Using_Standard_Formatters_for_Strings

namespace Formatting_Examples_Revised
{
    enum class Color { red, green, blue };
}

namespace std
{
    using namespace Formatting_Examples_Revised;

    // formatter for user defined enum type Color
    template<>
    struct std::formatter<Color> : public std::formatter<std::string>
    {
        auto format(Color col, format_context& ctx) const {

            std::string value{};

            switch (col)
            {
            case Color::red:
                value = "red";
                break;
            case Color::green:
                value = "green";
                break;
            case Color::blue:
                value = "blue";
                break;
            default:
                value = std::format("Color{}", static_cast<int>(col));
                break;
            }

            // delegate the rest of formatting to the string formatter
            return std::formatter<std::string>::format(value, ctx);
        }
    };
}

static void test_14()
{
    using namespace Formatting_Examples_Revised;

    // using user-provided formatter for enum Color
    for (auto val : { Color::red, Color::green, Color::blue, Color{ 123 } })
    {
        std::println("Color {:_>8} has value 0X{:02X}", val, static_cast<int>(val));
    }
}

#endif // StdFormatter_05_Using_Standard_Formatters_for_Strings

// ===========================================================================
// ===========================================================================

#ifdef StdFormatter_06_Using_Standard_Formatters_for_StdVector

namespace std
{
    using namespace Formatting_Examples_Revised;

    // formatter for std::vector
    template <typename T>
    struct std::formatter<std::vector<T>> : std::formatter<std::string_view>
    {
        constexpr auto parse(format_parse_context& ctx) {
            return ctx.begin();
        }

        auto format(const std::vector<T>& vec, std::format_context& ctx) const {

            std::string tmp{};

            const auto fmt_str = [&]() {
                if constexpr (std::is_integral<T>::value) {
                    return "{:+5}";
                }
                else if constexpr (std::is_floating_point<T>::value) {
                    return "{:+5.2}";
                }
                else {
                    return "{}";
                }
                }();

            const auto header = [&]() {

                if (std::is_same<T, int>::value) {
                    return "std::vector<int>";
                }
                else if (std::is_same<T, long>::value) {
                    return "std::vector<long>";
                }
                else if (std::is_same<T, short>::value) {
                    return "std::vector<short>";
                }
                else if (std::is_same<T, float>::value) {
                    return "std::vector<float>";
                }
                else if (std::is_same<T, double>::value) {
                    return "std::vector<double>";
                }
                else {
                    return "std::vector<>";
                }
                }();

            std::format_to(std::back_inserter(tmp), "{} - ", header);

            T lastElem = vec.back();

            std::for_each(
                vec.begin(),
                std::prev(vec.end()),
                [&](const auto& elem) {
                    std::format_to(std::back_inserter(tmp), "{}, ", elem);
                }
            );

            std::format_to(std::back_inserter(tmp), "{}", lastElem);

            return std::formatter<string_view>::format(tmp, ctx);
        }
    };
}

static void test_15()
{
    std::vector<int> intVec = { 1, 2, 3, 4, 5 };
    std::println("{}", intVec);

    std::vector<double> doublesVec = { 1.5, 2.5, 3.5, 4.5, 5.5 };
    std::println("{}", doublesVec);
}

#endif // StdFormatter_06_Using_Standard_Formatters_for_StdVector

// ===========================================================================
// ===========================================================================

namespace Formatting_Examples_Again_Revised
{
    class Color
    {
    private:
        std::uint8_t m_red;
        std::uint8_t m_green;
        std::uint8_t m_blue;

    public:
        Color() : Color{ 0, 0, 0 } {}

        Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
            : m_red{ red }, m_green{ green }, m_blue{ blue }
        {}

        std::uint8_t getRed() const { return m_red; }
        std::uint8_t getGreen() const { return m_green; }
        std::uint8_t getBlue() const { return m_blue; }
    };
}

#ifdef StdFormatter_07_Custom_Parsing_01

namespace std
{
    using namespace Formatting_Examples_Again_Revised;

    // formatter for class Color
    template<>
    struct std::formatter<Color> {
        constexpr auto parse(std::format_parse_context& ctx) {
            return ctx.begin();
        }

        auto format(const Color& col, std::format_context& ctx) const {

            return
                std::format_to(ctx.out(), "[{}, {}, {}]", col.getRed(), col.getGreen(), col.getBlue());
        }
    };
}

static void test_16()
{
    using namespace Formatting_Examples_Again_Revised;

    std::println("Color {}", Color{ 100, 200, 255 });
}

#endif // StdFormatter_07_Custom_Parsing_01

// ===========================================================================
// ===========================================================================

#ifdef StdFormatter_07_Custom_Parsing_02

namespace std
{
    using namespace Formatting_Examples_Again_Revised;

    // formatter for class Color
    template<>
    struct std::formatter<Color> : std::formatter<string_view>
    {
        auto format(const Color& col, std::format_context& ctx) const {

            std::string tmp{};

            std::format_to(std::back_inserter(tmp), "({}, {}, {})",
                col.getRed(), col.getGreen(), col.getBlue());

            return std::formatter<string_view>::format(tmp, ctx);
        }
    };
}

static void test_17()
{
    using namespace Formatting_Examples_Again_Revised;

    std::println("Color {}", Color{ 100, 200, 255 });
    // std::println("col {:h}\n", Color{ 100, 200, 255 });   // does not compile
}

#endif // StdFormatter_07_Custom_Parsing_02

// ===========================================================================
// ===========================================================================

#ifdef StdFormatter_07_Custom_Parsing_03

namespace std
{
    using namespace Formatting_Examples_Again_Revised;

    // formatter for class Color
    template <>
    class std::formatter<Color>
    {
    private:
        bool m_isHex;

    public:
        constexpr formatter() : m_isHex{ false } {}

        constexpr auto parse(std::format_parse_context& ctx)
        {
            auto pos{ ctx.begin() };
            while (pos != ctx.end() && *pos != '}') {
                if (*pos == 'h' || *pos == 'H')
                    m_isHex = true;
                ++pos;
            }

            return pos; // should return position of '}'
        }

        auto format(const Color& col, std::format_context& ctx) const {

            if (m_isHex) {
                uint32_t val{ static_cast<uint32_t>(col.getRed() << 16 | col.getGreen() << 8 | col.getBlue()) };
                return std::format_to(ctx.out(), "#{:X}", val);
            }
            else {
                return std::format_to(ctx.out(), "[{}, {}, {}]", col.getRed(), col.getGreen(), col.getBlue());
            }
        };
    };
}

static void test_18()
{
    using namespace Formatting_Examples_Again_Revised;

    Color color{ 100, 200, 255 };

    std::println("Color {}", color);
    std::println("Color {:h}", color);
}

#endif // StdFormatter_07_Custom_Parsing_03

// ===========================================================================
// ===========================================================================

void main_println()
{
    using namespace StdPrintln;

    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
    test_07();
    test_08();
    test_09();

#ifdef StdFormatter_01_Basic_Formatter_API
    test_10();
#endif

#ifdef StdFormatter_02_Parsing_Format_String
    test_11();
#endif

#ifdef StdFormatter_03_Delegating_Formatting_to_Standard_Formatters
    test_12();
#endif

#ifdef StdFormatter_04_Inheriting_From_Standard_Formatters
    test_13();
#endif

#ifdef StdFormatter_05_Using_Standard_Formatters_for_Strings
    test_14();
#endif

#ifdef StdFormatter_06_Using_Standard_Formatters_for_StdVector
    test_15();
#endif

#ifdef StdFormatter_07_Custom_Parsing_01
    test_16();
#endif

#ifdef StdFormatter_07_Custom_Parsing_02
    test_17();
#endif

#ifdef StdFormatter_07_Custom_Parsing_03
    test_18();
#endif
}

// =====================================================================================
// End-of-File
// =====================================================================================
    