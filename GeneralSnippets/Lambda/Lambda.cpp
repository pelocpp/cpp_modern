#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>

// =====================================================================================
// Lambda Methods
// =====================================================================================

namespace Lambda {

    struct CompareMyInts {

        bool operator() (const int n1, const int n2) {
            return n1 < n2;
        }
    };

    void test_01() {

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

        std::sort(std::begin(myVector), std::end(myVector), CompareMyInts());

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
            [](const int n1, const int n2) { return n1 < n2; }
        );

        for (int n : myVector) {
            std::cout << n << ' ';
        }
    }

    void test_03() {

        int n = 1;
        int m = 2;

        auto l1 = [=]() {
            std::cerr << "Copy:      " << n << " " << m << std::endl;
        };

        auto l2 = [&]() {
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

    auto test_04_helper_a() {

        int n = 1;
        int m = 2;

        auto lambda = [=]() {
            std::cerr << "Copy:      " << n << " " << m << std::endl;
        };

        return lambda;
    }

    auto test_04_helper_b() {

        int n = 1;
        int m = 2;

        auto lambda = [&]() {
            std::cerr << "Reference: " << n << " " << m << std::endl;
        };

        n = 3;
        m = 4;

        return lambda;  // I would't do this never ever :-)
    }

    void test_04() {

        auto outerLambda1 = test_04_helper_a();
        auto outerLambda2 = test_04_helper_b();
        outerLambda1();
        outerLambda2();
    }

    std::pair<
        std::function<void(std::string const&)>, 
        std::function<void(std::string const&)>
    > test_05_helper_a() {

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

    void test_05_helper_b(std::function<void(std::string const&)> lambda) {
        lambda("in test_helper ");
    }

    void test_05() {

        auto [lambda1, lambda2] = test_05_helper_a();

        lambda1("in test_05     ");
        test_05_helper_b(lambda1);

        lambda2("in test_05     ");
        test_05_helper_b(lambda2);
    }
}

// int main()
int main_lambdas()
{
    using namespace Lambda;
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
