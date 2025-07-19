// =====================================================================================
// GenericFunctions.cpp // Generic Functions (incl. Lambdas)
// =====================================================================================

module modern_cpp:generic_functions;

namespace GenericFunctions {

    // ---------------------------------------------------------------------------------
    // generic function

    static void function(auto x, int y) {
        std::cout << "x=" << x << ", y=" << y << std::endl;
    };

    static void test_01()
    {
        function(1, 123);
        function(2.5, 123);
        function(std::string{ "ABC" }, 123);

        // compiles too
        function<int>(1, 123);
        function<double>(2.5, 123);
        function<std::string>(std::string{ "ABC" }, 123);
    }

    // ---------------------------------------------------------------------------------
    // generic function - how the compiler sees them

    template<typename T>
    static void Function(T x, int y)
    {
        std::cout << "x=" << x << ", y=" << y << std::endl;
    }

    template<>
    void Function<int>(int x, int y)
    {
        std::cout << "x=" << x << ", y=" << y << std::endl;
    }

    template<>
    void Function<double>(double x, int y)
    {
        std::cout << "x=" << x << ", y=" << y << std::endl;
    }

    template<>
    void Function<std::string>(std::string x, int y)
    {
        std::cout << "x=" << x << ", y=" << y << std::endl;
    }

    static void test_02()
    {
        Function<int>(1, 123);
        Function<double>(123.456, 123);
        Function<std::string>(std::string{ "ABC" }, 123);
    }

    // ---------------------------------------------------------------------------------
    // generic function - several 'auto' parameters

    static void functionTwice(auto x, auto y) {
        std::cout << "x=" << x << ", y=" << y << std::endl;
    };

    // ---------------------------------------------------------------------------------
    // generic function - several 'auto' parameters - how the compiler sees them

    template<typename T, typename U>
    static void FunctionTwice(T x, U y)
    {
        std::cout << "x=" << x << ", y=" << y << std::endl;
    }

    static void test_03()
    {
        functionTwice(1, 2);
        functionTwice(123l, 456ll);
        functionTwice(123.456, 123.456F);

        FunctionTwice(1, 2);
        FunctionTwice(123l, 456ll);
        FunctionTwice(123.456, 123.456F);

        FunctionTwice<int, int>(1, 2);
        FunctionTwice<long, long long>(123l, 456ll);
        FunctionTwice<double, float>(123.456, 123.456F);
    }
}

// -------------------------------------------------------------------------------------

namespace GenericLambdas {

    // ---------------------------------------------------------------------------------
    // generic lambda

    auto lambda = [](auto x, int y) {
        std::cout << "x=" << x << ", y=" << y << std::endl;
        };

    static void test_01()
    {
        lambda(1, 123);
        lambda(2.5, 123);
        lambda(std::string{ "ABC" }, 123);
    }

    // ---------------------------------------------------------------------------------
    // generic lambda - how the compiler sees them

    struct Lambda
    {
        template <typename T>
        auto operator() (T x, int y) {
            std::cout << "x=" << x << ", y=" << y << std::endl;
        }

        template<>
        auto operator() <int> (int x, int y) {
            std::cout << "x=" << x << ", y=" << y << std::endl;
        }

        template<>
        auto operator() <double> (double x, int y) {
            std::cout << "x=" << x << ", y=" << y << std::endl;
        }

        template<>
        auto operator() <std::string> (std::string x, int y) {
            std::cout << "x=" << x << ", y=" << y << std::endl;
        }
    };

    static void test_02()
    {
        struct Lambda instance;
        instance(1, 200);
        instance(2.5, 201);
        instance(std::string{ "ABC" }, 202);

        // compiles too
        instance.operator()<int>(1, 200);
        instance.operator()<double>(2.5, 201);
        instance.operator()<std::string>(std::string{ "ABC" }, 202);
    }

    // ---------------------------------------------------------------------------------
    // generic lambda - several 'auto' parameters

    auto lambdaTwice = [](auto x, auto y) {
        std::cout << "x=" << x << ", y=" << y << std::endl;
        };

    // ---------------------------------------------------------------------------------
    // generic lambda - several 'auto' parameters - how the compiler sees them

