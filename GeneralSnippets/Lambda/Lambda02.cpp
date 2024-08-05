// =====================================================================================
// Lambda02.cpp // Lambdas under the Hood
// =====================================================================================

module modern_cpp:lambda;

namespace LambdasUnderTheHood {

    static void test_01()
    {
        int n{ 10 };

        auto lambda{ [n](int a) { return n + a; } };

        auto m { lambda(20) };  // m is now 30

        std::cout << "m: " << m << std::endl;
    }

    static void test_02()
    {
        class LambdaClass
        {
        public:
            LambdaClass(int n) : m_n{ n } {}

            int operator() (int a) const
            {
                return m_n + a;
            }

        private:
            mutable int m_n;  // if lambda modifies state, add keyword 'mutable'
        };

        const int n{ 30 };

        auto lambda{ LambdaClass(n) };

        auto m{ lambda(20) };    // m is now 50

        std::cout << "m: " << m << std::endl;
    }
}

void main_lambda_and_closure()
{
    using namespace LambdasUnderTheHood;
    test_01();
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
