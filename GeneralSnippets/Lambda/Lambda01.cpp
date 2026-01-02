// =====================================================================================
// Lambda01.cpp // Lambda Methods
// =====================================================================================

module modern_cpp:lambda;

namespace Lambdas {

    static bool compare (int n1, int n2) {
        return n1 < n2;
    }

    class Comparer
    {
    private:
        bool m_flag;

    public:
        Comparer() : m_flag{ true } {}
        Comparer(bool flag) : m_flag{ flag } {}

        bool operator() (int n1, int n2) const {
            return (m_flag) ? n1 < n2 : n1 > n2;
        }
    };

    // =====================================================================================

    static void test_00()
    {
        Comparer obj{ false };

        bool result{ obj(1, 2) };

        std::cout << std::boolalpha << result << std::endl;
    }

    // =====================================================================================

    static void test_01()
    {
        std::vector<int> vec{ 5, 6, 4, 1, 3, 2, 7, 8 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(
            vec.begin(),
            vec.end(),
            compare
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    // =====================================================================================

    static void test_02()
    {
        std::vector<int> vec{ 5, 6, 4, 1, 3, 2, 7, 8 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(
            vec.begin(),
            vec.end(),
            Comparer{}  // Comparer{ false }
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    // =====================================================================================

    static void test_03()
    {
        // local class within function possible
        class LocalComparer
        {
        private:
            bool m_flag;

        public:
            LocalComparer() : m_flag{ true } {}
            LocalComparer(bool flag) : m_flag{ flag } {}

            bool operator() (int n1, int n2) const {
                return (m_flag) ? n1 < n2 : n1 > n2;
            }
        };

        std::vector<int> vec{ 5, 6, 4, 1, 3, 2, 7, 8 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(
            vec.begin(),
            vec.end(),
            LocalComparer{}  // LocalComparer{ false }
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    // =====================================================================================

    static void test_04() {

        std::vector<int> vec{ 50, 90, 10, 30, 70, 80 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(
            vec.begin(),
            vec.end(),
            [] (int n1, int n2) { return n1 < n2; }
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    // =====================================================================================

    static void test_05() {

        // shortest lambda on earth: no parameters, capturing and doing nothing
        auto nothing{ [] {} };
        nothing();

        // c'tor notation
        auto itsOne{ [] { return 1; } };
        auto itsTwo{ [] { return 2; } };
        std::cout << itsOne() << ", " << itsTwo() << std::endl;
    }

    static void test_06() {

        // defining a lambda without 'auto'
        std::function<int(int, int, int)> lambdaWithThreeParams {
            [] (int x, int y, int z) {
                return x + y + z;
            }
        };

        std::cout << lambdaWithThreeParams(5, 6, 7) << std::endl;
    }

    static void test_07() {

        // defining new variables in the lambda capture:
        // we can declare a new variable that is only visible
        // in the scope of the lambda: We do so by defining a variable
        // in the lambda-capture without specifying its type:

        // lambda with variable definition
        auto lambda = [variable = 10] () { return variable; };
        std::cout << lambda() << std::endl;

        // Captures default to 'const value':
        // The mutable keyword removes the 'const' qualification from all captured variables
        auto counter = [count = 50] () mutable { 
            ++count; 
            return count;
        };

        for (std::size_t i{}; i < 5; ++i) {
            std::cout << counter() << " ";
        }
        std::cout << std::endl;
    }

    static void test_08() {

        int n = 1;
        int m = 2;

        auto l1 = [=] {
            std::cout << "Copy:      " << n << " " << m << std::endl;
        };

        auto l2 = [&] {
            std::cout << "Reference: " << n << " " << m << std::endl;
        };

        auto l3 = [&, m] {
            std::cout << "Both:      " << n << " " << m << std::endl;
        };

        auto l4 = [=, &m] {
            std::cout << "More both: " << n << " " << m << std::endl;
        };

        n = 3;
        m = 4;

        l1();
        l2();
        l3();
        l4();
    }

    static auto test_09_helper_a() {

        int n = 1;
        int m = 2;

        auto lambda = [=] {
            std::cout << "Copy:      " << n << " " << m << std::endl;
        };

        return lambda;
    }

    static auto test_09_helper_b() {

        int n = 1;
        int m = 2;

        auto lambda = [&] {
            std::cout << "Reference: " << n << " " << m << std::endl;
        };

        return lambda;  // I would't do this never ever :-)
    }

    static void test_09() {

        auto outerLambda1 = test_09_helper_a();
        auto outerLambda2 = test_09_helper_b();

        outerLambda1();
        outerLambda2();
    }

    static void test_10() {

        // demonstrating 'noexcept'
        auto itsOne([] () noexcept { return 1; });
        auto itsTwo = [] () noexcept { return 2; };
        std::cout << itsOne() << ", " << itsTwo() << std::endl;
    }

    static void test_11() {

        // IIFE - Immediately Invoked Functional Expression:
        // Inline-definition and direct invocation of lambda function:
        
        std::cout << [](int l, int r) { return l + r; } (11, 12) << std::endl;

        // Use case for IIFE:
        // This kind of expression might be useful when you have
        // a complex initialization of a const  object:

        constexpr auto ConstValue = [] () constexpr {
            /* several lines of code ... - "very complex" computation */
            return 123;
        } ();

        std::cout << "Const Value: " << ConstValue << std::endl;
    }

    // ======================================================
    // Another IIFE Examples:
    // Lambda is defined 'constexpr' - some concrete values are computed

    auto power = [] (int m, std::size_t n) constexpr {

        auto result = m;
        for (std::size_t i{ 1 }; i != n; ++i) {
            result *= m;
        }
        return result;
    };

    template <typename T>
    auto powerGeneric = [](T m, std::size_t n) constexpr {

        T result = m;
        for (std::size_t i{ 1 }; i != n; ++i) {
            result *= m;
        }
        return result;
    };

    auto powerAuto = [](auto m, std::size_t n) constexpr {

        auto result = m;
        for (std::size_t i{ 1 }; i != n; ++i) {
            result *= m;
        }
        return result;
    };

    static void test_12() {

        // IIFE - Immediately Invoked Functional Expression:
        // some real-world examples

        constexpr auto twoTimesTen = power(2, 10);
        constexpr auto fiveTimesTen = power(5, 10);

        constexpr auto threeTimesThree = powerGeneric<float>(3.0f, 3);
        constexpr auto fiveTimesFive = powerGeneric<double>(5.0, 5);

        constexpr auto twoTimesThree = powerAuto(2.0f, 3);
        constexpr auto fiveTimesThree = powerAuto(5.0, 3);
    }

    // ======================================================
    // More IIFE Examples:
    // Parameters of the 'constexpr' callable (function, lambda)
    // should have the same data type

    // works for int arguments
    auto minimum = [](int n, int m) constexpr {
        return (n <= m) ? n : m;
    };

    // works for arguments of different type (?!?)
    // type of the ternary ?: expression is
    // the common type of its second and third argument
    auto minimumAuto = [](auto n, auto m) constexpr {
        return (n <= m) ? n : m;
    };

    // works for arguments of different type (?!?)
    // type of the ternary ?: expression is
    // the common type of its second and third argument
    auto minimumMoreAuto = [](auto n, auto m) constexpr {

        if (n <= m) {
            return n;
        }
        else {
            return m;
        }
    };

    // works for arbitrary arguments of the same type (!)
    template <typename T>
    auto minimumGeneric = [](T n, T m) constexpr {
        return (n <= m) ? n : m;
    };

    // works for arbitrary arguments of the same type (!)
    // different syntax
    auto minimumMoreGeneric = []<typename T>(T n, T m) constexpr {
        return (n <= m) ? n : m;
    };

    static void test_13() {

        // IIFE - Immediately Invoked Functional Expression:
        // some more real-world examples: regarding argument data types

        constexpr auto value1 = minimum(10, 20);

        constexpr auto value2 = minimumAuto(10.0, 5.0);
        constexpr auto value3 = minimumAuto(11.11, 5.5f);             // Why does this compile, different argument types (?)

        constexpr auto value4 = minimumMoreAuto(11.11, 5.5); 
        // constexpr auto value5 = minimumMoreAuto(11.11, 5.5f);      // does NOT compile (!)

        constexpr auto value6 = minimumAuto(11.11, 5.5f);             // Why does this compile (?)

        constexpr auto value7 = minimumGeneric<int>(30, 40);
        constexpr auto value8 = minimumGeneric<double>(30.0f, 40.0);  // Compiles, but different argument types (!)

        constexpr auto value9 = minimumMoreGeneric(60, 50);
        // constexpr auto value10 = minimumMoreGeneric(50.0f, 60.0);  // does NOT compile (!), compare with 'minimumGeneric' (?!?!)
    }

    // ======================================================
    // Feature: Generalized Lambda Capture
    // Lambdas and Move-Semantics of Closure Variables

    static void test_14() {

        // Feature: Generalized Lambda Capture

        class SampleClass
        {
        public:
            void doSomething() { std::println("Doing Something"); };
        };

        std::unique_ptr<SampleClass> ptr { 
            std::make_unique<SampleClass>() 
        };

        // Does not compile: by-value capture with move-only type (!)
        // auto lambda = [=] () { ptr->doSomething(); };

        // Compiles: by-reference capture with move-only type (!)
        auto lambda = [&] () { ptr->doSomething(); };

        // How about by-move capture?
        // Instead of adding it, C++14 introduced the "Generalized Lambda Capture",
        // also known as "Init Capture":

        auto lambda2 = [ptrSampleClass = std::move(ptr)] () {
            ptrSampleClass->doSomething();
        };

        lambda2();

        // Note:
        // We are allowed to keep the name of the variable 'ptr' the same inside the lambda:

        ptr = std::make_unique<SampleClass>();

        auto lambda3 = [ptr = std::move(ptr)]() {
            ptr->doSomething();
        };

        lambda3();
    }
}

void main_lambdas()
{
    using namespace Lambdas;
    test_00();
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
    test_07();
    test_08();
    test_09();
    test_10();
    test_11();
    test_12();
    test_13();
    test_14();
}

// =====================================================================================
// End-of-File
// =====================================================================================
