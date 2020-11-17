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

    template <typename... TARGS>
    void doSomethingForAll(const TARGS& ... args) {
        std::initializer_list<int> list = { (doSomething(args), 0)... };
    }

    // doesn't compile
    //template <typename... TARGS>
    //void doSomethingForAll(const TARGS& ... args) {
    //    doSomething(args)...;
    //}

    void test_01() {
        doSomethingForAll(1, '!', std::string("ABC"), 5.5);
        std::cout << std::endl;
    }

    template <typename HEAD, typename... TAIL>
    void print(const HEAD& head, const TAIL&... tail) {
        std::cout << head;
        if constexpr (sizeof...(tail) > 0) {
            std::cout << ", ";
            print(tail...);
        }
    }

    void test_02() {
        print(1, '!', std::string("ABC"), 5.5);
        std::cout << std::endl;
    }
}

void main_variadic_templates_working_on_every_argument()
{
    using namespace VariadicTemplatesWorkingOnEveryArgument;
    test_01();
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
