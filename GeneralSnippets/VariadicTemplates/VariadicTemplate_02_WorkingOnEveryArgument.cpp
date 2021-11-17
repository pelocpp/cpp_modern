// =====================================================================================
// Variadic Templates - Working on every argument
// =====================================================================================

#include <iostream>
#include <variant>
#include <string>

namespace VariadicTemplatesWorkingOnEveryArgument {

    template <typename T>
    void doSomething(const T& value) {
        std::cout << "got value " << value << std::endl;
    }

    // doesn't compile
    //template <typename... TARGS>
    //void doSomethingForAll(const TARGS& ... args) {
    //    doSomething(args)...;
    //}

    template <typename... TARGS>
    void doSomethingForAll(const TARGS& ... args) {
        // std::initializer_list<int> list = { (doSomething(args), 0)... };
        std::initializer_list<int> { (doSomething(args), 0)... };
    }

    void test_01() {
        doSomethingForAll(1, '!', std::string("ABC"), 5.5);
        std::cout << std::endl;
    }

    // ================================================================

    void print() {}

    template <typename HEAD, typename ... TAIL>
    void print(HEAD value, TAIL ... rest)
    {
        std::cout << value << ", ";
        print(rest ...);
    }

    void test_02() {
        print(1, '!', std::string("ABC"), 5.5);
        std::cout << std::endl;
    }

    template <typename HEAD, typename... TAIL>
    void printEx(const HEAD& head, const TAIL&... tail) {
        std::cout << head;
        if constexpr (sizeof...(tail) > 0) {
            std::cout << ", ";
            printEx(tail...);
        }
    }

    void test_03() {
        printEx(1, '!', std::string("ABC"), 5.5);
        std::cout << std::endl;
    }
}

void main_variadic_templates_working_on_every_argument()
{
    using namespace VariadicTemplatesWorkingOnEveryArgument;
   //test_01();
    test_02();
    test_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
