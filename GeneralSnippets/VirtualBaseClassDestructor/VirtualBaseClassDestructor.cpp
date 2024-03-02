// =====================================================================================
// VirtualBaseClassDestructor.cpp // Virtual Base Class Destructor
// =====================================================================================

module modern_cpp:virtual_base_class_destructor;

namespace VirtualBaseClassDestructor {

    class Base
    {
    public:
        ~Base()  // <== add keyword 'virtual' in front of this line !!!
        {
            // do some important cleanup in class Base
            std::cout << "d'tor Base" << std::endl;
        }

        // some virtual methods
        virtual void doSomething() {}
    };

    class Derived : public Base
    {
    public:
        ~Derived()
        {
            // do some important cleanup in class Derived
            std::cout << "d'tor Derived" << std::endl;
        }
    };

    static void test01() {
        Base* b = new Derived();
        // use b
        delete b; // here's the problem!
    }
}

void main_virtual_base_class_destructor()
{
    using namespace VirtualBaseClassDestructor;
    test01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
