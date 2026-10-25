// =====================================================================================
// PerfectForwarding.cpp // Perfect Forwarding
// =====================================================================================

module modern_cpp:perfect_forwarding;

import std;

namespace {

    void overloaded(const int& arg) {
        std::println("By lvalue: {}", arg);
    }

    void overloaded(int&& arg) {
        std::println("By rvalue: {}", arg);
    }

    /*
     * Note: "T&&" with "T" being template parameter is special: Universal Reference
     */

    template <typename T>
    void forwarding(T&& arg) {
        overloaded(arg);
    }

    template <typename T>
    void forwardingPerfect(T&& arg) {
        overloaded(std::forward<T>(arg));
    }

    void forwarding() {

        int n{ 123 };

        forwarding(n);

        forwarding(456);
    }

    void forwarding_perfect() {

        int n{ 123 };

        forwardingPerfect(n);

        forwardingPerfect(456);
    }

    // =================================================================================

    template <typename T, typename U>
    void foo(T&& arg1, U&& arg2)
    {
        // Beobachte den Inhalt der beiden Parameter 'arg1' und 'arg2'

        // T obj1 = std::forward<T>(arg1);
        // vs
        T obj1 = arg1;
        std::println("[{}]", arg1);

        U obj2 = std::forward<U>(arg2);
        std::println("[{}]", arg2);
    }

    void forwarding_perfect_second_example()
    {
        std::string s{ "DEF" };

        foo(std::string{ "ABC" }, s);
    }
}

void main_perfect_forwarding()
{
    forwarding();
    forwarding_perfect();
    forwarding_perfect_second_example();
}

// =====================================================================================
// End-of-File
// =====================================================================================
