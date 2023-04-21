// =====================================================================================
// GenericLambdas.cpp // Generic Lambdas
// =====================================================================================

module modern_cpp:generic_lambdas;

namespace GenericLambdas {

    // -------------------------------------------------------------------

    auto lambda = [](auto x, int y) {
        std::cout << "x=" << x << ", y=" << y << std::endl;
    };

    void test_01()
    {
        lambda(1, 100);
        lambda(2.5, 101);
        lambda(std::string{"ABC"}, 102);
        lambda("XYZ", 103);
    }

    struct Lambda
    {
        template <typename T>
        void operator() (T x, int y) {
            std::cout << "x=" << x << ", y=" << y << std::endl;
        }
    };

    void test_02()
    {
        struct Lambda instance;
        instance(1, 200);
        instance(2.5, 201);
        instance(std::string{ "ABC" }, 202);
        instance("XYZ", 203);
    }

    auto lambdaTwice = [](auto x, auto y) {
        std::cout << "x=" << x << ", y=" << y << std::endl;
    };

    struct LambdaTwice
    {
        template <typename T, typename U>
        void operator() (T x, U y) {
            std::cout << "x=" << x << ", y=" << y << std::endl;
        }
    };

    void test_03()
    {
        lambdaTwice(1, 300);
        lambdaTwice(2.5, 301);
        lambdaTwice(std::string{ "ABC" }, 302);
        lambdaTwice("XYZ", 303);

        struct LambdaTwice instance;
        instance(1, 400);
        instance(2.5, 401);
        instance(std::string{ "ABC" }, 402);
        instance("XYZ", 403);
    }

    // -------------------------------------------------------------------

    void test_04()
    {
        // define a generic lambda
        auto isGreaterThanFifty = [](const auto& n) { return n > 50; };

        std::vector<int> intValues{ 44, 65, 22, 77, 2 };

        // use generic lambda with a vector of integers
        auto it1 = std::find_if(
            std::begin(intValues),
            std::end(intValues),
            isGreaterThanFifty
        );
        if (it1 != std::end(intValues)) {
            std::cout << "Found a value: " << *it1 << std::endl;
        }

        std::vector<double> doubleValues{ 24.5, 75.5, 12.5, 87.5, 12.5 };

        // use exactly the *same* generic lambda with a vector of doubles
        auto it2 = std::find_if(
            std::begin(doubleValues),
            std::end(doubleValues),
            isGreaterThanFifty
        );
        if (it2 != std::end(doubleValues)) {
            std::cout << "Found a value: " << *it2 << std::endl;
        }
    }

    template <typename T>
    bool isGreaterThanFiftyEx(const T& n)
    {
        return n > 50;
    };

    void test_05()
    {
        std::vector<int> intValues{ 44, 65, 22, 77, 2 };

        // use template function with a vector of integers
        auto it1 = std::find_if(
            std::begin(intValues),
            std::end(intValues),
            isGreaterThanFiftyEx<int>
        );
        if (it1 != std::end(intValues)) {
            std::cout << "Found a value: " << *it1 << std::endl;
        }

        std::vector<double> doubleValues{ 24.5, 75.5, 12.5, 87.5, 12.5 };

        // use exactly the *same* template function with
        // another specialization with a vector of doubles
        auto it2 = std::find_if(
            std::begin(doubleValues),
            std::end(doubleValues),
            isGreaterThanFiftyEx<double>
        );
        if (it2 != std::end(doubleValues)) {
            std::cout << "Found a value: " << *it2 << std::endl;
        }
    }

    // ---------------------------------------------------------------------

    void test_06()
    {
        auto l1 = [](int a) { return a + a; };             // C++ 11, regular lambda

        auto l2 = [](auto a) { return a + a; };            // C++ 14, generic lambda

        auto l3 = []<typename T>(T a) { return a + a; };   // C++ 20, template lambda

        auto v1 = l1(42);                       // Ok
        // auto v2 = l1(42.0);                  // Warning
        // auto v3 = l1(std::string{ "42" });   // Error

        auto v5 = l2(42);                       // Ok
        auto v6 = l2(42.0);                     // Ok
        auto v7 = l2(std::string{ "42" });      // Ok
        
        auto v8 = l3(42);                       // Ok
        auto v9 = l3(42.0);                     // Ok
        auto v10 = l3(std::string{ "42" });     // Ok
    }

