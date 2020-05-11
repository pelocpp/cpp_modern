// =====================================================================================
// Variadic Templates - Working on every argument
// =====================================================================================

#include <iostream>
#include <variant>
#include <string>

namespace VariadicTemplatesWorkingOnEveryArgument {

    // https://arne-mertz.de/2016/11/more-variadic-templates/

    template <typename T>
    void doSomething(const T& value) {
        std::cout << "got value " << value << std::endl;
    }

    template <class... ARGS>
    void doSomethingForAll(ARGS const&... args) {
        std::initializer_list<int> list = { (doSomething(args), 0)... };
    }

    void test_01() {
        doSomethingForAll(1, '!', std::string("ABC"), 5.5);
    }

    template <class Head, class... Tail>
    void print(const Head& head, const Tail&... tail) {
        std::cout << head;
        if constexpr (sizeof...(tail) > 0) {
            std::cout << ", ";
            print(tail...);
        }
    }

    void test_02() {
        print(1, '!', std::string("ABC"), 5.5);
    }

    template <class Head, class... Tail>
    void print1(const Head& head, const Tail&... tail) {
        std::cout << head;
        (void)std::initializer_list<int>{ ((std::cout << ", " << tail), 0)... };
    }

    void test_03() {
        print1(1, '!', std::string("ABC"), 5.5);
    }
}

int main_working_on_every_argument()
{
    using namespace VariadicTemplatesWorkingOnEveryArgument;
    test_01();
    std::cout << std::endl;
    test_02();
    std::cout << std::endl;
    test_03();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
