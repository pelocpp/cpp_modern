// =====================================================================================
// ConstExpr.cpp
// =====================================================================================

module;

#include <cassert>

module modern_cpp:const_expr;

// =====================================================================================
// variables

namespace ConstExprVariables {

    constexpr double Pi = 3.14159265359;

#define          PI   3.14159265359

    static void testVariables() {

        std::println("Pi: {}", Pi);
        std::println("PI: {}", PI);
    }
}

// =====================================================================================
// functions

namespace ConstExprFunctions {

    // ======================================================
    // limit a number in a range or in between two given numbers

    #define   CLAMP(x, lo, hi)      ((x) < (lo) ? (lo) : ((x) > (hi) ? (hi) : (x)))

    static auto clamp = [](auto x, auto lo, auto hi) constexpr {
        return x < lo ? lo : (x > hi ? hi : x);
        }; 

    static void testFunctions_01() {

        constexpr std::size_t a{ 3 };
        constexpr std::size_t b{ 8 };

        constexpr auto value1{ CLAMP(a + b, 0, 10) };
        constexpr auto value2{ clamp(a + b, 0, 10) };
        constexpr auto value3{ clamp(a + b, 5,  8) };
    }
    
    // ======================================================
    // calculate the number multiplied by itself

    #define   SQUARE(x)             x * x

    static constexpr auto square (auto x) {
        return x * x;
    };

    static auto squareLambda = [](auto x) constexpr {
        return x * x;
    };

    static void testFunctions_02() {

        // Note: macros can produce unexpected results

        std::size_t a{ 1 };
        std::size_t b{ 2 };
        std::size_t value{ SQUARE(a + b) };       // value == 5: Wrong result !!!
        assert(value == 5);
    }

    static void testFunctions_03() {

        // Note: constexpr functions don't have side effects !!!

        constexpr std::size_t a{ 1 };
        constexpr std::size_t b{ 2 };
        constexpr auto value{ square(a + b) };
        static_assert(value == 9);                  // correct result !!!

        constexpr double x{ 3.0 };
        constexpr double y{ 4.0 };
        constexpr auto dvalue{ squareLambda(x + y) };
        static_assert(dvalue == 49.0);              // correct result !!!
    }

    static constexpr auto squareOfTwo = square(2);
    static constexpr auto squareOfThree = square(3.0);

    static constexpr auto squareOfFour = squareLambda(4);
    static constexpr auto squareOfFive = squareLambda(5.0);

    // ======================================================
    // swap the values of two variables

    #define   SWAP(a, b)        \
          {                     \
              auto tmp = (a);   \
              (a) = (b);        \
              (b) = tmp;        \
          }

    static auto swap = [](auto& a, auto& b) constexpr {
        auto tmp = a;
        a = b;
        b = tmp;
    };

    // constexpr lambda as a compile-time function template (C++ 20)
    // enforces that both parameters have the same type
    //static auto swap = []<typename T>(T& a, T& b) constexpr {
    //    auto tmp = a;
    //    a = b;
    //    b = tmp;
    //    };

    static void testFunctions_04() {

        std::size_t a{ 1 };
        std::size_t b{ 2 };

        std::println("{} - {}", a, b);
        SWAP(a, b);
        std::println("{} - {}", a, b);
    }

    static void testFunctions_05() {

        std::size_t a{ 1 };
        std::size_t b{ 2 };

        std::println("{} - {}", a, b);
        swap(a, b);
        std::println("{} - {}", a, b);
    }

    // ======================================================

    static void testFunctions() {

        testFunctions_01();
        testFunctions_02();
        testFunctions_03();
        testFunctions_04();
        testFunctions_05();
    }
}

// =====================================================================================
// classes and objects

namespace ConstExprClassesAndObjects {

    class Complex
    {
    private:
        float m_real;
        float m_imag;

    public:
        // c'tors
        constexpr Complex() : m_real{ }, m_imag{ } {}
        constexpr Complex(float real, float imag) : m_real{ real }, m_imag{ imag } {}

        // getter
        constexpr float real() const { return m_real; }
        constexpr float imag() const { return m_imag; }

        // operators
        constexpr Complex operator+ (const Complex& other) const
        {
            float real = m_real + other.m_real;
            float imag = m_imag + other.m_imag;
            return { real, imag };
        }
    };

    static void testComplex()
    {
        constexpr Complex c0{ };
        constexpr Complex c1{ 1.0, 2.0 };
        constexpr Complex c2{ 3.0, 3.0 };

        constexpr float r1{ c1.real() };
        constexpr Complex c3{ c1 + c2 };
        constexpr float r2{ c3.real() };

        // verify 'constness' with the help of disassembly and
        // https://www.h-schmidt.net/FloatConverter/IEEE754de.html
        
        std::println("Real: ", c3.real());
        std::println("Imag: ", c3.imag());

        // verify compile time computing
        static_assert (c1.real() == 1.0, "real part shoud be 1.0");
        static_assert (c3.real() == 4.0, "real part shoud be 4.0");
        static_assert (c3.imag() == 5.0, "imaginary part shoud be 5.0");
    }
}

// =====================================================================================
// dynamic variables

namespace ConstExprDynamicData {

    static constexpr int naiveSum(unsigned int n)
    {
        auto ip{ new int[n] };
        std::iota(ip, ip + n, 1);
        auto tmp{ std::accumulate(ip, ip + n, 0) };
        delete[] ip;
        return tmp;
    }

    static void testDynamicData()
    {
        constexpr int sum{ naiveSum(10) };
        std::println("Sum from 1 up to 10: {}", sum);
    }
}

// =====================================================================================
// example: compile-time table of power numbers

namespace ConstExprPow {

    constexpr size_t TableSize = 5;
    constexpr size_t Factor = 4;

    template<size_t F>
    constexpr auto powerTable = [] {

        std::array<size_t, TableSize> table = {};

        size_t index{ 1 };
        for (size_t& elem : table) {

            size_t tmp{ 1 };
            for (size_t i{}; i != F; ++i) {
                tmp *= index;
            }

            elem = tmp;
            ++index;
        }

        return table;
    } ();

    static constexpr size_t sumUpPowerTable()
    {
        static_assert (powerTable<Factor>[0] == 1, "Value should be ");
        static_assert (powerTable<Factor>[1] == 16, "Value should be ");
        static_assert (powerTable<Factor>[2] == 81, "Value should be ");
        static_assert (powerTable<Factor>[3] == 256, "Value should be ");
        static_assert (powerTable<Factor>[4] == 625, "Value should be ");

        size_t total{};

        for (size_t i{}; i != TableSize; ++i) {
            total += powerTable<Factor>[i];
        }

        return total;
    }

    static void testPower_01()
    {
        constexpr size_t total{ sumUpPowerTable() };
        static_assert (total == 979, "Sum should be 979");
        std::println("Total: ", total);
    }

    static void testPower_02()
    {
        int index = 1;
        for (size_t elem : powerTable<Factor>) {
            std::println("{:02}: {}", index++, elem);
        }

        constexpr size_t total = sumUpPowerTable();
        std::println("Total: {}", total);
    }

    static void testPower()
    {
        testPower_01();
        testPower_02();
    }
}

void main_constexpr()
{
    ConstExprVariables::testVariables();
    ConstExprFunctions::testFunctions();
    ConstExprClassesAndObjects::testComplex();
    ConstExprDynamicData::testDynamicData();
    ConstExprPow::testPower();
}

// =====================================================================================
// End-of-File
// =====================================================================================
