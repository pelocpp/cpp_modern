// =====================================================================================
// Variadic Templates
// =====================================================================================

#include <iostream>
#include <map>
#include <typeinfo>
#include <typeindex>

namespace VariadicTemplates {

    // Non-recursive template part (regular template)
    template<typename T>
    T adder(T v) {
        return v;
    }

    // Recursive template part
    // Note: ... specifies a so called 'parameter pack')
    template<typename T, typename ...Args>
    T adder(T first, Args... args) {
        return first + adder(args...);
    }

    void test_01() {

        int sum = adder(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        std::cout << "Sum from 1 up to 10: " << sum << std::endl;

        std::string stringConcat = adder (
            std::string("ABC"),
            std::string("DEF"), 
            std::string("GHI"), 
            std::string("JKL"),
            std::string("MNO")
        );
        std::cout << "String Concatenation: " << stringConcat << std::endl;
    }

    template<typename ...Args>
    void printer(Args... args) {
        // binary left fold (init == ostream)
        (std::cout << ... << args) << std::endl;
    }

    // demonstrating fold expressions
    void test_02() {
        printer(1, 2, 3, "ABC", "DEF", "GHI");
    }

    template<typename ...Args>
    auto anotherAdder(Args ...args) {
        return (args + ... + 0);  // binary right fold (init == 0)
    }

    void test_03() {
        int sum = anotherAdder<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        std::cout << "Sum from 1 up to 10: " << sum << std::endl;
    }

    // demonstrating all four versions of folding expressions

    template<typename ...Args>
    auto anotherSubtracterBRF(Args ...args) {
        return (args - ... - 0);  // binary right fold (init == 0)
    }

    void test_04a() {
        // binary right fold: 1 - (2 - (3 - (4 - ( 5 - 0)))) = 3
        int result = anotherSubtracterBRF<int>(1, 2, 3, 4, 5);
        std::cout << "BRF: 1 - (2 - (3 - (4 - ( 5 - 0)))): " << result << std::endl;
    }

    // -----------------------------------------------------------------------

    template<typename ...Args>
    auto anotherSubtracterBLF(Args ...args) {
        return (0 - ... - args);  // binary left fold (init == 0)
    }

    void test_04b() {
        // binary left fold: ((((0 - 1) - 2) - 3) - 4) - 5 =  -15
        int result = anotherSubtracterBLF<int>(1, 2, 3, 4, 5);
        std::cout << "BLF: ((((0 - 1) - 2) - 3) - 4) - 5: " << result << std::endl;
    }

    // -----------------------------------------------------------------------

    template<typename ...Args>
    auto anotherSubtracterURF(Args ...args) {
        return (args - ...);  // unary right fold
    }

    void test_04c() {
        // unary right fold: 1 - (2 - (3 - (4 - 5))) = 3
        int result = anotherSubtracterURF<int>(1, 2, 3, 4, 5);
        std::cout << "URF: 1 - (2 - (3 - (4 - 5))): " << result << std::endl;
    }

    // ----------------------------------------------------------------------

    template<typename ...Args>
    auto anotherSubtracterULF(Args ...args) {
        return (... - args);  // unary left fold
    }

    void test_04d() {
        // unary left fold: ((((1 - 2) - 3) - 4) - 5 = -13
        int result = anotherSubtracterULF<int>(1, 2, 3, 4, 5);
        std::cout << "URF: ((((1 - 2) - 3) - 4) - 5: " << result << std::endl;
    }

    // -----------------------------------------------------------------------

    // Folding over a comma (',' operator)

    template <typename... Args>
    void printerWithSeperator(Args... args) {
        std::string sep = " ";
        ((std::cout << args << sep), ...) << std::endl;
    }

    // demonstrating fold expressions
    void test_05() {
        printerWithSeperator(1, 2, 3, "ABC", "DEF", "GHI");
    }

    // -----------------------------------------------------------------------

    // Folding over a comma - pack arguments can be handled by a separate function

    template <typename T>
    std::ostream& handleArg(T arg) {
        std::cout << arg << "-";
        return std::cout;
    }

    template <typename... Args>
    void printerWithSeperator02(Args... args) {
        (handleArg(args), ...) << std::endl;
    }

    // demonstrating fold expressions
    void test_06() {
        printerWithSeperator02(1, 2, 3, "ABC", "DEF", "GHI");
    }
}

int main_variadic_templates()
{
    using namespace VariadicTemplates;
    test_01();
    test_02();
    test_03();
    test_04a();
    test_04b();
    test_04c();
    test_04d();
    test_05();
    test_06();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
