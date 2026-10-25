// =====================================================================================
// VirtualBaseClassDestructor.cpp // Virtual Base Class Destructor
// =====================================================================================

module modern_cpp:virtual_base_class_destructor;

import std;

namespace {

    class Base
    {
    public:
        ~Base()  // <== add keyword 'virtual' in front of this line !!!
        {
            // do some important cleanup in class Base
            std::println("d'tor Base");
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
            std::println("d'tor Derived");
        }
    };
}

void main_virtual_base_class_destructor()
{
    Base* b = new Derived();
    // use b
    delete b; // here's the problem!
}

// =====================================================================================
// End-of-File
// =====================================================================================
