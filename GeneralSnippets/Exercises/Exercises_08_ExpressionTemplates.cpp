// =====================================================================================
// Exercises_08_ExpressionTemplates.cpp
// =====================================================================================

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

    void test_01()
    {
        std::vector<double> a{ 1, 2, 3, 4,  5 };
        std::vector<double> b{ 6, 7, 8, 9, 10 };
        std::cout << "scalarProduct<double>(a, b) = " << scalarProduct<double>(a, b) << std::endl; // 130
        std::cout << "scalarProduct<double>(a, b) = " << scalarProduct<double>(a, a) << std::endl; // 55
    }

    void test_02()
    {
        std::vector<double> a{ 1, 2, 3, 4,  5 };
        std::vector<double> b{ 6, 7, 8, 9, 10 };
        std::cout << "scalarProductEx<double>(a, b) = " << scalarProductEx<double>(a.begin(), a.end(), b.begin()) << std::endl; // 130
        std::cout << "scalarProductEx<double>(a, b) = " << scalarProductEx<double>(a.begin(), a.end(), a.begin()) << std::endl; // 55
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

    void test_03()
    {
        std::vector<double> a{ 1, 2, 3, 4,  5 };
        std::vector<double> b{ 6, 7, 8, 9, 10 };
        std::cout << "ScalarProduct<5, double>=" << ScalarProduct<5, double>::result(
            a.cbegin(),
            b.cbegin()
        ) << std::endl; // 130
        std::cout << "ScalarProduct<5, double>=" << ScalarProduct<5, double>::result(
            a.cbegin(), 
            a.cbegin()) << std::endl; // 55
    }
}

void test_exercices_expression_templates()
{
    using namespace Exercises_ExpressionTemplates;
    test_01();
    test_02();
    test_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
