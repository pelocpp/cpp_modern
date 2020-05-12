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
    // Variant 1: "copy-paste" style 

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
        Repository repo;

        repo.setSlotA(123);
        std::cout << repo.getSlotA() << std::endl; // printing 123

        repo.setSlotB(std::string("ABC"));
        std::cout << repo.getSlotB() << std::endl; // printing "ABC"
    }

    // ===================================================================
    // Variant 2: "varidiac inheritance" style 

    template <typename T>
    class Slot
    {
    protected:
        T& get()
        {
            return m_value;
        }

        void set(const T& value) // Same encapsulation.
        {
            m_value = value;
        }

    private:
        T m_value;
    };

    template <typename... Slots>
    class RepositoryEx : private Slots...  // inherit private from our slots...
    {
    public:
        template <typename T> // select type
        T& get()
        {
            return Slot<T>::get(); // select base class
        }

        template <typename T>
        void set(const T& value)
        {
            Slot<T>::set(value);
        }
    };

    using MyRepo = RepositoryEx< Slot<int>, Slot<std::string> >;

    void test_04() {
        MyRepo repo;

        repo.set<std::string>("XYZ");
        repo.set(987); // note type deduction: we pass an int, so it writes to the int slot

        std::cout << repo.get<int>() << std::endl; // printing 987
        std::cout << repo.get<std::string>() << std::endl; // printing "XYZ"
    }

    // ===================================================================
    // Variant 3: improving variant 2: several slots with same type

    void test_05() {
        // RepositoryEx < Slot<int>, Slot<int> > repo;
        // error: 'VariadicTemplatesMixins::Slot<int>' is already a direct base
    }

    struct DefaultSlotKey; // forward definition sufficient

    template <typename T, typename Key = DefaultSlotKey>
    class SlotEx
    {
    protected:
        T& get()
        {
            return m_value;
        }

        void set(const T& value)
        {
            m_value = value;
        }

    private:
        T m_value;
    };

    template <typename... Slots>
    class RepositoryExEx : private Slots...  // inherit private from our slots...
    {
    public:
        template <typename T, typename Key = DefaultSlotKey>
        T& get()
        {
            return SlotEx<T, Key>::get(); // select base class
        }

        template <typename T, typename Key = DefaultSlotKey>
        void set(const T& value)
        {
            SlotEx<T, Key>::set(value);
        }
    };

    // again forward definition sufficient, definition not needed
    struct Key1;
    struct Key2;

    // repository definition with keys
    using MyRepoEx = RepositoryExEx
        <
        SlotEx<int>,
        SlotEx<std::string, Key1>,
        SlotEx<std::string, Key2>
        >;

    void test_06() {
        MyRepoEx repo;

        repo.set(12345); // note type deduction: we pass an int, so it writes to the int slot
        repo.set<std::string, Key1>("AAA");
        repo.set<std::string, Key2>("BBB");

        std::cout << repo.get<int>() << std::endl; // printing 12345
        std::cout << repo.get<std::string, Key1>() << std::endl; // printing "AAA"
        std::cout << repo.get<std::string, Key2>() << std::endl; // printing "BBB"
    }
}


int main()
// int main_mixins()
{
    using namespace VariadicTemplatesMixins;
    //test_01();
    //test_02();
   // test_03();
    // test_04();
    //test_05();  // doesn't compile
    test_06();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
