// =====================================================================================
// User defined literals - Older versions
// =====================================================================================

#include <iostream>
#include <string>
#include <cstdint>
#include <iomanip>

namespace Literals_Color_Runtime_Older_Version {

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
            << std::hex << std::setw(2) << std::setfill('0') << (int)col.m_r << ":"
            << std::hex << std::setw(2) << std::setfill('0') << (int)col.m_g << ":"
            << std::hex << std::setw(2) << std::setfill('0') << (int)col.m_b;

        return os;
    }

    // literal operator ("cooked" version)
    Color operator"" _rgb(unsigned long long int value) {

        if (value > 0xFFFFFF) {
            throw std::runtime_error("literal too large");
        }

        uint8_t r{ static_cast<uint8_t>((value & 0x00FF0000) >> 16) };
        uint8_t g{ static_cast<uint8_t>((value & 0x0000FF00) >> 8) };
        uint8_t b{ static_cast<uint8_t>((value & 0x000000FF) >> 0) };

        return { r, g, b };
    }

    // literal operator ("raw" version)
    Color operator"" _rgb(const char* literal, size_t) {

        // tiny implementation - just parsing hexadecimal format
        std::string arg(literal);
        if (arg.size() == 2 /* 0x */ + 6 /* FF FF FF */) {

            std::string rs{ arg.substr(2, 2) };
            std::string gs{ arg.substr(4, 2) };
            std::string bs{ arg.substr(6, 2) };

            uint8_t r{ static_cast<uint8_t>(std::stoi(rs, nullptr, 16)) };
            uint8_t g{ static_cast<uint8_t>(std::stoi(gs, nullptr, 16)) };
            uint8_t b{ static_cast<uint8_t>(std::stoi(bs, nullptr, 16)) };

            // note: braced-init-list syntax
            return { r, g, b };
        }

        // note: braced-init-list syntax
        return {};
    }

    void test_02() {
        Color red = 0xFF0000_rgb;
        std::cout << red << std::endl;
        Color magenta = 0xFF00FF_rgb;
        std::cout << magenta << std::endl;
        Color yellow = 0xFFFF00_rgb;
        std::cout << yellow << std::endl;

        Color unknown = 12345_rgb;
        std::cout << unknown << std::endl;
    }

    void test_02_with_errors() {
        // value outside rgb range
        // Color col1 = 0x1FFFFFF_rgb;
        // std::cout << col1 << std::endl;

        // illegal hexadecimal digit
        // Color col2 = "0x00GG00"_rgb;
        // std::cout << col2 << std::endl;
    }
}

namespace Literals_Color_CompileTime_Older_Version {

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
    constexpr Color operator"" _rgb(unsigned long long int value) {

        if (value > 0xFFFFFF) {
            throw std::logic_error("literal too large");
        }

        uint8_t r{ static_cast<uint8_t>((value & 0x00FF0000) >> 16) };
        uint8_t g{ static_cast<uint8_t>((value & 0x0000FF00) >> 8) };
        uint8_t b{ static_cast<uint8_t>((value & 0x000000FF) >> 0) };

        return { r, g, b };
    }

    constexpr size_t length(const char*);
    constexpr size_t hexstoi(const char*);

    // literal operator ("raw" version)
    constexpr Color operator"" _rgb(const char* literal, size_t) {

        // tiny implementation - just parsing hexadecimal format
        size_t len{ length(literal) };
        if (len == 2 /* 0x */ + 6 /* FF FF FF */) {

            char ar[3] = {};
            char ag[3] = {};
            char ab[3] = {};

            ar[0] = literal[2];
            ar[1] = literal[3];
            ag[0] = literal[4];
            ag[1] = literal[5];
            ab[0] = literal[6];
            ab[1] = literal[7];

            uint8_t r = static_cast<uint8_t>(hexstoi(ar));
            uint8_t g = static_cast<uint8_t>(hexstoi(ag));
            uint8_t b = static_cast<uint8_t>(hexstoi(ab));

            return { r, g, b };
        }

        return {};
    }

    // C++ 14 (recursive function)
    constexpr size_t length_(const char* str, size_t current_len = 0)
    {
        return *str == '\0'
            ? current_len  // end of recursion
            : length_(str + 1, current_len + 1);
    }

    // C++ 17
    constexpr size_t length(const char* str)
    {
        int len{};
        while (*str++ != '\0') {
            ++len;
        }
        return len;
    }

    constexpr bool isHex(char ch)
    {
        if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f')) {
            return true;
        }

        return false;
    }

    constexpr uint8_t hex2int(char ch)
    {
        if (!isHex(ch)) {
            throw std::logic_error("illegal hexadecimal digit");
        }

        // transform hex character to 4-bit equivalent number
        uint8_t byte = ch;
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

    constexpr size_t hexstoi(const char* str)
    {
        int value{};
        while (*str != '\0') {
            // get current character, then increment
            uint8_t byte = hex2int(*str);
            ++str;

            // shift 4 to make space for new digit, and add the 4 bits of the new digit 
            value = (value << 4) | (byte & 0xF);
        }
        return value;
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
