// ===========================================================================
// LegacyToModernity.cpp
// ===========================================================================

module;

#include <cstddef>
#include <print>

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

        static void legacy_inheritance_keyword_override()
        {
            Base base;
            Derived derived;
            std::println("Compiles successfully");

            Base* bp;
            bp = &derived;
            bp->func();
        }
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
            using Base::Base;      // inherits Base(int) and Base(int, const std::string&)
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

        std::vector<Person>::const_iterator it = persons.begin();  // iterator type must be manually adjusted

        auto it2 = persons.begin();                                // iterator type is deducted automatically  - at compile time
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
    // Method Chaining

    void legacy_method_chaining()
    {
        std::string s = "I have even sold some";
        s.replace(0, 6, "").replace(s.find("even"), 4, "only");

        std::println("{}", s);
    }

    // =======================================================================
    // std::string_view

    void legacy_string_view()
    {
        std::string s1 = "I'm more than 15 chars long - and reside on the heap";
        std::string_view s2 = "I'm more than 15 chars long - and reside not the heap";
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

    // double-free according to defaulted move c'tor

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

    std::unique_ptr<int> getValue()
    {
        std::unique_ptr<int> value{ std::make_unique<int>(100) };
        return value;               // RVO !!!
        // or
        //return std::move(value);  // Bad Style - RVO is prevented
    }

    void legacy_move_semantics_04()
    {
        std::unique_ptr<int> data = getValue();
    }

    void legacy_move_semantics()
    {
        //legacy_move_semantics_01();
        //legacy_move_semantics_02();
       // legacy_move_semantics_03();
        legacy_move_semantics_04();
    }
}

// ===========================================================================

void main_legacy()
{
//    legacy_null();
//    legacy_inheritance_keyword_override();
     legacy_inheriting_constructors();
//    legacy_auto_range_based_for_loop();
//    legacy_enums();
//    legacy_default_ctor();
//    legacy_method_chaining();
//    legacy_move_semantics();
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
