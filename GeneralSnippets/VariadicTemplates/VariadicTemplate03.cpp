// =====================================================================================
// Variadic Templates
// =====================================================================================

#include <iostream>
#include <map>
#include <typeinfo>
#include <typeindex>

namespace VariadicTemplates03 {

    void test_01() {

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

    void test_02() {

        // regular template invocation
        listTypeNames(std::cout, 3.1415);                      

        // recursive variadic template invocation
        listTypeNames(std::cout, (short) 123, 123, (long) 123, 3.14F, 3.14, 'A', "ABC", false);
    }
}

int main_variadic_templates_02()
{
    using namespace VariadicTemplates03;
    test_01();
    test_02();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
