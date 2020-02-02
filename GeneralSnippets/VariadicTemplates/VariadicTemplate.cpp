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

        std::string stringConcat = adder(std::string("ABC"), std::string("DEF"), std::string("GHI"), std::string("JKL"), std::string("MNO"));
        std::cout << "String Concatenation: " << stringConcat << std::endl;
    }

    void test_02() {

        const std::map<std::type_index, std::string> typeNames {
            { std::type_index(typeid(int)),  "int"},
            { std::type_index(typeid(long)),  "long"},
            { std::type_index(typeid(short)),  "short"},
            { std::type_index(typeid(char)),  "char"},
            { std::type_index(typeid(const char*)), "const char*"},
            { std::type_index(typeid(float)),  "float"},
            { std::type_index(typeid(double)),  "double"},
            { std::type_index(typeid(bool)),  "bool"}
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
            { std::type_index(typeid(int)),  "int"},
            { std::type_index(typeid(long)),  "long"},
            { std::type_index(typeid(short)),  "short"},
            { std::type_index(typeid(char)),  "char"},
            { std::type_index(typeid(const char*)), "const char*"},
            { std::type_index(typeid(float)),  "float"},
            { std::type_index(typeid(double)),  "double"},
            { std::type_index(typeid(bool)),  "bool"}
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
        (std::cout << ... << args) << std::endl;
    }

    template <typename... Args>
    void printerWithSeperator(Args... args)
    {
        std::string sep = " ";
        ((std::cout << args << sep), ...) << std::endl;
    }

    // demonstrating fold expressions
    void test_04() {

        printer(1, 2, 3, "ABC", "DEF", "GHI");
        printerWithSeperator(1, 2, 3, "ABC", "DEF", "GHI");
    }

    template<typename ...Args>
    auto anotherAdder(Args ...args)
    {
        return (args + ... + 0);
    }

    void test_05() {
        int sum = anotherAdder<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        std::cout << "Sum from 1 up to 10: " << sum << std::endl;
    }
}

int main_variadic_templates()
{
    using namespace VariadicTemplates;
    //test_01();
    //test_02();
    //test_03();
    test_04();
    test_05();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
