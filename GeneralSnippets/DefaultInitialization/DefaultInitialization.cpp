// =====================================================================================
// DefaultInitialization.cpp // Default Initialization
// =====================================================================================

module modern_cpp:default_initialization;

import std;

namespace {

    class X
    {
    private:
        int m_i = 1;
        int m_j{ 2 };

    public:
        X() = default;    // initializes m_i with 1 and m_j with 2
        X(int);
    };

    X::X(int value) : m_i{ value }  // initializes m_i with value (here: 17) and m_j with 2
    {}

    static void default_initialization() {
        X x{};
        X y{ 17 };
    }
}

void main_default_initialization()
{
    default_initialization();
}

// =====================================================================================
// End-of-File
// =====================================================================================
