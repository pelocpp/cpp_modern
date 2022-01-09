// =====================================================================================
// Variadic Templates
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <type_traits>

// =====================================================================================
// Inhalt:
// - Variadic Expressions / Variadische Ausdrücke
// - Variadische Templates mit Zugriff auf Basisklasse und 'using'
// - Variadic Expressions with Indices / Variadische Ausdrücke mit Indizes
// =====================================================================================

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

    // =====================================================================================
    // =====================================================================================

    // Use case: Variadic Base Classes and keyword 'using'
    // Several implementations of a method (e.g. operator())
    // can be reached from the corresponding base class 

    class Customer
    {
    private:
        std::string m_name;
    public:
        Customer(const std::string& name) : m_name(name) { }
        std::string getName() const { return m_name; }
    };

    struct CustomerEquals {
        bool operator() (const Customer& c1, const Customer& c2) const {
            std::cout << "isEqual" << std::endl;
            return c1.getName() == c2.getName();
        }
    };

    struct CustomerHash {
        std::size_t operator() (Customer const& c) const {
            std::cout << "hash" << std::endl;
            return std::hash<std::string>()(c.getName());
        }
    };

    template<typename... RULES>
    struct CustomerRules : RULES...
    {
        using RULES::operator() ... ; // C++17
    };

    void test_02()
    {
        using Rules = CustomerRules<CustomerEquals, CustomerHash>;

        Rules rules;

        Customer hans("Hans");
        Customer sepp("Sepp");

        bool result = rules(hans, sepp);
        std::cout << "rules(hans, sepp) => " << result << std::endl;

        size_t hashHans = rules(hans);
        std::cout << "rules(hans) => " << hashHans << std::endl;

        size_t hashSepp = rules(sepp);
        std::cout << "rules(sepp) => " << hashSepp << std::endl;
    }

    // =====================================================================================
    // =====================================================================================

    // Use case: Variadic Expressions with Indices / Variadische Ausdrücke mit Indizes
    //
    
    template <typename T, typename ...IDX>
    void printElements(const T& container, IDX ...index) {
    
        print(container[index] ...);
    }
    
    void test_03()
    {
        std::vector<std::string> numbers{ "one", "two", "three", "four", "five" };
        printElements(numbers, 4, 3, 2);
    
        std::string s{ "0123456789" };
        printElements(s, 8, 6, 4, 2, 0);
    }
}

void main_variadic_templates_more_examples()
{
    using namespace VariadicTemplatesSystematic;

    test_01();  // Variadic Expressions
    test_02();  // Variadic Base Classes and keyword 'using'
    test_03();  // Variadic Expressions with Indices 
}

// =====================================================================================
// End-of-File
// =====================================================================================
