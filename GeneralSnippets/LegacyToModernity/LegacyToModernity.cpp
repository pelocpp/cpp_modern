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

    // =======================================================================
    // Method Chaining

    int legacy_method_chaining()
    {
        std::string s = "I have even sold some";
        s.replace(0, 6, "").replace(s.find("even"), 4, "only");

        std::println("{}", s);
        return 0;
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

    void legacy_move_semantics()
    {
        legacy_move_semantics_01();
        legacy_move_semantics_02();
    }
}

// ===========================================================================

void main_legacy()
{
    legacy_null();
    legacy_auto_range_based_for_loop();
    legacy_enums();
    legacy_default_ctor();
    legacy_method_chaining();
    legacy_move_semantics();
}

// ===========================================================================
// End-of-File
// ===========================================================================
