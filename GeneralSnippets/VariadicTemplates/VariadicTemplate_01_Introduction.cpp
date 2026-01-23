// ========================================================================
// VariadicTemplate_01_Introduction.cpp // Variadic Templates: Introduction
// ========================================================================

module modern_cpp:variadic_templates;

namespace VariadicTemplatesIntro_01 {

    // ====================================================================
    // 1. Beispiel für ein variadisches Template:
    // Eine print-Funktion mit beliebig vielen Argumenten
    // ====================================================================

    // Non-recursive template part (regular template)
    template <typename T>
    void print(T value)
    {
        std::cout << value << " ";
    }

    // Recursive template part
    template <typename T, typename ... TRest>
    void print(T n, TRest ... rest)
    {
        print<T>(n);
        print<TRest...>(rest ...);
    }

    // Generische Funktionsschreibweise (C++ 20)
    static void print_ex(auto value)
    {
        std::cout << value << " ";
    }

    // Generische Funktionsschreibweise (C++ 20) - rekursiver Anteil
    static void print_ex(auto n, auto ... rest)
    {
        print_ex(n);
        print_ex(rest ...);
    }

    static void test_printer_01()
    {
        print<int, int, int, int, int>(1, 2, 3, 4, 5);

        print_ex<int, int, int, int, int>(1, 2, 3, 4, 5);
    }
}

namespace VariadicTemplates_TestClassDoSomething {

    // ========================================================================
    // Test-Klasse DoSomething
    // Nur die Konstruktoren sind interessant
    // ========================================================================

    class DoSomething {
    private:
        int m_var1;
        int m_var2;
        int m_var3;

    public:
        DoSomething() : m_var1{}, m_var2{}, m_var3{} {
            std::cout << "c'tor()" << std::endl;
        }

        DoSomething(int n) : m_var1{ n }, m_var2{}, m_var3{} {
            std::cout << "c'tor(int)" << std::endl;
        }

        DoSomething(int n, int m) : m_var1{ n }, m_var2{ m }, m_var3{} {
            std::cout << "c'tor(int, int)" << std::endl;
        }

        DoSomething(int n, int m, int k) : m_var1{ n }, m_var2{ m }, m_var3{ k } {
            std::cout << "c'tor(int, int, int)" << std::endl;
        }

        friend std::ostream& operator<< (std::ostream&, const DoSomething&);
    };

    std::ostream& operator<< (std::ostream& os, const DoSomething& obj) {
        os
            << "var1: " << obj.m_var1
            << ", var2: " << obj.m_var2
            << ", var3: " << obj.m_var3;

        return os;
    }
}

namespace VariadicTemplatesIntro_02 {

    // =============================================================
    // 2. Beispiel für ein variadisches Template:
    // Anwendungsfall: Standardfunktion std::unique_ptr<>
    // =============================================================

    using namespace VariadicTemplates_TestClassDoSomething;

    // einfache Variante
    template<typename T, typename ... TArgs>
    std::unique_ptr<T> my_make_unique(TArgs ... args)
    {
        return std::unique_ptr<T>{ new T{ args... } };
    }

    // bessere Variante: Mit Universal Referenz
    template<typename T, typename ... TArgs>
    std::unique_ptr<T> my_make_unique_ex(TArgs&&... args)
    {
        return std::unique_ptr<T>{ new T{ std::forward<TArgs>(args)... } };
    }

    // noch bessere Variante: Generische Funktionsschreibweise (C++ 20)
    // Siehe auch:
    // https://en.cppreference.com/w/cpp/utility/forward
    template <typename T>
    std::unique_ptr<T> my_make_unique_ex_ex(auto&& ... args)
    {
        std::unique_ptr<T> tmp{ new T{ std::forward<decltype(args)>(args) ... } };
        return tmp;
    }

    static void test_my_make_unique()
    {
        std::unique_ptr<DoSomething> up1 = my_make_unique<DoSomething>();
        std::unique_ptr<DoSomething> up2 = my_make_unique<DoSomething>(1);
        std::unique_ptr<DoSomething> up3 = my_make_unique<DoSomething>(10, 11);
        std::unique_ptr<DoSomething> up4 = my_make_unique<DoSomething>(100, 101, 102);

        int n = 33, m = 34;
        std::unique_ptr<DoSomething> up5 = my_make_unique<DoSomething>(n, m);
    }

