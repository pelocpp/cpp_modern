// =====================================================================================
// PerfectForwarding03.cpp // Perfect Forwarding 03
// =====================================================================================

module modern_cpp:perfect_forwarding;

namespace PerfectForwarding03 {

    void overloaded(int& arg) {
        std::cout << "By lvalue" << std::endl;
    }

    void overloaded(int&& arg) {
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

    static void test_01() {
        std::cout << "Caller passes rvalue:" << std::endl;
        forwarding(5);
        std::cout << "----------------------------" << std::endl;
        std::cout << "Caller passes lvalue:" << std::endl;
        int x = 5;
        forwarding(x);
    }
}

void main_perfect_forwarding_03()
{
    using namespace PerfectForwarding03;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
