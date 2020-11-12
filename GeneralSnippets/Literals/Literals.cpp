// =====================================================================================
// user defined literals
// =====================================================================================

#include <iostream>
#include <string>
#include <cstdint>
#include <iomanip>

namespace Literals {

    void test_01() {

        // binary, octal and hexadecimal literals
        // (including single quotation mark as separator)

        long decval = 1'048'576;        // groups of three digits
        long hexval = 0x10'0000;        // four digits
        long octval = 00'04'00'00'00;   // two digits
        long binval = 0b100'000000'000000'000000;   //six digits

        std::cout << decval << std::endl;
        std::cout << hexval << std::endl;
        std::cout << octval << std::endl;
        std::cout << binval << std::endl;
    }

    class Color {
        friend std::ostream& operator<< (std::ostream&, const Color&);

    private:
        uint8_t m_a;
        uint8_t m_r;
        uint8_t m_g;
        uint8_t m_b;

    public:
        Color()
            : m_a{}, m_r{}, m_g{}, m_b{} {}

        Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
            : m_a{ a }, m_r{ r }, m_g{ g }, m_b{ b } {}
    };

    std::ostream& operator<< (std::ostream& os, const Color& col) { 

        os << std::uppercase
            << std::hex << std::setw(2) << std::setfill('0') << (int) col.m_r << ":"
            << std::hex << std::setw(2) << std::setfill('0') << (int) col.m_g << ":"
            << std::hex << std::setw(2) << std::setfill('0') << (int) col.m_b << " ["
            << std::hex << std::setw(2) << std::setfill('0') << (int) col.m_a << "]";

        return os;
    }

    // literal operator ("cooked" version)
    Color operator"" _color (unsigned long long int value) {

        uint8_t a = (uint8_t) ((value & 0xFF000000) >> 24);
        uint8_t r = (uint8_t) ((value & 0x00FF0000) >> 16);
        uint8_t g = (uint8_t) ((value & 0x0000FF00) >> 8);
        uint8_t b = (uint8_t) ((value & 0x000000FF) >> 0);

        return Color(a, r, g, b);
    }

    // literal operator ("raw" version)
    Color operator"" _color(const char*  literal) {

        /* tiny implementation - just parsing hexadecimal format
        */
        std::string arg(literal);
        if (arg.size() == 2 /* 0x */  + 8 /* FF FF FF FF */) {

            std::string as = arg.substr(2, 2);
            std::string rs = arg.substr(4, 2);
            std::string gs = arg.substr(6, 2);
            std::string bs = arg.substr(8, 2);

            int a = std::stoi(as, nullptr, 16);
            int r = std::stoi(rs, nullptr, 16);
            int g = std::stoi(gs, nullptr, 16);
            int b = std::stoi(bs, nullptr, 16);

            // Note: braced-init-list syntax: 
            // "return an object of the function's return type initialized with an corresponding c'tor":
            // Short hand for a new instance of the methods return type

            return { (uint8_t) a, (uint8_t) r, (uint8_t) g, (uint8_t) b };
        }

        // Note: braced-init-list syntax: 
        // "return an object of the function's return type initialized with default c'tor"
        // Short hand for a new instance of the methods return type

        return {};
    }

    void test_02() {
        Color col(255, 70, 80, 90);
        std::cout << col << std::endl;
    }

    void test_03() {
        Color red = 0x00FF0000_color;
        std::cout << red << std::endl;
        Color magenta = 0x00FF00FF_color;
        std::cout << magenta << std::endl;
        Color yellow = 0x00FFFF00_color;
        std::cout << yellow << std::endl;

        Color unknown = 12345_color;
        std::cout << unknown << std::endl;
    }
}

void main_literals()
{
    using namespace Literals;
    test_01();
    test_02();
    test_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
