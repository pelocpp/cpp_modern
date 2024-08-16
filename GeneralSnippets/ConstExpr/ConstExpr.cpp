// =====================================================================================
// ConstExpr.cpp
// =====================================================================================

module modern_cpp:const_expr;

namespace ConstExprComplex {

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

        constexpr float r1 = c1.real();
        constexpr Complex c3 = c1 + c2;
        constexpr float r2 = c3.real();

        // verify 'constness' with the help of disassembly and
        // https://www.h-schmidt.net/FloatConverter/IEEE754de.html
        
        std::cout << "Real: " << c3.real() << std::endl;
        std::cout << "Imag: " << c3.imag() << std::endl;

        // verify compile time computing
        static_assert (c1.real() == 1.0, "real part shoud be 1.0");
        static_assert (c3.real() == 4.0, "real part shoud be 4.0");
        static_assert (c3.imag() == 5.0, "imaginary part shoud be 5.0");
    }
}

namespace ConstExprDynamicData {

    static constexpr int naiveSum(unsigned int n) {
        auto p = new int[n];
        std::iota(p, p + n, 1);
        auto tmp = std::accumulate(p, p + n, 0);
        delete[] p;
        return tmp;
    }

    static void testDynamicData()
    {
        constexpr int sum = naiveSum(5);
    }
}

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
        std::cout << "Total: " << total << std::endl;
    }

    static void testPower_02()
    {
        int index = 0;
        for (size_t elem : powerTable<Factor>) {
            std::cout << "    " << ++index << ": " << elem << std::endl;
        }

        constexpr size_t total = sumUpPowerTable();
        std::cout << "Total: " << total << std::endl;
    }

    static void testPower()
    {
        testPower_01();
        testPower_02();
    }
}

void main_constexpr()
{
    ConstExprComplex::testComplex();
    ConstExprDynamicData::testDynamicData();
    ConstExprPow::testPower();
}

// =====================================================================================
// End-of-File
// =====================================================================================
