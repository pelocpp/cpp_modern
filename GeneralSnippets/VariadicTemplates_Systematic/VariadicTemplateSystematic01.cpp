// =====================================================================================
// Variadic Templates
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <type_traits>

namespace VariadicTemplatesSystematic {

    // Use case: Variadic Expressions / Variadische Ausdrücke
    //

    template<typename T>
    void print(T arg)
    {
        std::cout << arg << '\n'; // print passed argument
    }

    template<typename T, typename... Types>
    void print(T firstArg, Types... args)
    {
        print(firstArg); // call print() for first argument
        print(args...);  // call print() for remaining arguments
    }

    template<typename... T>
    void printDoubled(T const&... args)
    {
        print((args + args)...);
        // same as
        print(args + args...);
    }

    template<typename... T>
    void printFiveTimes(T const&... args)
    {
        print(5 * args...);
    }

    template<typename... T>
    void printPlusOne(T const&... args)
    {
        print(args  +1 ...);    // works
        // print(args + 1...);  // doesn't compile: integer literal with too many decimal points
        // print((args + 1) ...);  // works
    }

    void test_01()
    {
        printDoubled(7.5);

        printFiveTimes(1, 2, 3, 4, 5);

        printPlusOne(1, 5, 10);
    }

    // Use case: Variadic Expressions with Indices / Variadische Ausdrücke mit Indizes
    //
    
    template <typename T, typename ...IDX>
    void printElements(const T& container, IDX ...index) {
    
        print(container[index] ...);
    }
    
    void test_02()
    {
        std::vector<std::string> numbers{ "one", "two", "three", "four", "five" };
        printElements(numbers, 4, 3, 2);
    
        std::string s{ "0123456789" };
        printElements(s, 8, 6, 4, 2, 0);
    }

    // Use case: Compile-Time Expression with Variadic Expressions
    //

    template<typename T, typename... TREST>
    constexpr bool isHomogeneous(T, TREST...)
    {
        return (std::is_same<T, TREST>::value && ...); // since C++17: folding expression !!!
    }

    void test_03()
    {
        bool result = isHomogeneous(43, -1, "hello");
        std::cout << std::boolalpha << result << std::endl;

        // expands to: 

        result = std::is_same<int, int>::value && std::is_same<int, char const*>::value;
        std::cout << std::boolalpha << result << std::endl;

        result = isHomogeneous(123, 456, 789);
        std::cout << std::boolalpha << result << std::endl;

        // expands to: 

        result = std::is_same<int, int>::value && std::is_same<int, int>::value;
        std::cout << std::boolalpha << result << std::endl;
    }
}

int main_variadic_templates()
{
    using namespace VariadicTemplatesSystematic;
    test_01();
    test_02();
    test_03();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
