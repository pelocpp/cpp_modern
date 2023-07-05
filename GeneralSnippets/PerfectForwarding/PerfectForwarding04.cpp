// =====================================================================================
// PerfectForwarding04.cpp // Perfect Forwarding 04
// =====================================================================================

module modern_cpp:perfect_forwarding;

import :dummy;

namespace PerfectForwarding04 {

    void overloaded(const Dummy& arg) {
        std::cout << "By lvalue" << std::endl;
    }

    void overloaded(Dummy&& arg) {
        // move-semantics should be applied here
        std::cout << "By rvalue" << std::endl;
    }

    /*
     * Note: "T&&" with "T" being template param is special:
     *       It adjusts "T" to be (for example) "int&" or non-ref "int" so std::forward knows what to do.
     */

    template <typename T>
    void forwarding(T&& arg) {
        std::cout << "By simple passing: ";
        overloaded(arg);
        std::cout << "Via std::move: ";
        overloaded(std::move(arg));  // conceptually this would invalidate arg
        std::cout << "Via std::forward: ";
        overloaded(std::forward<T>(arg));
    }

    void test_01() {
        std::cout << "Caller passes rvalue:" << std::endl;
        forwarding(Dummy(1));
        std::cout << "----------------------------" << std::endl;
        std::cout << "Caller passes lvalue:" << std::endl;
        Dummy dummy(1);
        forwarding(dummy);
    }
}

void main_perfect_forwarding_04()
{
    using namespace PerfectForwarding04;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
