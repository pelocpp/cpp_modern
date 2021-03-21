// =====================================================================================
// DefaultInitialization
// =====================================================================================

#include <iostream>
#include <vector>

namespace DefaultInitializationExample {

    class X
    {
    private:
        int m_i = 1;
        int m_j{ 2 };

    public:
        X(int);
    };

    X::X(int value) : m_i{ value }
    {
    }

    class Y
    {
    private:
        int m_i = 4;
        int m_j{ 5 };

    public:
        Y(int a) : m_i{ a } {}  // initializes m_i with a and m_j with 5
        Y() = default;          // initializes m_i with 4 and m_j with 5
    };

    void test_01() {

    }
}


void main_default_initialization()
{
    using namespace DefaultInitializationExample;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
