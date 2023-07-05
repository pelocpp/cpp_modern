// =====================================================================================
// PerfectForwarding.cpp // Perfect Forwarding
// =====================================================================================

module modern_cpp:perfect_forwarding;

namespace PerfectForwarding {

    void overloaded(int& arg) {
        std::cout << "By lvalue: " << arg << std::endl;
    }

    void overloaded(int&& arg) {
        std::cout << "By rvalue: " << arg << std::endl;
    }

    /*
     * Note: "T&&" with "T" being template parameter is special:
     *       It adjusts "T" to be (for example) "int&" or non-ref "int" so std::forward knows what to do.
     */

    template <typename T>
    void forwarding(T&& arg) {
        overloaded(arg);
    }

    template <typename T>
    void forwardingPerfect(T&& arg) {
        overloaded(std::forward<T>(arg));
    }

    void test_forwarding() {

        int n{ 123 };
        forwarding(n);

        forwarding(456);
    }

    void test_forwardingPerfect() {

        int n{ 123 };
        forwardingPerfect(n);

        forwardingPerfect(456);
    }

    void test_01() {
        test_forwarding();
        // test_forwardingPerfect();
    }
}

void main_perfect_forwarding()
{
    using namespace PerfectForwarding;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
