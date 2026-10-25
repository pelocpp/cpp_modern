// =====================================================================================
// ConstructorsDestructorsOrder.cpp // Order Constructor/Destructor Invocations
// =====================================================================================

module modern_cpp:constructors_destructors_order;

import std;

namespace {

    class Something {
    public:
        Something() { std::cout << "c'tor Something" << std::endl; }
        virtual ~Something() { std::cout << "d'tor Something" << std::endl; }
    };

    class Base {
    public:
        Base () { std::cout << "c'tor Base" << std::endl; }
        virtual ~Base() { std::cout << "d'tor Base" << std::endl; }
    };

    class Derived : Base {
    public:
        Derived() { std::cout << "c'tor Derived" << std::endl; }
        virtual ~Derived() { std::cout << "d'tor Derived" << std::endl; }

        void printHello() const {
            std::cout << "Hello!" << std::endl;
        }

    private:
        Something m_something;
    };


    void order_constructor_invocations() {

        Derived myDerived;
        myDerived.printHello();
    }
}

void main_constructor_invocations()
{
    order_constructor_invocations();
}

// =====================================================================================
// End-of-File
// =====================================================================================
