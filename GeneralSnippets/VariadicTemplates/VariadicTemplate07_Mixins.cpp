// =====================================================================================
// Variadic Templates - Mixins
// =====================================================================================

#include <iostream>
#include <string>
#include <functional>

namespace VariadicTemplatesMixins {

    // need some classes with default constructors
    class A { public: A() = default; };
    class B { public: B() = default; };
    class C { public: C() = default; };

    template<typename ... TS>
    class X : public TS...
    {
    public:
        X(const TS&... mixins) : TS(mixins)... {}
    };

    void test_01() {
        A a;
        B b;
        C c;
        X<A, B> xAB(a, b);
        // X<B, A> xBA;   // Error, needs arguments
        X<C> xC(c);
        X<> xNoBases;

        X<A, B, C>  xabc(a, b, c);
    }

    void test_02() {
        A a;
        B b;
        C c;

        X<A, B, C>  xabc(a, b, c);
    }

    // ===================================================================

    class SlotA
    {
    public:
        int value;
    };

    class SlotB
    {
    public:
        std::string value;
    };

    // Note: private inheritance, no one can access directly to the slots other than Repository itself
    class Repository : private SlotA, private SlotB
    {
    public:
        void setSlotA(const int& value)
        {
            // Access the base-class's value: since we have multiple bases
            // with a 'value' field, we need to "force" the access to SlotA.
            SlotA::value = value;
        }

        int getSlotA()
        {
            return SlotA::value;
        }

        void setSlotB(const std::string& b)
        {
            SlotB::value = b;
        }

        std::string getSlotB()
        {
            return SlotB::value;
        }
    };

    void test_03() {
        Repository r;

        r.setSlotA(42);
        std::cout << r.getSlotA() << std::endl; // Print: 42.

        r.setSlotB(std::string("toto"));
        std::cout << r.getSlotB() << std::endl; // Print: "toto".
    }

   //  WEITER: https://jguegant.github.io/blogs/tech/thread-safe-multi-type-map.html



}

int main_mixins()
{
    using namespace VariadicTemplatesMixins;
    test_01();
    test_02();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
