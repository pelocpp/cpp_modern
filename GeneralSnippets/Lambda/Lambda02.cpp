// =====================================================================================
// Lambda and Closure Classes
// =====================================================================================

#include <iostream>

namespace LambdaAndClosure {

    void test_01() {

        const int n{ 10 };
        auto lambda = [n](int a) {return n + a; };
        const auto m = lambda(20); // m is now 30
        std::cout << "m: " << m << std::endl;
    }

    class ClosureClass
    {
    public:
        ClosureClass(int n) : m_n(n) {}

        int operator()(int a)
        {
            return m_n + a;
        }

    private:
        int m_n;
    };

    void test_02() {

        const int n{ 30 };
        auto lambda = ClosureClass(n);
        const auto m = lambda(20); // m is now 50
        std::cout << "m: " << m << std::endl;
    }
}

int main_lambdaandclosure()
{
    using namespace LambdaAndClosure;
    test_01();
    test_02();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
