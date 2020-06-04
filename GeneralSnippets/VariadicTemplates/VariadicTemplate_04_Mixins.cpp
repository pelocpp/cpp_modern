// =====================================================================================
// Variadic Templates - Mixins
// =====================================================================================

#include <iostream>
#include <sstream>
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
    class MyRepository : private SlotA, private SlotB
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
        MyRepository repo;

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
    class Repository : private Slots...  // inherit private from our slots...
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

    using MyRepo = Repository< Slot<int>, Slot<std::string> >;

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

        template <typename... Args>
        void emplace(const Args&... args)
        {
            m_value = T(args...); // copy-operator (might use move semantics)
        }

    private:
        T m_value;
    };

    template <typename... Slots>
    class RepositoryEx : private Slots...  // inherit private from our slots...
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

        template <typename T, typename Key = DefaultSlotKey, typename... Args>
        void emplace(const Args&... args)
        {
            SlotEx<T, Key>::emplace(args...);
        }
    };

    // again forward definition sufficient, definition not needed
    struct Key1;
    struct Key2;

    // repository definition with keys
    using MyRepoEx = RepositoryEx
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

    class Person {
    private:
        std::string m_firstName;
        std::string m_lastName;
        int m_age;
    public:
        Person() : m_firstName(std::string("")), m_lastName(std::string("")), m_age(0) {}

        Person(const std::string& firstName, const std::string& lastName, const int age)
        : m_firstName(firstName), m_lastName(lastName), m_age(age) {}

        Person& operator= (const Person& person) {
            // prevent self-assignment
            if (this == &person)
                return *this;

            // assign right side
            m_firstName = person.m_firstName;
            m_lastName = person.m_lastName;
            m_age = person.m_age;

            return *this;
        }
        Person& operator= (Person&& person) noexcept  { 
            // prevent self-assignment
            if (this == &person)
                return *this;

            // assign right side
            m_firstName = person.m_firstName;
            m_lastName = person.m_lastName;
            m_age = person.m_age;

            // reset source  object, ownership has been moved
            person.m_firstName.clear();
            person.m_lastName.clear();
            person.m_age = 0;

            return *this;
        }

        std::string operator()() { 
            std::ostringstream oss; 
            oss << m_firstName << " " << m_lastName << " [" << m_age << "]"; 
            return  oss.str();
        }
    };

    void test_07() {
        using MyRepo = RepositoryEx
        <
        SlotEx<Person>,
        SlotEx<std::string>
        >;

        MyRepo repo;

        repo.emplace<std::string>(5, 'A');
        std::cout << repo.get<std::string>() << std::endl; // printing "AAAAA"

        repo.emplace<Person>(std::string("Hans"), std::string("Mueller"), 21);
        std::cout << repo.get<Person>()() << std::endl; // printing "Hans Mueller [21]"
    }
}

int main_mixins()
{
    using namespace VariadicTemplatesMixins;
    test_01();
    test_02();
    test_03();
    test_04();
    //test_05();  // doesn't compile
    test_06();
    test_07();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
