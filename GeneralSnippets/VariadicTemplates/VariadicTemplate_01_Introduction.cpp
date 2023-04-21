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
    void printAll(T value)
    {
        std::cout << value << " ";
    }

    // Recursive template part
    // Note: ... specifies a so called 'parameter pack')
    template <typename T, typename ... TRest>
    void printAll(T n, TRest ... rest)
    {
        printAll<T>(n);
        printAll<TRest...>(rest ...);
    }

    void test_printer_01()
    {
       printAll<int, int, int, int, int>(1, 2, 3, 4, 5);
    }
}

namespace VariadicTemplatesIntro_02 {

    // ========================================================================
    // 2. Beispiel für ein variadisches Template:
    // Eine add-Funktion mit beliebig vielen Argumenten unterschiedlichen Typs
    // ========================================================================

    // Non-recursive template part (regular template)
    template<typename T>
    T add(T v) {
        return v;
    }

    // Recursive template part
    // Note: ... specifies a so called 'parameter pack')
    template<typename T, typename ... TArgs>
    T add(T first, TArgs... args) {
        return first + add<TArgs ...>(args...);
    }

    void test_adder_01() {
        int sum = add<int, int, int, int, int>(1, 2, 3, 4, 5);
        std::cout << "Sum from 1 up to 5: " << sum << std::endl;
    }

    void test_adder_02() {

        int sum = add(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        std::cout << "Sum from 1 up to 10: " << sum << std::endl;

        std::string stringConcat = add(
            std::string("ABC"),
            std::string("DEF"),
            std::string("GHI"),
            std::string("JKL"),
            std::string("MNO")
        );
        std::cout << "String Concatenation: " << stringConcat << std::endl;
    }
}

namespace VariadicTemplates_TestClassUnknown {

    // ========================================================================
    // Test-Klasse Unknown
    // Nur die Konstruktoren sind interessant
    // ========================================================================

    class Unknown {
    private:
        int m_var1;
        int m_var2;
        int m_var3;

    public:
        Unknown() : m_var1{ -1 }, m_var2{ -1 }, m_var3{ -1 } {
            std::cout << "c'tor()" << std::endl;
        }

        Unknown(int n) : m_var1{ n }, m_var2{ -1 }, m_var3{ -1 } {
            std::cout << "c'tor(int)" << std::endl;
        }

        Unknown(int n, int m) : m_var1{ n }, m_var2{ m }, m_var3{ -1 } {
            std::cout << "c'tor(int, int)" << std::endl;
        }

        Unknown(int n, int m, int k) : m_var1{ n }, m_var2{ m }, m_var3{ k } {
            std::cout << "c'tor(int, int, int)" << std::endl;
        }

        friend std::ostream& operator<< (std::ostream&, const Unknown&);
    };

    std::ostream& operator<< (std::ostream& os, const Unknown& obj) {
        os 
            << "var1: " << obj.m_var1
            << ", var2: " << obj.m_var2
            << ", var3: " << obj.m_var3 << std::endl;

        return os;
    }
}

namespace VariadicTemplatesIntro_03 {

    // =============================================================
    // 3. Beispiel für ein variadisches Template:
    // Anwendungsfall: Standardfunktion std::unique_ptr<>
    // =============================================================

    using namespace VariadicTemplates_TestClassUnknown;

    // einfache Variante
    template<typename T, typename... TArgs>
    std::unique_ptr<T> my_make_unique(const TArgs&... args)
    {
        return std::unique_ptr<T>{ new T{ args... } };
    }

    // bessere Variante: Mit Universal Referenz
    template<typename T, typename... TArgs>
    std::unique_ptr<T> my_make_unique_ex(TArgs&&... args)
    {
        return std::unique_ptr<T>{ new T{ std::forward<TArgs>(args)... } };
    }

