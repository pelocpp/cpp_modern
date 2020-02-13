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

    void test_02() {

        const std::map<std::type_index, std::string> typeNames {
            { std::type_index(typeid(int)),          "int"},
            { std::type_index(typeid(long)),         "long"},
            { std::type_index(typeid(short)),        "short"},
            { std::type_index(typeid(char)),         "char"},
            { std::type_index(typeid(const char*)),  "const char*"},
            { std::type_index(typeid(float)),        "float"},
            { std::type_index(typeid(double)),       "double"},
            { std::type_index(typeid(bool)),         "bool"}
        };

        // classic C++
        std::map<std::type_index, std::string>::const_iterator it;
        for (it = typeNames.begin(); it != typeNames.end(); it++) {
            std::cout << "Value: " << it->second << std::endl;
        }

        // or C++11
        for (auto const& elem : typeNames) {
            std::cout << "Value: " << elem.second << std::endl;
        }

        // or C++17
        for (auto const& [key, value] : typeNames) {
            std::cout << "Value: " << value << std::endl;
        }
    }

    // Non-recursive template part (regular template)
    template <typename T>
    void listTypeNames(std::ostream & os, T val) { 

        static const std::map<std::type_index, std::string> typeNames{
            { std::type_index(typeid(int)),          "int"},
            { std::type_index(typeid(long)),         "long"},
            { std::type_index(typeid(short)),        "short"},
            { std::type_index(typeid(char)),         "char"},
            { std::type_index(typeid(const char*)),  "const char*"},
            { std::type_index(typeid(float)),        "float"},
            { std::type_index(typeid(double)),       "double"},
            { std::type_index(typeid(bool)),         "bool"}
        };

        const std::string typeName = typeNames.at(std::type_index(typeid(T)));
        os << typeName << " - value: " << val << '\n';
    }

    // Recursive template part
    // Note: ... specifies a so called 'parameter pack')
    template<typename First, typename ...Args>
    void listTypeNames(std::ostream & os, First first, Args ...args) {
        listTypeNames(os, first);    // non-recursive call with first element
        listTypeNames(os, args...);  // recursive call with remaining elements
    }

    void test_03() {

        // regular template invocation
        listTypeNames(std::cout, 3.1415);                      

        // recursive variadic template invocation
        listTypeNames(std::cout, (short) 123, 123, (long) 123, 3.14F, 3.14, 'A', "ABC", false);
    }

    template<typename ...Args>
    void printer(Args... args) {
        // binary left fold (init == ostream)
        (std::cout << ... << args) << std::endl;
    }

    // demonstrating fold expressions
    void test_04() {
        printer(1, 2, 3, "ABC", "DEF", "GHI");
    }

    template<typename ...Args>
    auto anotherAdder(Args ...args) {
        return (args + ... + 0);  // binary right fold (init == 0)
    }

    void test_05() {
        int sum = anotherAdder<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        std::cout << "Sum from 1 up to 10: " << sum << std::endl;
    }

    // demonstrating all four versions of folding expressions

    template<typename ...Args>
    auto anotherSubtracterBRF(Args ...args) {
        return (args - ... - 0);  // binary right fold (init == 0)
    }

    void test_06a() {
        // binary right fold: 1 - (2 - (3 - (4 - ( 5 - 0)))) = 3
        int result = anotherSubtracterBRF<int>(1, 2, 3, 4, 5);
        std::cout << "BRF: 1 - (2 - (3 - (4 - ( 5 - 0)))): " << result << std::endl;
    }

    // -----------------------------------------------------------------------

    template<typename ...Args>
    auto anotherSubtracterBLF(Args ...args) {
        return (0 - ... - args);  // binary left fold (init == 0)
    }

    void test_06b() {
        // binary left fold: ((((0 - 1) - 2) - 3) - 4) - 5 =  -15
        int result = anotherSubtracterBLF<int>(1, 2, 3, 4, 5);
        std::cout << "BLF: ((((0 - 1) - 2) - 3) - 4) - 5: " << result << std::endl;
    }

    // -----------------------------------------------------------------------

    template<typename ...Args>
    auto anotherSubtracterURF(Args ...args) {
        return (args - ...);  // unary right fold
    }

    void test_06c() {
        // unary right fold: 1 - (2 - (3 - (4 - 5))) = 3
        int result = anotherSubtracterURF<int>(1, 2, 3, 4, 5);
        std::cout << "URF: 1 - (2 - (3 - (4 - 5))): " << result << std::endl;
    }

    // ----------------------------------------------------------------------

    template<typename ...Args>
    auto anotherSubtracterULF(Args ...args) {
        return (... - args);  // unary left fold
    }

    void test_06d() {
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
    void test_07() {
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
    void test_08() {
        printerWithSeperator02(1, 2, 3, "ABC", "DEF", "GHI");
    }
}

int main_variadic_templates()
{
    using namespace VariadicTemplates;
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06a();
    test_06b();
    test_06c();
    test_06d();
    test_07();
    test_08();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