    static void test_my_make_unique_ex()
    {
        std::unique_ptr<DoSomething> up1 = my_make_unique_ex<DoSomething>();
        std::unique_ptr<DoSomething> up2 = my_make_unique_ex<DoSomething>(1);
        std::unique_ptr<DoSomething> up3 = my_make_unique_ex<DoSomething>(10, 11);
        std::unique_ptr<DoSomething> up4 = my_make_unique_ex<DoSomething>(100, 101, 102);

        int n = 33, m = 34;
        std::unique_ptr<DoSomething> up5 = my_make_unique_ex<DoSomething>(n, m);
    }

    static void test_my_make_unique_ex_ex()
    {
        std::unique_ptr<DoSomething> up1 = my_make_unique_ex_ex<DoSomething>();
        std::unique_ptr<DoSomething> up2 = my_make_unique_ex_ex<DoSomething>(1);
        std::unique_ptr<DoSomething> up3 = my_make_unique_ex_ex<DoSomething>(10, 11);
        std::unique_ptr<DoSomething> up4 = my_make_unique_ex_ex<DoSomething>(100, 101, 102);

        int n = 33, m = 34;
        std::unique_ptr<DoSomething> up5 = my_make_unique_ex_ex<DoSomething>(n, m);
    }
}

namespace VariadicTemplatesIntro_03 {

    // =================================================================================
    // 3. Beispiel für ein variadisches Template:
    // 
    // Anwendungsfall: "Generische Funktion 'make_an_object'"
    //                 Umsetzung Parameter Pack auf einen passenden Konstruktor
    // 
    // Siehe Analogien zu Factory-Pattern
    // =================================================================================

    using namespace VariadicTemplates_TestClassDoSomething;

    // einfache Variante
    template<typename T, typename... TArgs>
    T make_an_object(const TArgs&... args)
    {
        return T{ args... };
    }

    // bessere Variante: Mit Universal Referenz
    template<typename T, typename... TArgs>
    T make_an_object_ex(TArgs&&... args)
    {
        return T{ std::forward<TArgs>(args)... };
    }

    static void test_make_an_object()
    {
        DoSomething u1 = make_an_object<DoSomething>();
        DoSomething u2 = make_an_object<DoSomething>(1);
        DoSomething u3 = make_an_object<DoSomething>(10, 11);
        DoSomething u4 = make_an_object<DoSomething>(100, 101, 102);

        std::cout << u1 << std::endl;
        std::cout << u2 << std::endl;
        std::cout << u3 << std::endl;
        std::cout << u4 << std::endl;

        int n = 100;
        const int m = 101;

        DoSomething u5 = make_an_object<DoSomething, int, int&, const int&>(100, n, m);
        DoSomething u6 = make_an_object<DoSomething>(n, 51, m);

        std::cout << u5 << std::endl;
        std::cout << u6 << std::endl;

        // doesn't compile: too much parameters
        // DoSomething u7 = make_an_object<DoSomething>(1000, 1001, 1002, 1003);
        // std::cout << u7 << std::endl;
    }

    static void test_make_an_object_ex()
    {
        DoSomething u1 = make_an_object_ex<DoSomething>();
        DoSomething u2 = make_an_object_ex<DoSomething>(1);
        DoSomething u3 = make_an_object_ex<DoSomething>(10, 11);
        DoSomething u4 = make_an_object_ex<DoSomething>(100, 101, 102);

        std::cout << u1 << std::endl;
        std::cout << u2 << std::endl;
        std::cout << u3 << std::endl;
        std::cout << u4 << std::endl;

        int n = 100;
        const int m = 101;

        DoSomething u5 = make_an_object_ex<DoSomething, int, int&, const int&>(100, n, m);
        DoSomething u6 = make_an_object_ex<DoSomething>(n, 51, m);

        std::cout << u5 << std::endl;
        std::cout << u6 << std::endl;
    }
}

