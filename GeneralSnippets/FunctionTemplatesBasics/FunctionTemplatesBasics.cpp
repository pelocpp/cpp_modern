#include <iostream>

// =====================================================================================
// Funktionstemplates
// =====================================================================================

namespace FunctionTemplatesBasics {

    template <typename T>
    void printValue(T const& t)
    {
        std::cerr << "Value: " << t << std::endl;
    }

    template <>
    void printValue<bool>(bool const& b)
    {
        std::cerr << "Value: " << (b ? "true" : "false") << std::endl;
    }

    void test_01() {
        printValue<int>(10);
        printValue<bool>(true);
        printValue<double>(12.5);
    }

    void test_02() {
        printValue<>(10);
        printValue<>(true);
        printValue<>(12.5);
    }

    void test_03() {
        printValue(10);
        printValue(true);
        printValue(12.5);
    }
}

int main_function_templates_basics()
{
    using namespace FunctionTemplatesBasics;

    test_01();
    test_02();
    test_03();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
