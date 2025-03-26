// =====================================================================================
// Casts.cpp // static_cast, dynamic_cast, const_cast, reinterpret_cast
// and C-Style casts examples
// =====================================================================================

module modern_cpp:casts;

namespace DiverseCasts {

    static void test_01_implicit_conversions()
    {
        {
            // no conversions at all
            int a = 123;
            long b = 123l;
        }

        {
            // implicit conversions, done by the compiler
            long a = 123;     // int implicitly converted to long 
            double b = 123l;  // long implicitly converted to double
        }

        {
            // implicit conversions, done by the machine code 
            int a = 123;    
            long b = 123l; 

            long n = a;       // int implicitly converted to long 
            double m = b;     // long implicitly converted to double
        }

        {
            // Promotion
            long   a = 123;   // int promoted to long
            double b = 123l;  // long promoted to double
        }

        {
#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)

            // Demotion
            int  a = 10.0;   // warning: possible loss of data
            bool b = 123;    // warning: possible loss of data

#pragma warning(pop)
        }
    }

    static void test_02_explicit_conversions_static_cast()
    {
        {
            // static_cast
            int  a = static_cast<int>(123.456);  // double demoted to int
        }

        {
            // C-Style-Cast
            char c = 10;          // 1 byte
            int* p = (int*) &c;   // 4 bytes, works ?!?

            // *p = 5;            // run-time error: stack corruption
        }

        {
            // static_cast
            //char c = 10;                    // 1 byte
            //int* p = static_cast<int*>(&c); // 4 bytes // compile error
        }

        enum class Color { red, green, blue };

        {
            // int n = Color::blue;  // a value of type "Color" cannot be used to initialize an entity of type "int"

            int color = static_cast<int>(Color::blue);
            std::println("Color: {}", color);
        }
    }

    static void test_03_explicit_conversions_reinterpret_cast()
    {
        {
            // reinterpret_cast
            char c = 10;                           // 1 byte
            int* p = reinterpret_cast<int*>(&c);   // 4 bytes // compiles

            // *p = 5;                                // run-time error: stack corruption
        }

        struct MyStruct
        {
            char x1;
            char x2;
            char x3;
            char x4;
        };

        {
            struct MyStruct s{ 'A' , 'B' , 'C' , '\0' };

            // reinterpret struct as char* pointer :-) 
            char* ptr = reinterpret_cast<char*>(&s);
            std::println("{}", ptr);
        }
    }

    static void print(int* ptr)
    {
        std::println("{}", *ptr);
    }

    static void test_04_explicit_conversions_const_cast()
    {
        {
            const int constVar = 123;
            int* nonConstIp = const_cast<int*>(&constVar); // removes const
            *nonConstIp = 10; // potential run-time error
        }

        {
            const int constVar = 123;

            // print(&constVar);   // error: cannot convert argument 1 from 'const int*' to 'int*'

            print(const_cast<int*>(&constVar)); // allowed
        }
    }

    static void test_05_explicit_conversions_dynamic_cast()
    {
        class Base
        {
        public: 
            virtual void test() { std::println("Base"); }
        };
            
        class Derived : public Base
        {
        public:
            void test() override { std::println("Derived"); }
        };

        {
            Derived* child = new Derived();
            Base* base = dynamic_cast<Base*>(child); // ok
            base->test();
        }

        {
            Base* base = new Base();
            Derived* child = dynamic_cast<Derived*>(base);

            if (child == 0) {
                std::println("Null pointer returned!");
            }
        }

        {
            Base base;

            try {
                Derived& child = dynamic_cast<Derived&>(base);
            }
            catch (std::bad_cast& e)
            {
                std::println("{}", e.what());
            }
        }

        {
            // less performance overhead : using a static_cast
            Derived* child = new Derived();
            Base* base = static_cast<Base*>(child); // ok
            base->test();
        }

        {
            // conversion may either succeed or fail:
            // Failure: the base pointer points to a Base instance
            // Success: the base pointer points to a Derived instance

            Base* base = new Derived();  // toggle between Base and Derived
            Derived* child = dynamic_cast<Derived*>(base);

            if (child == 0) {
                std::println("Null pointer returned!");
            }
            else {
                std::println("dynamic_cast successful!");
            }
        }

        {
            // conversion may either succeed or fail:
            // Failure: the base pointer points to a Base instance
            // Success: the base pointer points to a Derived instance

            Base* base = new Base();  // toggle between Base and Derived
            Derived* child = static_cast<Derived*>(base);

            if (child == 0) {
                std::println("Null pointer returned!");
            }
            else {
                std::println("static_cast successful!");   // Oooops
            }
        }

        {
            // upcast: implicit conversion - always allowed
            Derived derived;
            Base& br = derived;
            br.test();

            // downcast: old-style cast
            Derived& anotherDerived = (Derived&)br;
            anotherDerived.test();

            // downcast: correct style
            Derived& anotherDerived2 = static_cast<Derived&>(br);
            anotherDerived2.test();

            // downcast: old-style cast
            // Take care: You cannot change a reference from the object to which it references once it bound at initialization.
            Base anotherBase;
            Derived& anotherDerived3 = (Derived&) anotherBase;
            anotherDerived3.test();

            // downcast: correct style
            // Take care: You cannot change a reference from the object to which it references once it bound at initialization.
            Derived& anotherDerived4 = static_cast<Derived&>(anotherBase);
            anotherDerived4.test();
        }
    }
}

// -------------------------------------------------------------------

void main_casts()
{
    using namespace DiverseCasts;

    test_01_implicit_conversions();
    test_02_explicit_conversions_static_cast();
    test_03_explicit_conversions_reinterpret_cast();
    test_04_explicit_conversions_const_cast();
    test_05_explicit_conversions_dynamic_cast();
}

// =====================================================================================
// End-of-File
// =====================================================================================