    struct LambdaTwice
    {
        template <typename T, typename U>
        auto operator() (T x, U y) {
            std::cout << "x=" << x << ", y=" << y << std::endl;
        }

        template<>
        auto operator() <int,int> (int x, int y) {
            std::cout << "x=" << x << ", y=" << y << std::endl;
        }

        template<>
        auto operator() <long, long long> (long x, long long y) {
            std::cout << "x=" << x << ", y=" << y << std::endl;
        }

        template<>
        auto operator() <double, float> (double x, float y) {
            std::cout << "x=" << x << ", y=" << y << std::endl;
        }
    };

    static void test_03()
    {
        lambdaTwice(1, 2);
        lambdaTwice(123l, 456ll);
        lambdaTwice(123.456, 123.456F);

        struct LambdaTwice instance;
        instance(1, 2);
        instance(123l, 456ll);
        instance(123.456, 123.456F);

        // compiles too
        instance.operator()<int, int>(1, 2);
        instance.operator()< long, long long >(123l, 456ll);
        instance.operator()<double, float>(123.456, 123.456F);
    }
}

// -------------------------------------------------------------------------------------

namespace GenericLambdasExample {

    static void test_01()
    {
        // define a generic lambda
        auto isGreaterThanFifty = [](auto n) { return n > 50; };

        std::vector<int> intValues{ 44, 65, 22, 77, 2 };

        // use generic lambda with a vector of integers
        auto it1 = std::find_if(
            intValues.begin(),
            intValues.end(),
            isGreaterThanFifty
        );
        if (it1 != intValues.end()) {
            std::cout << "Found a value: " << *it1 << std::endl;
        }

        std::vector<double> doubleValues{ 24.5, 75.5, 12.5, 87.5, 12.5 };

        // use exactly the *same* generic lambda with a vector of doubles
        auto it2 = std::find_if(
            doubleValues.begin(),
            doubleValues.end(),
            isGreaterThanFifty
        );
        if (it2 != doubleValues.end()) {
            std::cout << "Found a value: " << *it2 << std::endl;
        }
    }

    template <typename T>
    bool isGreaterThanFiftyEx(const T& n)
    {
        return n > 50;
    };

    static void test_02()
    {
        std::vector<int> intValues{ 44, 65, 22, 77, 2 };

        // use template function with a vector of integers
        auto it1 = std::find_if(
            intValues.begin(),
            intValues.end(),
            isGreaterThanFiftyEx<int>
        );
        if (it1 != std::end(intValues)) {
            std::cout << "Found a value: " << *it1 << std::endl;
        }

        std::vector<double> doubleValues{ 24.5, 75.5, 12.5, 87.5, 12.5 };

        // use exactly the *same* template function with
        // another specialization with a vector of doubles
        auto it2 = std::find_if(
            doubleValues.begin(),
            doubleValues.end(),
            isGreaterThanFiftyEx<double>
        );
        if (it2 != std::end(doubleValues)) {
            std::cout << "Found a value: " << *it2 << std::endl;
        }
    }
}

// -------------------------------------------------------------------------------------

namespace GenericFunctionsExample {

    // define a generic function (top-level (!))
    static auto isGreaterThanFifty(auto n) { return n > 50; };

    static void test_01()
    {
        std::vector<int> intValues{ 44, 65, 22, 77, 2 };

        // use generic function with a vector of integers
        auto it1{ std::find_if(
            intValues.begin(),
            intValues.end(),
            isGreaterThanFifty<int>
        ) };

        if (it1 != intValues.end()) {
            std::cout << "Found a value: " << *it1 << std::endl;
        }

        std::vector<double> doubleValues{ 24.5, 75.5, 12.5, 87.5, 12.5 };

        // use exactly the *same* generic function with a vector of doubles
        auto it2{ std::find_if(
            doubleValues.begin(),
            doubleValues.end(),
            isGreaterThanFifty<double>
        ) };

        if (it2 != doubleValues.end()) {
            std::cout << "Found a value: " << *it2 << std::endl;
        }
    }
}

// -------------------------------------------------------------------------------------

namespace GenericTemplatedLambdas {

    static void test_01()
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

    static void test_02()
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

