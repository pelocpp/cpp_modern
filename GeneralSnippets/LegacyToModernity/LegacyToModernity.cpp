// ===========================================================================
// LegacyToModernity.cpp
// ===========================================================================

module;

#include <cstddef>     // module implementation too unstable
#include <print>       // module implementation too unstable

module modern_cpp:legacy;

import std;

namespace {

    // =======================================================================
    // creating a copy instead using a const reference

    class Person
    {
    private:
        std::string m_name;

    public:
        // c'tor
        Person(const std::string& name) : m_name(name) {}
        // setter
        void setName(const std::string& name) { m_name = name; }
        // getter
        const std::string& getName() { return m_name; }
    };

    // =======================================================================
    // NULL, 0, nullptr

    void log(int code) {}
    void log(const char* msg) {}

    void legacy_null_01()
    {
        log(NULL);     // calls log(int)! (or is ambiguous, depending on the compiler)
        log(nullptr);  // calls log(const char*), as intended
    }

    void takesPointer(int* ptr) {}

    template <typename T>
    void wrap(T arg) { takesPointer(arg); }

    void legacy_null_02()
    {
        // wrap(0);        // T = int; int does NOT convert to a pointer, compile error
        // wrap(NULL);     // same problem, compile error
        wrap(nullptr);     // T = nullptr_t; converts to any pointer, works
    }

    void legacy_null()
    {
        legacy_null_01();
        legacy_null_02();
    }

    // =======================================================================
    // keyword 'override'

    namespace Keyword_Override {

        class Base
        {
        public:
            // user wants to override this method in the derived class
            virtual void func() { std::println("In base class"); }
        };

        class Derived : public Base
        {
        public:
            // did a silly mistake by putting an argument "int a"
            void func(int a) /*override*/   // <=== remove comment
            {
                std::println("In derived class");
            }
        };
    }

    static void legacy_inheritance_keyword_override()
    {
        using namespace Keyword_Override;

        Base base;
        Derived derived;
        std::println("Compiles successfully");

        Base* bp;
        bp = &derived;
        bp->func();
    }

    // =======================================================================
    // Inheriting constructors (C++11)

    namespace Inheriting_Constructors_Cpp_98 {

        // Variant 1: C++ 98: Boilerplate Forwarding

        class Base {
        public:
            Base(int id) : m_id(id) {}
            Base(int id, const std::string& name) : m_id(id), m_name(name) {}
        
        protected:
            int         m_id;
            std::string m_name;
        };

        class Derived : public Base {
        public:
            Derived(int id) : Base(id) {}                                  // pure forwarding
            Derived(int id, const std::string& name) : Base(id, name) {}   // pure forwarding
        
        private:
            int m_extra;
        };

        static void legacy_inheriting_constructors_01()
        {
            Derived d1(1);
            Derived d2(2, "two");
        }
    }

    namespace Inheriting_Constructors_Cpp_11 {

        // Variant 2: C++11: One line

        class Base {
        public:
            Base(int id) : m_id(id) {}
            Base(int id, const std::string& name) : m_id(id), m_name(name) {}

        protected:
            int         m_id;
            std::string m_name;
        };

        class Derived : public Base {
        public:
            using Base::Base;       // inherits Base(int) and Base(int, const std::string&)

        private:
            int m_extra = 0;        // default member initializer, important
        };

        static void legacy_inheriting_constructors_02()
        {
            Derived d1(1);
            Derived d2(2, "two");
        }
    }

    void legacy_inheriting_constructors()
    {
        Inheriting_Constructors_Cpp_98::legacy_inheriting_constructors_01();
        Inheriting_Constructors_Cpp_11::legacy_inheriting_constructors_02();
    }

    // =======================================================================
    // auto / Range-based for-loop

    struct Order { double price() const { return 0.0; } };

    void legacy_auto_range_based_for_loop()
    {
        std::vector<Order> orders;
        double total{};

        // C++98
        for (std::vector<Order>::const_iterator it = orders.begin(); it != orders.end(); ++it)
            total += it->price();

        // C++11
        for (const Order& o : orders)
            total += o.price();

        // refactoring

        std::vector<Person> persons;   // add comment ...
        // std::list<Person> persons;  // ... and remove comment

        std::vector<Person>::const_iterator it = persons.cbegin();  // iterator type must be manually adjusted

        auto it2 = persons.cbegin();                                // iterator type is deducted automatically  - at compile time
    }

    // =======================================================================
    // enums

    // 1. the problem with classic enums (unscoped enums)
    enum CarColor { Red, Blue, Green };
    // enum WineColor { Red, WHITE }; // ERROR: "Red" conflicts with CarColor::Red!