    void test_my_make_unique()
    {
        std::unique_ptr<Unknown> up1 = my_make_unique<Unknown>();
        std::unique_ptr<Unknown> up2 = my_make_unique<Unknown>(1);
        std::unique_ptr<Unknown> up3 = my_make_unique<Unknown>(10, 11);
        std::unique_ptr<Unknown> up4 = my_make_unique<Unknown>(100, 101, 102);

        int n = 33, m = 34;
        std::unique_ptr<Unknown> up5 = my_make_unique<Unknown>(n, m);
    }

    void test_my_make_unique_ex()
    {
        std::unique_ptr<Unknown> up1 = my_make_unique_ex<Unknown>();
        std::unique_ptr<Unknown> up2 = my_make_unique_ex<Unknown>(1);
        std::unique_ptr<Unknown> up3 = my_make_unique_ex<Unknown>(10, 11);
        std::unique_ptr<Unknown> up4 = my_make_unique_ex<Unknown>(100, 101, 102);

        int n = 33, m = 34;
        std::unique_ptr<Unknown> up5 = my_make_unique_ex<Unknown>(n, m);
    }
}

namespace VariadicTemplatesIntro_04 {

    // =================================================================================
    // 4. Beispiel für ein variadisches Template:
    // 
    // Anwendungsfall: "Generische Funktion 'make_an_object'"
    //                 Umsetzung Parameter Pack auf einen passenden Konstruktor
    // 
    // Siehe Analogien zu Factory-Pattern
    // =================================================================================

    using namespace VariadicTemplates_TestClassUnknown;

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

    void test_make_an_object()
    {
        Unknown u1 = make_an_object<Unknown>();
        Unknown u2 = make_an_object<Unknown>(1);
        Unknown u3 = make_an_object<Unknown>(10, 11);
        Unknown u4 = make_an_object<Unknown>(100, 101, 102);

        std::cout << u1 << std::endl;
        std::cout << u2 << std::endl;
        std::cout << u3 << std::endl;
        std::cout << u4 << std::endl;

        int n = 100;
        const int m = 101;

        Unknown u5 = make_an_object<Unknown, int, int&, const int&>(100, n, m);
        Unknown u6 = make_an_object<Unknown>(n, 51, m);

        std::cout << u5 << std::endl;
        std::cout << u6 << std::endl;

        // doesn't compile: too much parameters
        // Unknown u7 = make_an_object<Unknown>(1000, 1001, 1002, 1003);
        // std::cout << u7 << std::endl;
    }

    void test_make_an_object_ex()
    {
        Unknown u1 = make_an_object_ex<Unknown>();
        Unknown u2 = make_an_object_ex<Unknown>(1);
        Unknown u3 = make_an_object_ex<Unknown>(10, 11);
        Unknown u4 = make_an_object_ex<Unknown>(100, 101, 102);

        std::cout << u1 << std::endl;
        std::cout << u2 << std::endl;
        std::cout << u3 << std::endl;
        std::cout << u4 << std::endl;

        int n = 100;
        const int m = 101;

        Unknown u5 = make_an_object_ex<Unknown, int, int&, const int&>(100, n, m);
        Unknown u6 = make_an_object_ex<Unknown>(n, 51, m);

        std::cout << u5 << std::endl;
        std::cout << u6 << std::endl;
    }
}

namespace VariadicTemplatesIntro_05 {

    // ========================================================================
    // 5.) Drittes Beispiel:
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

    void test_printer_02()
    {
        print(123.456, "Hello", 789);
        print<double, const char*, int>(123.456, "Hello", 789);

        printEx(123.456, "Hello", 789);
        printEx<double, const char*, int>(123.456, "Hello", 789);
    }
}

void main_variadic_templates_introduction()
{
    using namespace VariadicTemplatesIntro_01;
    test_printer_01();

    using namespace VariadicTemplatesIntro_02;
    test_adder_01();
    test_adder_02();

    using namespace VariadicTemplatesIntro_03;
    test_my_make_unique();
    test_my_make_unique_ex();

    using namespace VariadicTemplatesIntro_04;
    test_make_an_object();
    test_make_an_object_ex();

    using namespace VariadicTemplatesIntro_05;
    test_printer_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