    void test_07()
    {
        auto l1 = [](int a, int b) { return a + b; };          // C++ 11, regular lambda

        auto l2 = [](auto a, auto b) { return a + b; };        // C++ 14, generic lambda

        auto l3 = []<typename T, typename U>(T a, U b) {       // C++ 20, template lambda
            return a + b; 
        };

        auto v1 = l1(42, 1);                                       // Ok
        // auto v2 = l1(42.0, 1.0);                                // Warning
        // auto v3 = l1(std::string{ "42" }, '1');                 // Error

        auto v4 = l2(42, 1);                                       // Ok
        auto v5 = l2(42.0, 1);                                     // Ok
        auto v6 = l2(std::string{ "42" }, '1');                    // Ok
        auto v7 = l2(std::string{ "42" }, std::string{ "1" });     // Ok

        auto v8 = l3(42, 1);                                       // Ok
        auto v9 = l3(42.0, 1);                                     // Ok
        auto v10 = l3(std::string{ "42" }, '1');                   // Ok
        auto v11 = l3(std::string{ "42" }, std::string{ "42" });   // Ok

    }

    void test_08()
    {
        auto l5 = []<typename T>(T a, T b) { return a + b; };      // C++ 20, template lambda

        auto v1 = l5(42, 1);                                       // Ok
        // auto v2 = l5(42, 1.0);                                  // Error
        auto v4 = l5(42.0, 1.0);                                   // Ok
        // auto v5 = l5(42, false);                                // Error
        auto v6 = l5(std::string{ "42" }, std::string{ "1" });     // Ok
        // auto v6 = l5(std::string{ "42" }, '1');                 // Error
    }

    void test_09()
    {
        auto l6 = [](auto a, decltype(a) b) { return a + b; };      // C++ 14, using decltype

        auto v1 = l6(42.0, 1);                                     // Ok
        // auto v2 = l6(42, 1.0);                                  // Warning
        // auto v3 = l6(std::string{ "42" }, '1');                 // Error
    }

    // -------------------------------------------------------------------

    void foo(const std::string& s) {
        std::cout << "Signature: const&" << std::endl;
    }

    void foo(std::string&& s) {
        std::cout << "Signature: &&" << std::endl;
    }

    auto callingFoo = [](auto&& s) {
        std::cout << "Calling foo(): " << s;
        foo(std::forward<decltype(s)>(s));
    };

    void test_10()
    {
        const std::string str{ "Hello World with LValue - " };
        callingFoo(str);
        callingFoo("Hello World with RValue - ");
    }

    // -------------------------------------------------------------------
    
    void test_11()
    {
        // power recursive function
        std::function<int(int, int)> power;

        power = [&] (int base, int exp) {
            return exp == 0 ? 1 : base * power(base, exp - 1);
        };

        std::cout << power(2, 10) << std::endl; // 2^10 = 1024
    }

    void test_12()
    {
        // factorial recursive function
        std::function<int(int)> factorial;

        factorial = [&] (int n) {
            if (n < 2) {
                return 1;
            }
            else {
                return n * factorial(n - 1);
            }
        };

        std::cout << factorial(5) << std::endl; // 120
    }

    void test_13()
    {
        // power recursive lambda function
        auto power = [] (auto self, auto base, int exp) -> decltype(base) {
            return exp == 0 ? 1 : base * self(self, base, exp - 1);
        };

        std::cout << power(power, 2, 10) << std::endl;    // 2^10 = 1024

        std::cout << power(power, 2.71828, 10);           // e^10 = 22026.3
    }

    void test_14()
    {
        // factorial recursive lambda function
        auto factorial = [] (auto f, int const n) {

            if (n < 2) {
                return 1;
            }
            else {
                return n * f(f, n - 1);
            }
        };

        std::cout << factorial (factorial, 5) << std::endl; // 120
    }

    // ---------------------------------------------------------------------

    void test_15() {

        // Example demonstrating so called 'Currying':

        // This means that we take a function that can accept some parameters
        // and store it in another function object, which accepts *fewer* parameters.

        // In our example, we define a 'plusTen' function which accepts a single parameter.
        // This parameter is forwarded to the 'plus' function.
        // The second parameter equals 10, which is being saved in the function object:

        auto plus = [](auto l, auto r) { return l + r; };

        auto plusTen = [plus](auto x) { return plus(10, x); };

        std::cout << plusTen(5) << std::endl;
    }

    // ---------------------------------------------------------------------

    // correlations between templates and lambdas
    template <typename T, typename U>
    auto add = [](const T& t, const U& u) -> decltype (t + u)
    {
        return t + u;
    };

    void test_16() {

        int n = 1;
        double d = 2.7;

        auto result1 = add<int, double>(n, d);
        std::cout << result1 << std::endl;
    }

    // ---------------------------------------------------------------------
}

void main_generic_lambdas()
{
    using namespace GenericLambdas;
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
    test_15();
    test_16();
}

// =====================================================================================
// End-of-File
// =====================================================================================
