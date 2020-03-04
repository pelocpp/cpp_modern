// =====================================================================================
// Variadic Templates
// =====================================================================================

#include <iostream>
#include <string>

namespace VariadicTemplates {

    /* Erstes Beispiel für ein variadisches Template:
    */

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

        std::string stringConcat = adder(
            std::string("ABC"),
            std::string("DEF"),
            std::string("GHI"),
            std::string("JKL"),
            std::string("MNO")
        );
        std::cout << "String Concatenation: " << stringConcat << std::endl;
    }

    // =================================================================================

    // Ein variadisches Template in zwei Realisierungsvarianten:
    //
    // a) Eine rekursive Template Funktion
    // b) Eine nicht-rekursive Non-Template Funktion

    void print()
    {
    }

    template<typename T, typename... Types>
    void print(T firstArg, Types... args)
    {
        std::cout << firstArg << std::endl; // print first argument
        print(args...); // call print() for remaining arguments
    }

    // Oder:
    // a) Eine rekursive Template Funktion
    // b) Eine nicht-rekursive Template Funktion
    //
    // Man beachte: Wenn sich zwei Template Funktionen nur um das Parameter Pack
    // unterscheiden, wird - wenn möglich - die
    // Template Funktionen ohne Parameter Pack bevorzugt:

    //template<typename T>
    //void print(T arg)
    //{
    //    std::cout << arg << std::endl; // print passed argument
    //}

    //template<typename T, typename... Types>
    //void print(T firstArg, Types... args)
    //{
    //    print(firstArg); // call print() for first argument
    //    print(args...);  // call print() for remaining arguments
    //}

    void test_02()
    {
        std::string s("World");
        print(123.456, "Hello", s);

        // same as
        print<double, const char*, std::string>(123.456, "Hello", s);
    }
}

int main_variadic_templates_intro()
{
    using namespace VariadicTemplates;
    test_01();
    test_02();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
