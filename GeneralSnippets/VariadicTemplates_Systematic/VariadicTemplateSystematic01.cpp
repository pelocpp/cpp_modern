// =====================================================================================
// Variadic Templates
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

namespace VariadicTemplatesSystematic {

    // Beispiele für variadische Ausdrücke
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

    // Beispiele für variadische Ausdrücke mit Indizes
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
}

// int main_variadic_templates_intro()
int main()
{
    using namespace VariadicTemplatesSystematic;
    // test_01();
    test_02();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
