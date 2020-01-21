// =====================================================================================
// Perfect Forwarding
// =====================================================================================

#include <iostream>

namespace PerfectForwarding {

    void overloaded(int const& arg) {
        std::cout << "By lvalue" << std::endl;
    }

    void overloaded(int&& arg) { 
        std::cout << "By rvalue" << std::endl;
    }

    /*
     * Note: "T&&" with "T" being template param is special:
     *       It adjusts "T" to be (for example) "int &" or non-ref "int" so std::forward knows what to do.
     */

    template <typename T>
    void forwarding(T&& arg) {
        std::cout << "via std::forward: ";
        overloaded(std::forward<T>(arg));
        std::cout << "via std::move: ";
        overloaded(std::move(arg));  // conceptually this would invalidate arg
        std::cout << "By simple passing: ";
        overloaded(arg);
    }

    void test_01_perfect_forwarding() {
        std::cout << "initial caller passes rvalue:" << std::endl;
        forwarding(5);
        std::cout << "initial caller passes lvalue:" << std::endl;
        int x = 5;
        forwarding(x);
    }
}

int main_perfect_forwarding() {

    using namespace PerfectForwarding;

    test_01_perfect_forwarding();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