    // 2. the solution: Enum classes (scoped enums)
    enum class TrafficLightPhase { Red, Yellow, Green }; // "Red" and "Green" are safely encapsulated here

    enum class SensorStatus { Ok, Error, Red };          // No name conflict with TrafficLightPhase::Red!

    void legacy_enums() {

        // --- DIFFERENCE 1: Scope ---
        // with classic enums, the values ​​are exported into the surrounding scope:
        int myColor = Red;

        // with enum class, the name of the enumeration must be prefixed:
        TrafficLightPhase light = TrafficLightPhase::Red;

        SensorStatus sensor = SensorStatus::Red;   // cleanly separated! 

        // --- DIFFERENCE 2: Implicit int conversion ---
        // classic enums implicitly convert to int (error-prone!):
        if (myColor == 0) {
            std::println("This works because Red implicitly becomes 0.");
        }

        // enum classes completely prevent this implicit conversion:
        // if (light == 0) { } // COMPILER ERROR: No implicit conversion! 

        // if you absolutely need the integer value,
        // you must request it explicitly (using static_cast):
        if (static_cast<int>(light) == 0) {
            std::println("Explicit cast works: TrafficLightPhase::Red is {}", static_cast<int>(light));
        }
    }

    // =======================================================================
    // typedef vs. using

    template <typename T>
    using StringMap = std::map<std::string, T>;   // Template Aliasing (Alias Templates)

    void legacy_typedef_using()
    {
        // Usage:
        StringMap<int> myMap;
    }

    typedef int MyInt;
    using MyInt = int;
    
    typedef void (*FuncPtr)(int, const std::string&);
    using FuncPtr = void(*)(int, const std::string&);
    
    typedef int IntArray[10];
    using IntArray = int[10];

    // =======================================================================
    // constexpr

    // windef.h -- Basic Windows Type Definitions
    typedef unsigned char     BYTE;
    typedef unsigned short    WORD;
    typedef unsigned long     DWORD;

    // wingdi.h
    typedef DWORD             COLORREF;

    // wingdi.h // Little-Endian BGR-Format
    #define RGB(r,g,b)  ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

    // classic RGB-Format
    constexpr std::uint32_t Rgb(std::uint8_t r, std::uint8_t g, std::uint8_t b)
    {
        return
            static_cast<std::uint32_t>(r) << 16 |
            static_cast<std::uint32_t>(g) << 8 |
            static_cast<std::uint32_t>(b);
    }

    void legacy_macros_constexpr()
    {
        // not recommended usage - no errors or just warnings
        COLORREF unknown1 = RGB(255.0, 0.0, 0.0);             // No warning, no error
        COLORREF unknown2 = RGB('173', '216', '230');         // No warning, no error
        COLORREF unknown3 = RGB(1000, 5000, 32000);           // No warning, no error

        // recommended usage
        constexpr std::uint32_t red{ Rgb(255, 0, 0) };
        constexpr std::uint32_t lightBlue{ Rgb(173, 216, 230) };
        constexpr std::uint32_t aqua{ Rgb(0, 255, 255) };
        constexpr std::uint32_t darkGreen{ Rgb(1, 50, 32) };

        std::println("{:#010X}", red);
        std::println("{:#010X}", lightBlue);
        std::println("{:#010X}", aqua);
        std::println("{:#010X}", darkGreen);
    }

    // =======================================================================
    // Method Chaining

    void legacy_method_chaining()
    {
        std::string s = "I have even sold some";
        s.replace(0, 6, "").replace(s.find("even"), 4, "only");

        std::println("{}", s);
    }

    // =======================================================================
    // `auto` keyword: "left-to-right" initialization style

    class X {};

    class Foo {
    public:
        Foo() = default;
        Foo(int) {};
    };

    Foo createFooOject() { return {}; }

    void legacy_left_to_right_initialization_syntax()
    {
        auto var1 = 0;
        auto var2 = Foo{};
        auto var3 = createFooOject();
        auto var4 = std::mutex{};

        auto name = std::string{ "Hans" };
        auto anotherName = "Sepp";
        auto ptr = std::make_unique<Foo>(123);
        auto myLambda = [](auto n, auto m) { return n + m; };

        //X x1();
        // auto x2 = X();
    }

    // =======================================================================
    // is_transparent

    void legacy_is_transparent_01()
    {
        std::set<std::string> strings;

        std::string one{ "one" };
        strings.insert(one);
        strings.insert("two");   // is there a (performance) problem ???

        auto pos = strings.find("one");
    }

    void legacy_is_transparent_02()
    {
        // using is_transparent implicitly

        std::set<std::string, std::less<>> strings;  // std::less<> is transparent, look at source code of std::less<>

        strings.insert("one");
        strings.insert("two");

        auto pos = strings.find("one");
    }

