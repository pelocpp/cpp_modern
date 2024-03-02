// =====================================================================================
// TemplatesFunctionBasics.cpp // Function Templates
// =====================================================================================

module modern_cpp:templates_function_basics;

namespace FunctionTemplate_01_Basics {

    template <typename T>
    struct Point
    {
        T m_x;
        T m_y;

        Point operator+ (const Point& p) const {
            return { m_x + p.m_x, m_y + p.m_y }; 
        }

        T distance() const {
            return std::sqrt(m_x * m_x + m_y * m_y);
        }
    };

    // normal function definition
    bool lessThan(int a, int b)
    {
        return (a < b) ? true : false;
    }

    // function template definition
    template <typename T>
    bool lessThan(const T& a, const T& b)
    {
        return (a < b) ? true : false;
    }

    // explicit function template specialization
    template <>
    bool lessThan<Point<double>>(const Point<double>& a, const Point<double>& b)
    {
        return (a.distance() < b.distance()) ? true : false;
    }

    // another explicit function template specialization
    template <>
    bool lessThan<std::complex<double>>(const std::complex<double>& a, const std::complex<double>& b)
    {
        return (std::abs(a) < std::abs(b)) ? true : false;
    }

    // note: explicit versus partial function template specialization
    template <typename T, typename U>
    void function(T a, U b) {}

    // partial function template specialization: not allowed (!)
    // template <typename T>
    // void function<T, int>(T a, int b) {}

    // explicit function template specialization: allowed (!)
    template <>
    void function<double, int>(double, int) {}

    static void test_01()
    {
        bool result;
        result = lessThan(10, 20);
        // result = lessThan(10, 20.5);   // warning or error
        result = lessThan(10.0, 20.0);
        result = lessThan(Point<double>{ 1, 2 }, Point<double>{ 3, 4 });

        using namespace std::complex_literals;
        std::complex<double> z1 = 1. + 2i;
        std::complex<double> z2 = 1. - 2i;
        result = lessThan(z1, z2);
    }
}

namespace FunctionTemplate_02_Overloading {

    template <typename T>
    inline const T& minimum(const T& a, const T& b) {
        return (a < b) ? a : b;
    }

    template <typename T>
    inline const T& minimum(const T& a, const T& b, const T& c) {
        return a < b ? (a < c ? a : c) : (b < c ? b : c);
    }

    inline const int& minimum(const int& a, const int& b) { 
        return (a < b) ? a : b;
    }

    static void test_02()
    {
        minimum(1, 2, 3);       // Template mit 3 Argumenten
        minimum(1.0, 2.0);      // minimum<double> per Typ Deduktion
        minimum('X', 'Y');      // minimum<char> per Typ Deduktion
        minimum(1, 2);          // non-template Variante bevorzugt
        minimum<>(1, 2);        // minimum<int> per Typ Deduktion
        minimum<double>(1, 2);  // minimum<double> ohne Typ Deduktion
        // <minimum('X', 3.14);     // non-template Variante für 2 ints (compiler warning)
    }
}

namespace FunctionTemplates_03_Specialisation {

    template <typename T>
    void printValue(T const& t)
    {
        std::cout << "Value: " << t << std::endl;
    }

    // put this template into comments if Typ Deduktion is going to be demonstrated
    template <>
    void printValue<bool>(bool const& b)
    {
        std::cout << std::boolalpha << "Value: " << b << std::endl;
    }

    static void test_03_01() {
        printValue<int>(10);
        printValue<bool>(true);
        printValue<double>(12.5);
    }

    static void test_03_02() {
        printValue<>(10);
        printValue<>(true);
        printValue<>(12.5);
    }

    static void test_03_03() {
        printValue(10);
        printValue(true);
        printValue(12.5);
    }
}

namespace FunctionTemplates_04_Specialization_vs_FunctionOverloading {

    // from https://stackoverflow.com/questions/7108033/template-specialization-vs-function-overloading
    // but doesn't still demonstrate, what it should demonstrate :(

    namespace Variant_01 {

        template <typename T> void foo(T) {};
        template <typename T> void foo(T*) { std::cout << "overload"; };  // overload of foo(T)
        template <>           void foo<int*>(int*) { std::cout << ""; };  // specialization of foo(T*)

        static void test_04() {

            int* ip = new int{ 123 };

            foo(new int);       // calls overload
        
            delete ip;
        }
    }

    namespace Variant_02 {

        template <typename T> void foo(T) {};
        template <>           void foo<int*>(int*) { std::cout << ""; };  // specialization of foo(T*)
        template <typename T> void foo(T*) { std::cout << "overload"; };  // overload of foo(T)
   
        static void test_04() {

            int* ip = new int{ 123 };

            foo(new int);       // calls specialization

            delete ip;
        }
    }

    static void test_04() {
        Variant_01::test_04();
        Variant_02::test_04();
    }
}

void main_function_templates_basics()
{
    using namespace FunctionTemplate_01_Basics;
    test_01();

    using namespace FunctionTemplate_02_Overloading;
    test_02();

    using namespace FunctionTemplates_03_Specialisation;
    test_03_01();
    test_03_02();
    test_03_03();

    using namespace FunctionTemplates_04_Specialization_vs_FunctionOverloading;
    test_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
