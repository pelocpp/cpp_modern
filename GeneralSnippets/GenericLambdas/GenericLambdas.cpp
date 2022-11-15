// =====================================================================================
// Generic Lambdas
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

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

    // define a generic lambda
    auto isGreaterThanFifty = [](const auto& n) { return n > 50; };

    void test_04()
    {
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

    auto l1 = [](int a) { return a + a; };             // C++ 11, regular lambda

    auto l2 = [](auto a) { return a + a; };            // C++ 14, generic lambda

    auto l3 = []<typename T>(T a) { return a + a; };   // C++ 20, template lambda

    void test_06()
    {
        auto v1 = l1(42);                    // OK
        // auto v2 = l1(42.0);                  // Warning
        // auto v3 = l1(std::string{ "42" });   // Error

        auto v5 = l2(42);                    // OK
        auto v6 = l2(42.0);                  // OK
        auto v7 = l2(std::string{ "42" });   // OK
        
        auto v8 = l3(42);                    // OK
        auto v9 = l3(42.0);                  // OK
        auto v10 = l3(std::string{ "42" });  // OK
    }

    auto l11 = [](int a, int b) {return a + b; };
    auto l12 = [](auto a, auto b) {return a + b; };
    auto l13 = []<typename T, typename U>(T a, U b)
    {
        return a + b;
    };

    void test_07()
    {
        auto v1 = l11(42, 1); // OK
        //auto v2 = l11(42.0, 1.0); // warning
        //auto v3 = l11(std::string{ "42" }, '1'); // error

        auto v4 = l12(42, 1); // OK
        auto v5 = l12(42.0, 1); // OK
        auto v6 = l12(std::string{ "42" }, '1'); // OK
        auto v7 = l12(std::string{ "42" }, std::string{ "1" }); // OK

        auto v8 = l13(42, 1); // OK
        auto v9 = l13(42.0, 1); // OK
        auto v10 = l13(std::string{ "42" }, '1'); // OK
        auto v11 = l13(std::string{ "42" }, std::string{ "42" }); // OK

    }


    // REKURSIVE LAmbdas ...
    // WEITER :  https://www.nextptr.com/tutorial/ta1224017367/generic-code-with-generic-lambda-expression



    // -------------------------------------------------------------------



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
}

// =====================================================================================
// End-of-File
// =====================================================================================
