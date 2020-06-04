// =====================================================================================
// Expression Templates
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <chrono> 

namespace ExpressionTemplates {

    template <typename T, size_t COLS = 1000, size_t ROWS = 1000>
    class Matrix {
    private:
        std::vector<T> m_values;

    public:
        using value_type = T;

        // c'tor
        Matrix() : m_values(COLS* ROWS) {}

        // getter
        static size_t cols();
        static size_t rows();

        // functor - representing index operator
        const T& operator()(size_t x, size_t y) const;
        T& operator()(size_t x, size_t y);

        // operator= --> classical definition
        Matrix<T, COLS, ROWS>& operator=(const Matrix<T, COLS, ROWS>& rhs);

        // operator= --> expression template approach (template member method)
        template <typename TEXPR>
        Matrix<T, COLS, ROWS>& operator=(const TEXPR& expression);
    };

    template <typename T, size_t COLS, size_t ROWS>
    size_t Matrix<T, COLS, ROWS>::cols() {
        return COLS;
    }

    template <typename T, size_t COLS, size_t ROWS>
    size_t Matrix<T, COLS, ROWS>::rows() {
        return ROWS;
    }

    template <typename T, size_t COLS, size_t ROWS>
    const T& Matrix<T, COLS, ROWS>::operator()(size_t x, size_t y) const {
        return m_values[y * COLS + x];
    }

    template <typename T, size_t COLS, size_t ROWS>
    T& Matrix<T, COLS, ROWS>::operator()(size_t x, size_t y) {
        return m_values[y * COLS + x];
    }

    // classical operator+ definition
    template <typename T, size_t COLS, size_t ROWS>
    Matrix<T, COLS, ROWS> operator+(const Matrix<T, COLS, ROWS>& lhs, const Matrix<T, COLS, ROWS>& rhs)
    {
        Matrix<T, COLS, ROWS> result;
        for (size_t y = 0; y != Matrix<T, COLS, ROWS>::rows(); ++y) {
            for (size_t x = 0; x != Matrix<T, COLS, ROWS>::cols(); ++x) {
                result(x, y) = lhs(x, y) + rhs(x, y);
            }

        }
        return result;
    }

    // classical operator= implementation
    template <typename T, size_t COLS, size_t ROWS>
    Matrix<T, COLS, ROWS>& Matrix<T, COLS, ROWS>::operator=(const Matrix<T, COLS, ROWS>& rhs) {

        // prevent self-assignment
        if (this != &rhs) {
            m_values = rhs.m_values;
        }
        return *this;
    }

    // expression template approach: operator=
    template <typename T, size_t COLS, size_t ROWS>
    template <typename TEXPR>
    Matrix<T, COLS, ROWS>& Matrix<T, COLS, ROWS>::operator=(const TEXPR& expression) {
        for (size_t y = 0; y != rows(); ++y) {
            for (size_t x = 0; x != cols(); ++x) {
                m_values[y * COLS + x] = expression(x, y);
            }
        }
        return *this;
    }

    // ========================================================================

    template<typename T, size_t COLS, size_t ROWS>
    Matrix<T, COLS, ROWS> add3(
        const Matrix<T, COLS, ROWS>& a,
        const Matrix<T, COLS, ROWS>& b,
        const Matrix<T, COLS, ROWS>& c)
    {
        Matrix<T, COLS, ROWS> result;
        for (size_t y = 0; y != ROWS; ++y) {
            for (size_t x = 0; x != COLS; ++x) {
                result(x, y) = a(x, y) + b(x, y) + c(x, y);
            }
        }
        return result;
    }

    // ========================================================================

    template <typename LHS, typename RHS>
    class MatrixSum
    {
    public:
        using value_type = typename LHS::value_type;

        MatrixSum(const LHS& lhs, const RHS& rhs) : rhs(rhs), lhs(lhs) {}

        friend MatrixSum<LHS, RHS> operator+(const LHS& lhs, const LHS& rhs);

        value_type operator() (int x, int y) const {
            return lhs(x, y) + rhs(x, y);
        }
    private:
        const LHS& lhs;
        const RHS& rhs;
    };

    template <typename LHS, typename RHS>
    MatrixSum<LHS, RHS> operator+(const LHS& lhs, const LHS& rhs) {
        return MatrixSum<LHS, RHS>(lhs, rhs);
    }

    // ========================================================================

