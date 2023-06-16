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
        friend constexpr Complex operator+(const Complex& x, const Complex& y)
        {
            float real = x.real() + y.real();
            float imag = x.imag() + y.imag();
            return Complex{ real, imag };
        }
    };

    void testComplex()
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

namespace ConstExprComplexTemplate {

    template <typename T>
    class Complex
    {
    private:
        T m_real;
        T m_imag;

    public:
        // c'tors
        constexpr Complex() : m_real{ }, m_imag{ } {}
        constexpr Complex(T real, T imag) : m_real{ real }, m_imag{ imag } {}

        // getter
        constexpr T real() const { return m_real; }
        constexpr T imag() const { return m_imag; }

        // operators
        friend constexpr Complex<T> operator+(const Complex<T>& x, const Complex<T>& y)
        {
            return Complex<T>{ x.real() + y.real(), x.imag() + y.imag() };
        }
    };

    void testComplexTemplate()
    {
        constexpr Complex<float> c0{ };
        constexpr Complex<float> c1{ 10.0, 20.0 };
        constexpr Complex<float> c2{ 30.0, 30.0 };

        constexpr float r1 = c1.real();
        constexpr Complex<float> c3 = c1 + c2;
        constexpr float r2 = c3.real();

        std::cout << "Real: " << c3.real() << std::endl;
        std::cout << "Imag: " << c3.imag() << std::endl;

        // verify compile time computing
        static_assert (c1.real() == 10.0, "real part shoud be 10.0");
        static_assert (c3.real() == 40.0, "real part shoud be 40.0");
        static_assert (c3.imag() == 50.0, "imaginary part shoud be 50.0");
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

    constexpr size_t sumUpPowerTable()
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

    void testPower_01()
    {
        constexpr size_t total{ sumUpPowerTable() };
        static_assert (total == 979, "Sum should be 979");
        std::cout << "Total: " << total << std::endl;
    }

    void testPower_02()
    {
        int index = 0;
        for (size_t elem : powerTable<Factor>) {
            std::cout << "    " << ++index << ": " << elem << std::endl;
        }

        constexpr size_t total = sumUpPowerTable();
        std::cout << "Total: " << total << std::endl;
    }

    void testPower()
    {
        testPower_01();
        testPower_02();
    }
}

namespace ConstExprCollatz {

    constexpr int collatz(int index)
    {
        return (index % 2 == 0) ? index / 2 : index * 3 + 1;
    }

    constexpr auto collatzLambda = [](int index)
    {
        return (index % 2 == 0) ? index / 2 : index * 3 + 1;
    };

    // class definition (type which holds sequences)
    template <int ... NS>
    struct CollatzSequence
    {
        static constexpr std::array<int, sizeof... (NS)> elements = { NS ... };
    };

    // helper class template declaration
    template <int ... NS>
    struct SequenceHelper;

    // helper class template: recursion case
    template <int I, int ... NS>
    struct SequenceHelper<I, NS...>
    {
        static constexpr int next = collatz(I);
        using type = typename SequenceHelper<next, next, NS ...>::type;
    };

    // recursion termination
    template <int ... NS>
    struct SequenceHelper<1, NS ...>
    {
        using type = CollatzSequence<NS ...>;
    };

    template <int N>
    using makeCollatzSequence = typename SequenceHelper<N>::type;

    void testCollatz()
    {
        auto seq1 = makeCollatzSequence<13>{};
        //CollatzSequence seq2 = makeCollatzSequence<9>{};
        auto sequence = seq1.elements;

        std::cout << "Size: " << sequence.size() << std::endl;

        std::for_each(std::rbegin(sequence), std::rend(sequence), [](const int elem) {
            std::cout << "   Element: " << elem << std::endl;
        });
    }
}

namespace ConstExprCollatzInheritance {

    constexpr int collatz(int index) {
        return (index % 2 == 0) ? index / 2 : index * 3 + 1;
    }

    // class template: recursion case
    template<size_t START, size_t ... D>
    struct Helper : Helper<collatz(START), D ..., collatz(START)> { };

    // recursion termination
    template<size_t ... D>
    struct Helper<1, D ...>
    {
        static constexpr std::array<size_t, sizeof ... (D)> table = { D... };
    };

    auto squaresTable = Helper<13>::table;

    void testCollatzInheritance()
    {
        std::cout << "Size: " << squaresTable.size() << std::endl;

        for (size_t elem : squaresTable) {
            std::cout << "   Element: " << elem << std::endl;
        }
    }
}

void main_constexpr()
{
    ConstExprComplex::testComplex();
    ConstExprComplexTemplate::testComplexTemplate();
    ConstExprPow::testPower();
    ConstExprCollatz::testCollatz();
    ConstExprCollatzInheritance::testCollatzInheritance();
}

// =====================================================================================
// End-of-File
// =====================================================================================
