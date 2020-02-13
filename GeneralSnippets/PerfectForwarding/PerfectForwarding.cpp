// =====================================================================================
// Perfect Forwarding
// =====================================================================================

#include <iostream>
#include "../Global/Dummy.h"

namespace PerfectForwarding {

    void overloaded(const int& arg) {
        std::cout << "By lvalue" << std::endl;
    }

    void overloaded(int&& arg) { 
        std::cout << "By rvalue" << std::endl;
    }

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
        forwarding(5);
        std::cout << "----------------------------" << std::endl;
        std::cout << "Caller passes lvalue:" << std::endl;
        int x = 5;
        forwarding(x);
    }

    void test_02() {
        std::cout << "Caller passes rvalue:" << std::endl;
        forwarding(Dummy(1));
        std::cout << "----------------------------" << std::endl;
        std::cout << "Caller passes lvalue:" << std::endl;
        Dummy dummy(1);
        forwarding(dummy);
    }
}

int main_perfect_forwarding() {
    using namespace PerfectForwarding;
    test_01();
    test_02();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
