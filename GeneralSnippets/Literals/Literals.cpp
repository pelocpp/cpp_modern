// =====================================================================================
// User defined literals
// =====================================================================================

module;

#include <cstdint>   // for uint8_t

module modern_cpp:literals;

namespace Literals_With_Separators {

    static void test_01() {

        // binary, octal and hexadecimal literals
        // (including single quotation mark as separator)

        long decval { 1'048'576 };
        long hexval { 0x10'0000 };
        long octval { 00'04'00'00'00 };
        long binval { 0b1'00000000'00000000'00000000 };

        std::cout << decval << std::endl;
        std::cout << hexval << std::endl;
        std::cout << octval << std::endl;
        std::cout << binval << std::endl;
    }
}

// =====================================================================================
// implementation of literal operator
// =====================================================================================

namespace Literals_Color_Runtime {

    class Color {
        friend std::ostream& operator<< (std::ostream&, const Color&);

    private:
        uint8_t m_r;
        uint8_t m_g;
        uint8_t m_b;

    public:
        Color() : m_r{}, m_g{}, m_b{} {}

        Color(uint8_t r, uint8_t g, uint8_t b)
            : m_r{ r }, m_g{ g }, m_b{ b } {}
    };

    std::ostream& operator<< (std::ostream& os, const Color& col) {

        os << std::uppercase
            << std::hex << std::setw(2) << std::setfill('0') << (int) col.m_r << ":"
            << std::hex << std::setw(2) << std::setfill('0') << (int) col.m_g << ":"
            << std::hex << std::setw(2) << std::setfill('0') << (int) col.m_b;

        return os;
    }

    // literal operator ("cooked" version)
    static Color operator"" _rgb(unsigned long long int value) {

        if (value > 0xFFFFFF) {
            throw std::runtime_error("literal too large");
        }

        uint8_t r{ static_cast<uint8_t>((value & 0x00FF0000) >> 16) };
        uint8_t g{ static_cast<uint8_t>((value & 0x0000FF00) >> 8) };
        uint8_t b{ static_cast<uint8_t>((value & 0x000000FF) >> 0) };

        return Color { r, g, b };
    }

    // literal operator ("raw" version)
    static Color operator"" _rgb(const char* literal, size_t length) {

        // tiny implementation - just parsing hexadecimal format
        std::string arg(literal);

        if (arg.size() == 2 /* 0x */ + 6 /* FF FF FF */) {

            std::string rs { arg.substr(2, 2) };
            std::string gs { arg.substr(4, 2) };
            std::string bs { arg.substr(6, 2) };

            uint8_t r { static_cast<uint8_t>(std::stoi(rs, nullptr, 16)) };
            uint8_t g { static_cast<uint8_t>(std::stoi(gs, nullptr, 16)) };
            uint8_t b { static_cast<uint8_t>(std::stoi(bs, nullptr, 16)) };

            return Color{ r, g, b };
        }

        return Color{};
    }

    static void test_02() {

        Color red{ 0xFF0000_rgb };
        std::cout << red << std::endl;

        Color magenta{ 0xFF00FF_rgb };
        std::cout << magenta << std::endl;

        Color yellow{ 0xFFFF00_rgb };
        std::cout << yellow << std::endl;

        Color unknown{ 12345_rgb };
        std::cout << unknown << std::endl;

        unknown = "0x012345"_rgb;
        std::cout << unknown << std::endl;
    }

    static void test_02_with_errors()
    {
        // value outside rgb range
         Color col1{ 0x1FFFFFF_rgb };
         std::cout << col1 << std::endl;

        // illegal hexadecimal digit
         Color col2{ "0x00GG00"_rgb };
         std::cout << col2 << std::endl;
    }
}

// =====================================================================================
// 'constexpr' implementation of literal operator
// =====================================================================================

namespace Literals_Color_CompileTime {

    class Color {
        friend std::ostream& operator<< (std::ostream&, const Color&);

    private:
        uint8_t m_r;
        uint8_t m_g;
        uint8_t m_b;

    public:
        constexpr Color() : m_r{}, m_g{}, m_b{} {}

        constexpr Color(uint8_t r, uint8_t g, uint8_t b)
            : m_r{ r }, m_g{ g }, m_b{ b } {}
    };

    std::ostream& operator<< (std::ostream& os, const Color& col) {

        os << std::uppercase
            << std::hex << std::setw(2) << std::setfill('0') << (int)col.m_r << ":"
            << std::hex << std::setw(2) << std::setfill('0') << (int)col.m_g << ":"
            << std::hex << std::setw(2) << std::setfill('0') << (int)col.m_b;

        return os;
    }

    // literal operator ("cooked" version)
    static constexpr Color operator"" _rgb(unsigned long long int value) {

        if (value > 0xFFFFFF) {
            throw std::logic_error("literal too large");
        }

        uint8_t r{ static_cast<uint8_t>((value & 0x00FF0000) >> 16) };
        uint8_t g{ static_cast<uint8_t>((value & 0x0000FF00) >> 8) };
        uint8_t b{ static_cast<uint8_t>((value & 0x000000FF) >> 0) };

        return Color{ r, g, b };
    }

    static constexpr bool isHex(char ch) {

        if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f')) {
            return true;
        }

        return false;
    }

    static constexpr uint8_t hex2int(char ch) {

        if (!isHex(ch)) {
            throw std::logic_error("illegal hexadecimal digit");
        }

        // transform hex character to 4-bit equivalent number
        uint8_t byte{ static_cast<uint8_t>(ch) };

        if (byte >= '0' and byte <= '9') {
            byte -= '0';
        }
        else if (byte >= 'a' and byte <= 'f') {
            byte -= ('a' - 10);
        }
        else if (byte >= 'A' and byte <= 'F') {
            byte -= ('A' - 10);
        }

        return byte;
    }

    static constexpr size_t hexstoi(const char* str)
    {
        int value{};

        while (*str != '\0') {

            // get current character, then increment
            uint8_t byte{ hex2int(*str) };
            ++str;

            // shift 4 to make space for new digit, and add the 4 bits of the new digit 
            value = (value << 4) | (byte & 0xF);
        }

        return value;
    }

    // literal operator ('raw' and 'constexpr' version)
    static constexpr Color operator"" _rgb(const char* literal, size_t length) {

        // std::string is partially 'constexpr'
        std::string arg(literal);

        if (arg.size() == 2 /* 0x */ + 6 /* FF FF FF */) {

            std::string rs{ arg.substr(2, 2) };
            std::string gs{ arg.substr(4, 2) };
            std::string bs{ arg.substr(6, 2) };

            // std::stoi is not 'constexpr' -  at the time of this writing
             uint8_t r { static_cast<uint8_t>(hexstoi(rs.c_str())) };
             uint8_t g { static_cast<uint8_t>(hexstoi(gs.c_str())) };
             uint8_t b { static_cast<uint8_t>(hexstoi(bs.c_str())) };

            return Color{ r, g, b };
        }

        return Color{};
    }

    static void test_03() {

        constexpr Color red{ 0xFF0000_rgb };
        std::cout << red << std::endl;

        constexpr Color magenta{ 0xFF00FF_rgb };
        std::cout << magenta << std::endl;

        constexpr Color yellow{ 0xFFFF00_rgb };
        std::cout << yellow << std::endl;

        constexpr Color unknown{ 12345_rgb };
        std::cout << unknown << std::endl;
    }

    // throws errors at compile time
    static void test_03_with_errors() {

        // value outside rgb range
        // constexpr Color col1{ 0x1FFFFFF_rgb };

        // illegal hexadecimal digit
        // constexpr Color col2{ "0x00GG00"_rgb };
    }
}

void main_literals()
{
    using namespace Literals_With_Separators;
    test_01();

    using namespace Literals_Color_Runtime;
    test_02();
    // test_02_with_errors();   // throws exceptions at runtime

    using namespace Literals_Color_CompileTime;
    test_03();
    test_03_with_errors();      // throws errors at compile time
}

// =====================================================================================
// End-of-File
// =====================================================================================
