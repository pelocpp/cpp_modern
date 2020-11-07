// =====================================================================================
// Function Templates
// =====================================================================================

#include <iostream>

namespace FunctionTemplatesBasics {

    template <typename T>
    void printValue(T const& t)
    {
        std::cout << "Value: " << t << std::endl;
    }

    // put this template into comments if type deduction is going to be demonstrated
    template <>
    void printValue<bool>(bool const& b)
    {
        std::cout << std::boolalpha << "Value: " << b << std::endl;
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

void main_function_templates_basics()
{
    using namespace FunctionTemplatesBasics;
    test_01();
    test_02();
    test_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