    void legacy_is_transparent()
    {
        legacy_is_transparent_01();
        legacy_is_transparent_02();
    }

    // =======================================================================
    // std::string_view

    void legacy_string_view()
    {
        std::string s1 = "I'm more than 15 chars long - and reside on the heap";
        std::string_view s2 = "I'm more than 15 chars long - and reside not the heap";
    }

    // =======================================================================
    // std::string_view

    int adder(std::initializer_list<int> list)
    {
        return std::accumulate(list.begin(), list.end(), 0);
    }

    int adder(const std::vector<int>& list)
    {
        return std::accumulate(list.begin(), list.end(), 0);
    }

    void legacy_initializer_list()
    {
        int sum = adder({ 1, 2, 3, 4, 5 });
        std::println("{}", sum);
    }

    // =======================================================================
    // Move Semantics

    struct Handle {
        static int copies;
        Handle() { ++copies; }
        Handle(const Handle&) { ++copies; }   // legacy: used as a statistic
        Handle(Handle&&) noexcept = default;
        // ...
    };

    int Handle::copies = 0;

    void legacy_move_semantics_01()
    {
        Handle h1;
        Handle h2;

        Handle h = std::move(h1);
    }

    // double-free according to defaulted move c'tor

    class Buffer {
    public:
        Buffer() { m_data = new char [5] {}; }
        Buffer(Buffer&&) = default; // looks harmless
        ~Buffer() { delete[] m_data; }
    private:
        char* m_data;
    };

    void legacy_move_semantics_02()
    {
        Buffer buffer1;
        Buffer buffer2 = std::move(buffer1);  // crashes
    }

    // copy operation instead of moving

    struct Tracer {

        std::string name;

        Tracer(std::string n) : name{ std::move(n) } {}

        Tracer(const Tracer& other) : name(other.name) {
            std::println("copy {}", name);
        }

        Tracer(Tracer&& other) noexcept : name{ std::move(other.name) } {
            std::println("move");
        }
    };

    void legacy_move_semantics_03()
    {
        Tracer a{ "one" };
        Tracer b = std::move(a);        // prints "move"

        const Tracer c{ "two" };
        Tracer d = std::move(c);        // prints "copy two"
    }

    // copy operation instead of moving - one more example

    std::vector<std::string> members;

    void store(const std::string& s) {
        members.push_back(std::move(s));   // looks efficient, actually copies
    }

    // Option 1: take by value and move (good if you always keep a copy)
    //void store(std::string s) {
    //    members.push_back(std::move(s));   // moves - one solution
    //}

    // Option 2: provide overloads
    //void store(const std::string& s) { members.push_back(s); }
    //void store(std::string&& s) { members.push_back(std::move(s)); }

    void legacy_move_semantics_04()
    {
        std::string s("abc");        
        store(s);
        store("def");
    }

    // do not use std::move in combination with return

    std::unique_ptr<int> getValue()
    {
        std::unique_ptr<int> value{ std::make_unique<int>(100) };
        return value;               // RVO !!!
        // or
        //return std::move(value);  // Bad Style - RVO is prevented
    }

    void legacy_move_semantics_05()
    {
        std::unique_ptr<int> data = getValue();
    }

    void legacy_move_semantics()
    {
        legacy_move_semantics_01();
        // legacy_move_semantics_02();  // crashes intentionally
        legacy_move_semantics_03();
        legacy_move_semantics_04();
        legacy_move_semantics_05();
    }
}

// ===========================================================================

void main_legacy()
{
    legacy_null();
    legacy_inheritance_keyword_override();
    legacy_inheriting_constructors();
    legacy_auto_range_based_for_loop();
    legacy_enums();
    legacy_typedef_using();
    legacy_macros_constexpr();
    legacy_method_chaining();
    legacy_left_to_right_initialization_syntax();
    legacy_is_transparent();
    legacy_string_view();
    legacy_initializer_list();
    legacy_move_semantics();
}

// ===========================================================================
// End-of-File
// ===========================================================================

// =======================================================================
// Noch nicht behandelt

struct Alt {
    int x;
    Alt() {} // Benutzerdefiniert, tut nichts!
};

struct Neu {
    int x;
    Neu() = default; // Compiler-generiert
};

void legacy_default_ctor() {
    Alt a = Alt(); // a.x ist UNINITIALISIERT (Zufallswert im Speicher!)
    Neu n = Neu(); // n.x wird garantiert mit 0 initialisiert (Value-Initialization)
    Neu n2{};      // n.x wird garantiert mit 0 initialisiert (Value-Initialization)
}
