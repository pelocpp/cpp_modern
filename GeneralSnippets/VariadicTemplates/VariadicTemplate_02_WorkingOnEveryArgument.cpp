// =====================================================================================
// VariadicTemplate_02_WorkingOnEveryArgument.cpp // Working on every argument
// =====================================================================================

module modern_cpp:variadic_templates;

namespace VariadicTemplatesWorkingOnEveryArgument {

    // ====================================================================
    // 1. Beispiel:
    // Parameter Pack Expansion mit Hilfe von std::initializer_list
    // ====================================================================

    template <typename T>
    void doSomething(const T& value) {
        std::cout << "got value " << value << std::endl;
    }

    // doesn't compile
    //template <typename... TArgs>
    //void doSomethingForAll(const TArgs& ... args) {
    //    doSomething(args)...;
    //}

    template <typename... TArgs>
    void doSomethingForAll(const TArgs& ... args) {
        // std::initializer_list<int> list = { (doSomething(args), 0)... };
        std::initializer_list<int> { (doSomething(args), 0)... };
    }

    static void test_01() {
        doSomethingForAll(1, '!', std::string("ABC"), 5.5);
        std::cout << std::endl;
    }

    // ====================================================================
    // 2. Beispiel:
    // C++ 17 constexpr if
    // Beispiel mit "Trailing Comma"
    // ====================================================================

    // ====================================================================
    // 1. Variante: 
    // print-Funktion mit 2 Überladungen
    // ====================================================================

    static void print() {}

    template <typename Head, typename ... Tail>
    void print(Head head, Tail ... tail)
    {
        std::cout << head << ", ";
        print(tail ...);
    }

    static void test_02_01() {
        print(1, '!', std::string("ABC"), 5.5);
        std::cout << std::endl;
    }

    // ====================================================================
    // 2. Variante: 
    // print-Funktion in einer Überladung und mit constexpr
    // ====================================================================

    template <typename Head, typename... Tail>
    void printEx(const Head& head, const Tail&... tail) {
        std::cout << head;
        if constexpr (sizeof...(tail) > 0) {
            std::cout << ", ";
            printEx(tail...);
        }
    }

    static void test_02_02() {
        printEx(1, '!', std::string("ABC"), 5.5);
        std::cout << std::endl;
    }
}

void main_variadic_templates_working_on_every_argument()
{
    using namespace VariadicTemplatesWorkingOnEveryArgument;
    test_01();
    test_02_01();
    test_02_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
