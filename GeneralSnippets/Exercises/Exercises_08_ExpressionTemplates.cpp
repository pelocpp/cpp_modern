// =====================================================================================
// Exercises_08_ExpressionTemplates.cpp
// =====================================================================================

module;

#include "../ScopedTimer/ScopedTimer.h"

module modern_cpp_exercises:expression_templates;

namespace Exercises_ExpressionTemplates {

    template <typename T>
    T scalarProduct(const std::vector<T>& a, const std::vector<T>& b)
    {
        T product{};
        for (size_t i{}; i != a.size(); ++i) {
            product += (a[i]) * (b[i]);
        }
        return product;
    }

    template <typename T>
    T scalarProductEx(typename std::vector<T>::iterator&& a, typename std::vector<T>::iterator&& end, typename std::vector<T>::iterator&& b)
    {
        T product{};
        for (; a != end; ++a, ++b) {
            product += (*a) * (*b);
        }
        return product;
    }

    static void test_01()
    {
        std::vector<double> a{ 1, 2, 3, 4,  5 };
        std::vector<double> b{ 6, 7, 8, 9, 10 };

        auto prod1 { scalarProduct<double>(a, b) };
        auto prod2 { scalarProduct<double>(a, a) };

        std::cout << "scalarProduct<double>(a, b) = " << prod1 << std::endl; // 130
        std::cout << "scalarProduct<double>(a, a) = " << prod2 << std::endl; // 55
    }

    static void test_02()
    {
        std::vector<double> a{ 1, 2, 3, 4,  5 };
        std::vector<double> b{ 6, 7, 8, 9, 10 };

        auto prod1{ scalarProductEx<double>(a.begin(), a.end(), b.begin()) };
        auto prod2{ scalarProductEx<double>(a.begin(), a.end(), a.begin()) };

        std::cout << "scalarProductEx<double>(a, b) = " << prod1 << std::endl; // 130
        std::cout << "scalarProductEx<double>(a, a) = " << prod2 << std::endl; // 55
    }

    // primary template
    template <size_t N, typename T>
    class ScalarProduct {
    public:
        static inline T result(
            const typename std::vector<T>::const_iterator a,
            const typename std::vector<T>::const_iterator b) {
                return (*a) * (*b) + ScalarProduct<N - 1, T>::result(a + 1, b + 1);
        }
    };

    // partial specialization to terminate recursion
    template <typename T>
    class ScalarProduct<1, T> {
    public:
        static inline T result(
            const typename std::vector<T>::const_iterator a,
            const typename std::vector<T>::const_iterator b) {
                return (*a) * (*b);
        }
    };

    static void test_03()
    {
        std::vector<double> a{ 1, 2, 3, 4,  5 };
        std::vector<double> b{ 6, 7, 8, 9, 10 };

        auto prod1{ ScalarProduct<5, double>::result(a.cbegin(), b.cbegin()) };
        auto prod2{ ScalarProduct<5, double>::result(a.cbegin(), a.cbegin()) };

        std::cout << "ScalarProduct<5, double> = " << prod1 << std::endl; // 130
        std::cout << "ScalarProduct<5, double> = " << prod2 << std::endl; // 55
    }

    static void test_04()
    {
        constexpr auto MaxIterations = 1000000000;

        std::vector<double> a{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        {
            ScopedTimer watch{};
            auto prod{ 0.0 };

            for (size_t n{}; n != MaxIterations; ++n) {
                prod = scalarProduct<double>(a, a);
            }
            std::cout << "scalarProduct<double>(a, a): " << prod << std::endl;
        }

        {
            ScopedTimer watch{};
            auto prod{ 0.0 };

            for (size_t n{}; n != MaxIterations; ++n) {
                prod = scalarProductEx<double>(a.begin(), a.end(), a.begin());
            }
            std::cout << "scalarProductEx<double>(a.begin(), a.end(), a.begin()): " << prod << std::endl;
        }

        {
            ScopedTimer watch{};
            auto prod{ 0.0 };

            for (size_t n{}; n != MaxIterations; ++n) {
                prod = ScalarProduct<10, double>::result(a.cbegin(), a.cbegin());
            }
            std::cout << "ScalarProduct<10, double>::result(a.cbegin(), a.cbegin()): " << prod << std::endl;
        }
    }
}

void test_exercices_expression_templates()
{
    using namespace Exercises_ExpressionTemplates;
    //test_01();
    //test_02();
    //test_03();
    test_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