namespace VariadicTemplatesIntro_04 {

    // =============================================================
    // 4. Beispiel für ein variadisches Template:
    // Expansion des Parameter Packs: Datentypen und Argumente
    // =============================================================

    template <typename... TArgs>
    void examine_parameter_pack(TArgs ... args) {

        // expand template parameter pack 'TArgs' first,
        // then function parameter pack 'args'
        std::tuple<TArgs ...> tup { args ... };
    }

    static void examine_parameter_pack_ex(auto ... args) {

        std::tuple tup1{ args ... };

        std::tuple<decltype(args) ...> tup2{args ...};
    }

    static void examine_parameter_pack_ex_ex(int args_1, double args_2, std::string args_3, long long args_4) {

        std::tuple<int, double, std::string, long long> tup{ args_1, args_2, args_3, args_4 };
    }

    static void test_parameterpack_expansion() {

        examine_parameter_pack(123, 123.456, std::string{ "foo" }, 789ll);
        examine_parameter_pack_ex(123, 123.456, std::string{ "foo" }, 789ll);
        examine_parameter_pack_ex_ex(123, 123.456, std::string{ "foo" }, 789ll);
    }
}

namespace VariadicTemplatesIntro_05 {

    // =============================================================
    // 5. Beispiel für ein variadisches Template:
    // Anwendungsfall: Zugriff auf die einzelnen Elemente eines Parameter Packs
    // =============================================================

    template <typename... TArgs>
    void func(TArgs... args) {

        // unpack all function arguments with the help of a std::initializer_list object
        auto unpackedArgs = { args ... };

        for (auto param : unpackedArgs) {
            std::cout << "Passed Argument: " << param << std::endl;
        }

        // oder

        for (auto param : { args ... }) {
            std::cout << "Passed Argument: " << param << std::endl;
        }
    }

    static void test_accessing_parameterpack()
    {
        func(10, 11, 12, 13, 14, 15);
    }
}

namespace VariadicTemplatesIntro_06 {

    // ========================================================================
    // 6. Beispiel:
    // Ein variadisches Template in zwei Realisierungsvarianten.
    // 
    // Ende der Rekursion:
    // a) Eine rekursive Template Funktion
    // b) Eine nicht-rekursive Non-Template Funktion
    // 
    // Man beachte: Wenn sich zwei Template Funktionen nur um das Parameter Pack
    // unterscheiden, wird - wenn möglich - die Template Funktionen ohne Parameter Pack bevorzugt:
    // ========================================================================

    // Ende der Rekursion: Eine non-Template Funktion
    static void print()
    {
    }

    template<typename T, typename... Types>
    void print(T firstArg, Types... args)
    {
        std::cout << firstArg << std::endl; // print first argument
        print(args...); // call print() for remaining arguments
    }

    // Oder:
    // Ende der Rekursion: Eine Template Funktion

    template<typename T>
    void printEx(T arg)
    {
        std::cout << arg << std::endl; // print passed argument
    }

    template<typename T, typename... Types>
    void printEx(T firstArg, Types... args)
    {
        printEx(firstArg); // call print() for first argument
        printEx(args...);  // call print() for remaining arguments
    }

    static void test_printer_02()
    {
        print(123.456, "Hello", 789);
        print<double, const char*, int>(123.456, "Hello", 789);

        printEx(123.456, "Hello", 789);
        printEx<double, const char*, int>(123.456, "Hello", 789);
    }
}

void main_variadic_templates_introduction()
{
    VariadicTemplatesIntro_01::test_printer_01();

    VariadicTemplatesIntro_02::test_my_make_unique();
    VariadicTemplatesIntro_02::test_my_make_unique_ex();

    VariadicTemplatesIntro_03::test_make_an_object();
    VariadicTemplatesIntro_03::test_make_an_object_ex();

    VariadicTemplatesIntro_04::test_parameterpack_expansion();

    VariadicTemplatesIntro_05::test_accessing_parameterpack();

    VariadicTemplatesIntro_06::test_printer_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