    void test_01()
    {
        std::cout << "Expression Template 01:" << std::endl;

        const size_t cols = 2000;
        const size_t rows = 1000;

        Matrix<double, cols, rows> a, b, c;

        // initialize a, b & c
        for (size_t y = 0; y != rows; ++y) {
            for (size_t x = 0; x != cols; ++x) {
                a(x, y) = 1.0;
                b(x, y) = 2.0;
                c(x, y) = 3.0;
            }
        }

        Matrix<double, cols, rows> result = a + b + c;  // result(x, y) = 6 
    }

    void test_02()
    {
        std::cout << "Expression Template 02:" << std::endl;

        Matrix<double> a, b, c, result;

        // adding 2 matrices
        MatrixSum<Matrix<double>, Matrix<double>> sumAB(a, b);
        for (size_t y = 0; y != Matrix<double>::rows(); ++y) {
            for (size_t x = 0; x != Matrix<double>::cols(); ++x) {
                result(x, y) = sumAB(x, y);
            }
        }

        // adding 3 matrices
        MatrixSum<MatrixSum<Matrix<double>, Matrix<double>>, Matrix<double>> sumABC(sumAB, c);
        for (size_t y = 0; y != Matrix<double>::rows(); ++y) {
            for (size_t x = 0; x != Matrix<double>::cols(); ++x) {
                result(x, y) = sumABC(x, y);
            }
        }
    }

    void test_03()
    {
        std::cout << "Expression Template 03:" << std::endl;

        const size_t cols = 2000;
        const size_t rows = 1000;

        Matrix<double, cols, rows> result, a, b, c;

        // initialize a, b & c
        for (size_t y = 0; y != rows; ++y) {
            for (size_t x = 0; x != cols; ++x) {
                a(x, y) = 1.0;
                b(x, y) = 2.0;
                c(x, y) = 3.0;
            }
        }

        // adding 3 matrices
        MatrixSum<Matrix<double, cols, rows>, Matrix<double, cols, rows>> sumAB(a, b);
        MatrixSum<MatrixSum<Matrix<double, cols, rows>, Matrix<double, cols, rows>>, Matrix<double, cols, rows>> sumABC(sumAB, c);

        result = sumABC;
    }

    void test_04a_benchmark(
        int iterations,
        Matrix<double>& result,
        const Matrix<double>& a1,
        const Matrix<double>& a2,
        const Matrix<double>& a3,
        const Matrix<double>& a4,
        const Matrix<double>& a5)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            result = a1 + a2 + a3 + a4 + a5;
        }
        auto end = std::chrono::high_resolution_clock::now();

        std::cout
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << " milliseconds." << std::endl;
    }

    void test_04b_benchmark(
        int iterations,
        Matrix<double>& result,
        const Matrix<double>& a1,
        const Matrix<double>& a2,
        const Matrix<double>& a3,
        const Matrix<double>& a4,
        const Matrix<double>& a5)
    {
        // adding 5 matrices with expression template approach
        MatrixSum<Matrix<double>, Matrix<double>> sumAB(a1, a2);
        MatrixSum<MatrixSum<Matrix<double>, Matrix<double>>, Matrix<double>> sumABC(sumAB, a3);
        MatrixSum<MatrixSum<MatrixSum<Matrix<double>, Matrix<double>>, Matrix<double>>, Matrix<double>> sumABCD(sumABC, a4);
        MatrixSum<MatrixSum<MatrixSum<MatrixSum<Matrix<double>, Matrix<double>>, Matrix<double>>, Matrix<double>>, Matrix<double>> sumABCDE(sumABCD, a5);

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            result = sumABC;
        }
        auto end = std::chrono::high_resolution_clock::now();

        std::cout
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << " milliseconds." << std::endl;
    }

    void test_04_benchmark()
    {
        std::cout << "Expression Templates 04 (Benchmark):" << std::endl;

        constexpr int Iterations = 10;

        Matrix<double> result, a, b, c, d, e;

        // initialize a, b & c
        for (size_t y = 0; y != Matrix<double>::rows(); ++y) {
            for (size_t x = 0; x != Matrix<double>::cols(); ++x) {
                a(x, y) = 1.0;
                b(x, y) = 2.0;
                c(x, y) = 3.0;
                d(x, y) = 4.0;
                e(x, y) = 5.0;
            }
        }

        std::cout << "Start:" << std::endl;
        test_04a_benchmark(Iterations, result, a, b, c, d, e);
        test_04b_benchmark(Iterations, result, a, b, c, d, e);
        std::cout << "Done." << std::endl;
    }
}

int main_expression_templates()
{
    using namespace ExpressionTemplates;
    test_01();
    test_02();
    test_03();
    test_04_benchmark();
    return 1;
}

// =====================================================================================
// End-of-File
// =====================================================================================
