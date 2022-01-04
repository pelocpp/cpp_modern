// =====================================================================================
// Function Templates
// =====================================================================================

#include <iostream>
#include <cmath>
#include <complex>

namespace FunctionTemplateMinimum {

    template <typename T>
    struct Point
    {
        T m_x;
        T m_y;

        Point operator+ (const Point& p) {
            return { m_x + p.m_x, m_y + p.m_y }; 
        }

        T distance() {
            return std::sqrt(m_x * m_x + m_y * m_y);
        }
    };

    // normal function definition
    bool minimum(int a, int b)
    {
        return (a < b) ? true : false;
    }

    // function template definition
    template <typename T>
    bool minimum(T a, T b)
    {
        return (a < b) ? true : false;
    }

    // explicit function template specialization
    template <>
    bool minimum<Point<double>>(Point<double> a, Point<double> b)
    {
        return (a.distance() < b.distance()) ? true : false;
    }

    // another explicit function template specialization
    template <>
    bool minimum<std::complex<double>>(std::complex<double> a, std::complex<double> b)
    {
        return (std::abs(a) < std::abs(b)) ? true : false;
    }

    // note: explicit versus partial function template specialization
    template <typename T, typename U>
    void function(T a, U b) {}

    // partial function template specialization: not allowed (!)
    //template <typename T>
    //void function<T, int>(T a, int b) {}

    // explicit function template specialization: allowed (!)
    template <>
    void function<double, int>(double a, int b) {}

    void test_01()
    {
        bool result;
        result = minimum(10, 20);
        result = minimum(10.0, 20.0);
        result = minimum(Point<double>{ 1, 2 }, Point<double>{ 3, 4 });

        using namespace std::complex_literals;
        std::complex<double> z1 = 1. + 2i;
        std::complex<double> z2 = 1. - 2i;
        result = minimum(z1, z2);
    }
}

namespace FunctionTemplatesBasics {

    template <typename T>
    void printValue(T const& t)
    {
        std::cout << "Value: " << t << std::endl;
    }

    // put this template into comments if type deduction is going to be demonstrated
    template <>
    void printValue<bool>(bool const& b)
    {
        std::cout << std::boolalpha << "Value: " << b << std::endl;
    }

    void test_02() {
        printValue<int>(10);
        printValue<bool>(true);
        printValue<double>(12.5);
    }

    void test_03() {
        printValue<>(10);
        printValue<>(true);
        printValue<>(12.5);
    }

    void test_04() {
        printValue(10);
        printValue(true);
        printValue(12.5);
    }
}

void main_function_templates_basics()
{
    using namespace FunctionTemplateMinimum;
    test_01();

    using namespace FunctionTemplatesBasics;
    test_02();
    test_03();
    test_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
