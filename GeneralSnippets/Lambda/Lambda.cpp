// =====================================================================================
// Lambda Methods
// =====================================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>

namespace Lambda {

    bool myCompare (const int n1, const int n2) {
        return n1 < n2;
    }

    struct MyComparer {
        bool operator() (const int n1, const int n2) {
            return n1 < n2;
        }
    };

    void test_01() {

        // local class within function possible
        struct MyInternalComparer {
            bool operator() (const int n1, const int n2) {
                return n1 < n2;
            }
        };

        std::vector<int> myVector;
        myVector.push_back(5);
        myVector.push_back(9);
        myVector.push_back(1);
        myVector.push_back(3);
        myVector.push_back(7);
        myVector.push_back(8);

        for (int n : myVector) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(std::begin(myVector), std::end(myVector), myCompare);
        // or
        std::sort(std::begin(myVector), std::end(myVector), MyComparer());
        // or
        std::sort(std::begin(myVector), std::end(myVector), MyInternalComparer());

        for (int n : myVector) {
            std::cout << n << ' ';
        }
    }

    void test_02() {

        std::vector<int> myVector;
        myVector.push_back(50);
        myVector.push_back(90);
        myVector.push_back(10);
        myVector.push_back(30);
        myVector.push_back(70);
        myVector.push_back(80);

        for (int n : myVector) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(std::begin(myVector), std::end(myVector),
            [] (const int n1, const int n2) { return n1 < n2; }
        );

        for (int n : myVector) {
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

        // works with anything that defines the plus 'operator+'
        auto plus = [] (auto l, auto r) { return l + r; };
        std::cout << plus(1, 2) << std::endl;
        std::cout << plus(std::string{ "a" }, "b") << std::endl;

        // inline-definition and invocation of lambda funtion
        std::cout << [] (auto l, auto r) { return l + r; } (11, 12) << std::endl;

        // closure with variable definition
        auto counter = [count = 50]() mutable { ++count; return count; };
        for (size_t i{ 0 }; i < 5; ++i) {
            std::cout << counter() << " ";
        }
        std::cout << std::endl;
    }

    void test_04() {

        int n = 1;
        int m = 2;

        auto l1 = [=] () {
            std::cerr << "Copy:      " << n << " " << m << std::endl;
        };

        auto l2 = [&] {
            std::cerr << "Reference: " << n << " " << m << std::endl;
        };

        auto l3 = [&n, m] {
            std::cerr << "Both:      " << n << " " << m << std::endl;
        };

        n = 3;
        m = 4;

        l1();
        l2();
        l3();
    }

    auto test_05_helper_a() {

        int n = 1;
        int m = 2;

        auto lambda = [=] {
            std::cerr << "Copy:      " << n << " " << m << std::endl;
        };

        return lambda;
    }

    auto test_05_helper_b() {

        int n = 1;
        int m = 2;

        auto lambda = [&] {
            std::cerr << "Reference: " << n << " " << m << std::endl;
        };

        return lambda;  // I would't do this never ever :-)
    }

    void test_05() {

        auto outerLambda1 = test_05_helper_a();
        auto outerLambda2 = test_05_helper_b();
        outerLambda1();
        outerLambda2();
    }

    std::pair<
        std::function<void(std::string const&)>, 
        std::function<void(std::string const&)>
    > 
    test_06_helper_a() {

        int n = 1;
        int m = 2;

        std::function<void(std::string const&)> lambda1 = [=](std::string const& info) {
            std::cerr << info << "Copy:      " << n << " " << m << std::endl;
        };

        std::function<void(std::string const&)> lambda2 = [&](std::string const& info) {
            std::cerr << info << "Reference: " << n << " " << m << std::endl;
        };

        return std::pair<
            std::function<void(std::string const&)>,
            std::function<void(std::string const&)>>(lambda1, lambda2);
    }

    void test_06_helper_b(std::function<void(std::string const&)> lambda) {
        lambda("in test_helper ");
    }

    void test_06() {

        auto [lambda1, lambda2] = test_06_helper_a();

        lambda1("in test_05     ");
        test_06_helper_b(lambda1);

        lambda2("in test_05     ");
        test_06_helper_b(lambda2);
    }

    // decltype may modify type deduction, e.g. in generic lamdas
    // (decltype (t + u), decltype (t) or decltype (u) are valid)
    template <typename T, typename U>
    auto add(const T& t, const U& u) -> decltype (t + u) { return t + u; }

    void test_07() {
         
        int n = 1;
        double d = 2.7;

        auto result = add(n, d);

        std::cout << result << std::endl;
    }

    void test_08() {

        // Example demonstrating so called 'Currying':
        // This means that we take a function that can accept some parameters
        // and store it in another function object, which accepts fewer parameters.

        // In our example, we store the 'plus' function and only accept one parameter,
        // which we forward to the 'plus' function.The other parameter is the
        // value 10, which we save in the function object. This way, we get a function,
        // which we call 'plusTen' because it can add that value
        // to the single parameter it accepts :

        auto plus = [](auto l, auto r) { return l + r; };

        auto plusTen = [plus](int x) { return plus(10, x); };

        std::cout << plusTen(5) << std::endl;
    }
}

int main_lambdas()
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

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
