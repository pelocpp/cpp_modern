// =====================================================================================
// PerfectForwarding.cpp // Perfect Forwarding
// =====================================================================================

module modern_cpp:perfect_forwarding;

namespace PerfectForwarding {

    static void overloaded(int& arg) {
        std::cout << "By lvalue: " << arg << std::endl;
    }

    static void overloaded(int&& arg) {
        std::cout << "By rvalue: " << arg << std::endl;
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

    static void test_forwarding() {

        int n{ 123 };

        forwarding(n);

        forwarding(456);
    }

    static void test_forwardingPerfect() {

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
        std::cout << arg1 << std::endl;

        T obj2 = std::forward<U>(arg2);
        std::cout << arg2 << std::endl;
    }

    static void test_example()
    {
        using namespace std::string_literals;

        std::string s{ "DEF" };
        std::cout << s << std::endl;

        foo(std::string{ "ABC" }, s);
    }
}

void main_perfect_forwarding()
{
    using namespace PerfectForwarding;
    test_forwarding();
    test_forwardingPerfect();
    test_example();
}

// =====================================================================================
// End-of-File
// =====================================================================================
