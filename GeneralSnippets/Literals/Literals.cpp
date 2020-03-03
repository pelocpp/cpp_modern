// =====================================================================================
// std::tuple
// =====================================================================================

#include <iostream>
#include <string>
#include <cstdint>
#include <iomanip>

namespace Literals {

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
            : m_a(a), m_r(r), m_g(g), m_b(b) {}
    };

    std::ostream& operator<< (std::ostream& os, const Color& col) { 

        os << std::uppercase
            << std::hex << std::setw(2) << std::setfill('0') << (int) col.m_r << ":"
            << std::hex << std::setw(2) << std::setfill('0') << (int) col.m_g << ":"
            << std::hex << std::setw(2) << std::setfill('0') << (int) col.m_b << "["
            << std::hex << std::setw(2) << std::setfill('0') << (int) col.m_a << "]";

        return os;
    }

    // literal operator ("cooked" version)
    Color operator"" _col (unsigned long long int value) {

        uint8_t a = (uint8_t) ((value & 0xFF000000) >> 24);
        uint8_t r = (uint8_t)((value & 0x00FF0000) >> 16);
        uint8_t g = (uint8_t)((value & 0x0000FF00) >> 8);
        uint8_t b = (uint8_t)((value & 0xFF0000FF) >> 0);

        return Color(a, r, g, b);
    }

    // literal operator ("raw" version)
    Color operator"" _col(const char*  literal) {

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

            return { (uint8_t) a, (uint8_t) r, (uint8_t) g, (uint8_t) b };
        }

        return {};
    }

    void test_00() {
        Color col(255, 70, 80, 90);
        std::cout << col << std::endl;
    }

    void test_01() {
        Color red = 0x00FF0000_col;
        std::cout << red << std::endl;
        Color magenta = 0x00FF00FF_col;
        std::cout << magenta << std::endl;
        Color yellow = 0x00FFFF00_col;
        std::cout << yellow << std::endl;

        Color unknown = 12345_col;
        std::cout << unknown << std::endl;
    }
}

int main_literals()
{
    using namespace Literals;
    test_01();
    test_01();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
