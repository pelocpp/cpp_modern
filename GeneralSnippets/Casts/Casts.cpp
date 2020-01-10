#include <iostream>
#include <memory>

// =====================================================================================
// static_cast, dynamic_cast, const_cast and reinterpret_cast examples
// =====================================================================================

namespace CastStatic {

    enum class Color { red, green, blue };

    void test_01() {

        // int n = Color::blue;  // a value of type "Color" cannot be used to initialize an entity of type "int"

        int m = static_cast<int>(Color::blue);
        std::cout << m << std::endl;
    }

    struct Base {
        // int m = 0;
        void sayHello() const {
            std::cout << "This is Base!" << std::endl;
        }
    };

    struct Derived : Base {
        void sayHello() const {
            std::cout << "This is Derived!" << std::endl;
        }
    };

    // static_cast
    void test_02() {

        // upcast
        Derived derived;
        Base& br = derived; // upcast: implicit conversion - allowed
        br.sayHello();

        // downcast
        Derived& anotherDerived = (Derived&)br; // downcast - old-style cast
        anotherDerived.sayHello();

        Derived& anotherDerived2 = static_cast<Derived&>(br); // downcast - correct style
        anotherDerived2.sayHello();

        Base anotherBase;
        Derived& anotherDerived3 = (Derived&)anotherBase; // downcast - old-style cast
        anotherDerived3.sayHello();

        Derived& anotherDerived4 = static_cast<Derived&>(anotherBase); // downcast - correct style
        anotherDerived4.sayHello();
    }
}

namespace CastDynamic {

    struct Base {
        // int m = 0;
        virtual void sayHello() const {
            std::cout << "This is Base!" << std::endl;
        }
    };

    struct Derived : Base {
        void sayHello() const override {
            std::cout << "This is Derived!" << std::endl;
        }
    };

    Derived* testFunc(Base* baseRef) {

        Derived* pDerived = dynamic_cast<Derived*> (baseRef);
        if (pDerived != nullptr) {
            pDerived->sayHello();
        }
        else {
            std::cout << "dynamic_cast failed!" << std::endl;
        }

        return static_cast<Derived*>(baseRef);
    }

    void test_01() {

        Base aBase;
        Derived aDerived;

        Base* pBase1 = &aBase;
        Base* pBase2 = &aDerived;

        Derived* pResult;

        pResult = testFunc(pBase2);
        pResult->sayHello();

        pResult = testFunc(pBase1);
        pResult->sayHello();
    }

    void test_02() {}
}

namespace CastConst {

    void test_01() {

        int n = 1;
        const int* ip1 = &n;
        std::cout << n << std::endl;

        // *ip1 = 2;  // doesn't compile

        // remove constness from pointer
        int* ip2 = const_cast <int*> (ip1);
        *ip2 = 2;  // compiles :-)
        std::cout << n << std::endl;

        // remove constness from a reference
        const int& ri = n;
        const_cast <int&> (ri) = 3;
        std::cout << n << std::endl;

        // convert const pointer directly
        *const_cast <int*> (ip1) = 4;
        std::cout << n << std::endl;
    }

    void test_02() {}
}

namespace CastReinterpret {

    void test_01() {

        int* p = new int(65);
        char* ch = reinterpret_cast<char*>(p);
        std::cout << *p << std::endl;
        std::cout << *ch << std::endl;
    }

    struct myStruct {
        char x1;
        char x2;
        char x3;
        char x4;
    };

    void test_02() {

        // using {} initialization syntax
        myStruct s{ 'A' , 'B' , 'C' , '\0' };

        // reinterpret struct as char* pointer :-) 
        char* ptr = reinterpret_cast<char*>(&s);

        std::cout << ptr << std::endl;
    }
}

int main_casts()
{
    using namespace CastStatic;
    // using namespace CastDynamic;
    // using namespace CastConst;
    // using namespace CastReinterpret;
    test_01();
    test_02();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
