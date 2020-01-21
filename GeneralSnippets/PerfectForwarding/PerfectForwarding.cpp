// =====================================================================================
// Perfect Forwarding
// =====================================================================================

#include <iostream>

namespace PerfectForwarding {

    void overloaded(int const& arg) {
        std::cout << "by lvalue" << std::endl;
    }

    void overloaded(int&& arg) { 
        std::cout << "by rvalue" << std::endl;
    }

    template< typename t >
    /* "t &&" with "t" being template param is special, and  adjusts "t" to be
       (for example) "int &" or non-ref "int" so std::forward knows what to do. */
    void forwarding(t&& arg) {
        std::cout << "via std::forward: ";
        overloaded(std::forward< t >(arg));
        std::cout << "via std::move: ";
        overloaded(std::move(arg)); // conceptually this would invalidate arg
        std::cout << "by simple passing: ";
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
