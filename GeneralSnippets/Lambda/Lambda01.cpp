// =====================================================================================
// Lambda Methods
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

namespace Lambda {

    bool myCompare (int n1, int n2) {
        return n1 < n2;
    }

    struct MyComparer {
        bool operator() (int n1, int n2) {
            return n1 < n2;
        }
    };

    void test_01() {

        // local class within function possible
        struct MyInternalComparer {
            bool operator() (int n1, int n2) {
                return n1 < n2;
            }
        };

        std::vector<int> vec { 5, 9, 1, 3, 7, 8 };
        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(std::begin(vec), std::end(vec), myCompare);
        // or
        std::sort(std::begin(vec), std::end(vec), MyComparer());
        // or
        std::sort(std::begin(vec), std::end(vec), MyInternalComparer());

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    void test_02() {

        std::vector<int> vec{ 50, 90, 10, 30, 70, 80 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(
            std::begin(vec),
            std::end(vec),
            [] (int n1, int n2) { return n1 < n2; }
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    void test_03() {

        // shortest lambda on earth: no parameters, capturing and doing nothing
        auto nothing = []{};
        nothing();

        // c'tor notation
        auto itsOne ([] { return 1; });
        auto itsTwo ([] { return 2; });
        std::cout << itsOne() << ", " << itsTwo() << std::endl;

        // "copy-c'tor" notation
        auto itsFour = [] { return 4; };
        auto itsFive = [] { return 5; };
        std::cout << itsFour() << ", " << itsFive() << std::endl;
    }

    void test_04() {

        // defining a lambda without 'auto'
        std::function<int(int, int, int)> threeArgs([](int x, int y, int z) {
            return x + y + z; 
            }
        );

        std::cout << threeArgs (5, 6, 7) << std::endl;
    }

    void test_05() {

        // defining new variables in the lambda capture:
        // we can declare a new variable that is only visible in the scope of the lambda.
        // we do so by defining a variable in the lambda-capture without specifying its type

        // lambda with variable definition
        auto lambda = [variable = 10]() { return variable; };
        std::cout << lambda() << std::endl;

        // Captures default to 'const value':
        // The mutable keyword removes the 'const' qualification from all captured variables
        auto counter = [count = 50]() mutable { 
            ++count; 
            return count;
        };

        for (size_t i{}; i < 5; ++i) {
            std::cout << counter() << " ";
        }
        std::cout << std::endl;
    }

    void test_06() {

        int n = 1;
        int m = 2;

        auto l1 = [=] () {
            std::cout << "Copy:      " << n << " " << m << std::endl;
        };

        auto l2 = [&] () {
            std::cout << "Reference: " << n << " " << m << std::endl;
        };

        auto l3 = [&, m] () {
            std::cout << "Both:      " << n << " " << m << std::endl;
        };

        auto l4 = [=, &m] () {
            std::cout << "More both: " << n << " " << m << std::endl;
        };

        n = 3;
        m = 4;

        l1();
        l2();
        l3();
        l4();
    }

    auto test_07_helper_a() {

        int n = 1;
        int m = 2;

        auto lambda = [=] {
            std::cout << "Copy:      " << n << " " << m << std::endl;
        };

        return lambda;
    }

    auto test_07_helper_b() {

        int n = 1;
        int m = 2;

        auto lambda = [&] {
            std::cout << "Reference: " << n << " " << m << std::endl;
        };

        return lambda;  // I would't do this never ever :-)
    }

    void test_07() {

        auto outerLambda1 = test_07_helper_a();
        auto outerLambda2 = test_07_helper_b();
        outerLambda1();
        outerLambda2();
    }

    void test_08() {

        // Example demonstrating so called 'Currying':

        // This means that we take a function that can accept some parameters
        // and store it in another function object, which accepts *fewer* parameters.

        // In our example, we define a 'plusTen' function which accepts a single parameter.
        // This parameter is forwarded to the 'plus' function. The second parameter equals 10,
        // which is being saved in the function object:

        auto plus = [](auto l, auto r) { return l + r; };

        auto plusTen = [plus](int x) { return plus(10, x); };

        std::cout << plusTen(5) << std::endl;
    }

    void test_10() {

        // demonstrating 'noexcept'
        auto itsOne([] () noexcept { return 1; });
        auto itsTwo = [] () noexcept { return 2; };
        std::cout << itsOne() << ", " << itsTwo() << std::endl;
    }

    // similarities between templates and generic lambdas
    template <typename T, typename U>
    auto add = [](const T& t, const U& u) -> decltype (t + u)
    {
        return t + u;
    };

    void test_11() {

        int n = 1;
        double d = 2.7;

        auto result1 = add<int, double>(n, d);
        std::cout << result1 << std::endl;
    }

    void test_12() {
        // works with anything that defines the plus 'operator+'
        auto plus = [](auto l, auto r) { return l + r; };
        std::cout << plus(1, 2) << std::endl;
        std::cout << plus(std::string{ "a" }, "b") << std::endl;

        // inline-definition and direct invocation of lambda funtion
        std::cout << [](auto l, auto r) { return l + r; } (11, 12) << std::endl;
    }

}

void main_lambdas()
{
    using namespace Lambda;
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
    test_07();
    test_08();
    test_10();
    test_11();
    test_10();
}

// =====================================================================================
// End-of-File
// =====================================================================================
