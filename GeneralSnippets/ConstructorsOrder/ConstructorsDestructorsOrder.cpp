// =====================================================================================
// ConstructorsDestructorsOrder.cpp // Order Constructor/Destructor Invocations
// =====================================================================================

module modern_cpp:constructors_destructors_order;

namespace OrderConstructorInvocations {

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


    static void test_01() {

        Derived myDerived;
        myDerived.printHello();
    }
}

void main_constructor_invocations()
{
    using namespace OrderConstructorInvocations;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