    static void test_03()
    {
        auto l5 = []<typename T>(T a, T b) { return a + b; };      // C++ 20, template lambda

        auto v1 = l5(42, 1);                                       // Ok
        // auto v2 = l5(42, 1.0);                                  // Error
        auto v4 = l5(42.0, 1.0);                                   // Ok
        // auto v5 = l5(42, false);                                // Error
        auto v6 = l5(std::string{ "42" }, std::string{ "1" });     // Ok
        // auto v6 = l5(std::string{ "42" }, '1');                 // Error
    }

    static void test_04()
    {
        auto l6 = [](auto a, decltype(a) b) { return a + b; };     // C++ 14, using decltype

        auto v1 = l6(42.0, 1);                                     // Ok
        // auto v2 = l6(42, 1.0);                                  // Warning
        // auto v3 = l6(std::string{ "42" }, '1');                 // Error
    }

    // -------------------------------------------------------------------------------------

    static void foo(const std::string& s) {
        std::cout << "Signature: const&" << std::endl;
    }

    static void foo(std::string&& s) {
        std::cout << "Signature: &&" << std::endl;
    }

    auto callingFoo = [](auto&& s) {
        std::cout << "Calling foo(): " << s;
        foo(std::forward<decltype(s)>(s));
    };

    static void test_05()
    {
        const std::string str{ "Hello World with LValue - " };
        callingFoo(str);
        callingFoo("Hello World with RValue - ");
    }
}

// -------------------------------------------------------------------------------------

namespace GenericRecursiveLambdas {

    static void test_01()
    {
        // power recursive function
        std::function<int(int, int)> power;

        power = [&](int base, int exp) {
            return exp == 0 ? 1 : base * power(base, exp - 1);
            };

        std::cout << power(2, 10) << std::endl; // 2^10 = 1024
    }

    static void test_02()
    {
        // factorial recursive function
        std::function<int(int)> factorial;

        factorial = [&](int n) {
            if (n < 2) {
                return 1;
            }
            else {
                return n * factorial(n - 1);
            }
            };

        std::cout << factorial(5) << std::endl; // 120
    }

    static void test_03()
    {
        // power recursive lambda function
        auto power = [](auto self, auto base, int exp) -> decltype(base) {
            return exp == 0 ? 1 : base * self(self, base, exp - 1);
            };

        std::cout << power(power, 2, 10) << std::endl;    // 2^10 = 1024

        std::cout << power(power, 2.71828, 10);           // e^10 = 22026.3
    }

    static void test_04()
    {
        // factorial recursive lambda function
        auto factorial = [](auto f, int const n) {

            if (n < 2) {
                return 1;
            }
            else {
                return n * f(f, n - 1);
            }
            };

        std::cout << factorial(factorial, 5) << std::endl; // 120
    }
}

// -------------------------------------------------------------------------------------

namespace GenericLambdasCurrying {


    static void test_01() {

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

    static void test_02() {

        int n = 1;
        double d = 2.7;

        auto result1 = add<int, double>(n, d);
        std::cout << result1 << std::endl;
    }
}

// -------------------------------------------------------------------------------------

static void test_generic_functions()
{
    using namespace GenericFunctions;
    test_01();
    test_02();
    test_03();
}

static void test_generic_functions_example()
{
    using namespace GenericFunctionsExample;
    test_01();
}

static void test_generic_lambdas()
{
    using namespace GenericLambdas;
    test_01();
    test_02();
    test_03();
}

static void test_generic_lambdas_example()
{
    using namespace GenericLambdasExample;
    test_01();
    test_02();
}

static void test_templated_lambdas()
{
    using namespace GenericTemplatedLambdas;
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
}

static void test_recursive_lambdas()
{
    using namespace GenericRecursiveLambdas;
    test_01();
    test_02();
    test_03();
    test_04();
}

static void test_lambdas_and_currying()
{
    using namespace GenericLambdasCurrying;
    test_01();
    test_02();
}

// -------------------------------------------------------------------------------------

void main_generic_functions()
{
    test_generic_functions();
    test_generic_functions_example();
    test_generic_lambdas();
    test_generic_lambdas_example();
    test_templated_lambdas();
    test_recursive_lambdas();
    test_lambdas_and_currying();
}

// =====================================================================================
// End-of-File
// =====================================================================================
