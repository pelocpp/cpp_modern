// =====================================================================================
// Expression Templates
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <chrono> 

namespace ExpressionTemplates {

    constexpr bool Verbose = false;

    // default sizes
    constexpr size_t DefaultCols = 3;
    constexpr size_t DefaultRows = 3;

    // benchmark sizes
    constexpr int Iterations = 10;
    constexpr size_t BenchmarkRows = 2000;
    constexpr size_t BenchmarkCols = 1000;

    template <typename T>
    class Matrix {
    private:
        size_t m_cols;
        size_t m_rows;
        std::vector<T> m_values;

    public:
        using value_type = T;

        // c'tor
        Matrix(size_t cols = DefaultCols, size_t rows = DefaultRows)
            : m_cols(cols), m_rows(rows), m_values(cols* rows) {}

        // getter
        size_t inline getCols() const { return m_cols; };
        size_t inline getRows() const { return m_rows; };

        // functor - representing index operator
        const T& operator()(size_t x, size_t y) const;
        T& operator()(size_t x, size_t y);

        // operator= --> classical definition
        Matrix<T>& operator=(const Matrix<T>& rhs);

        // operator= --> expression template approach (template member method)
        template <typename TEXPR>
        Matrix<T>& operator=(const TEXPR& expression);
    };

    template <typename T>
    const T& Matrix<T>::operator()(size_t x, size_t y) const {
    //    if constexpr (Verbose) {
    //        std::cout << "Matrix::operator() const => " << x << ',' << y << std::endl;
    //    }
        return m_values[y * getCols() + x];
    }

    template <typename T>
    T& Matrix<T>::operator()(size_t x, size_t y) {
        //if constexpr (Verbose) {
        //    std::cout << "Matrix::operator() => [" << x << ',' << y << ']' << std::endl;
        //}
        return m_values[y * getCols() + x];
    }

    // classical operator+ definition
    template <typename T>
    Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs)
    {
        Matrix<T> result(lhs.getCols(), lhs.getRows());
        for (size_t y = 0; y != lhs.getRows(); ++y) {
            for (size_t x = 0; x != lhs.getCols(); ++x) {
                // result(x, y) = lhs(x, y) + rhs(x, y);

                if constexpr (Verbose) {
                    T l = lhs(x, y);
                    T r = rhs(x, y);
                    std::cout << "Matrix:: adding " << l << '+' << r << std::endl;
                    T tmp = l + r;
                    std::cout << "Matrix:: assigning result " << tmp << std::endl;
                    result(x, y) = tmp;
                }
                else {
                    result(x, y) = lhs(x, y) + rhs(x, y);
                }
            }

        }
        return result;
    }

    // classical operator= implementation
    template <typename T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {

        // prevent self-assignment
        if (this != &rhs) {
            m_values = rhs.m_values;
        }
        return *this;
    }

    // expression template approach: operator=
    template <typename T>
    template <typename TEXPR>
    Matrix<T>& Matrix<T>::operator=(const TEXPR& expression) {
        for (size_t y = 0; y != getRows(); ++y) {
            for (size_t x = 0; x != getCols(); ++x) {

                if constexpr (Verbose) {
                    T sum = expression(x, y);
                    std::cout << "Matrix::    assigning expression result " << sum << std::endl;
                    m_values[y * getCols() + x] = sum;
                }
                else {
                    m_values[y * getCols() + x] = expression(x, y);
                }
            }
        }
        return *this;
    }

    // ========================================================================

    template<typename T>
    Matrix<T> add3(
        const Matrix<T>& a,
        const Matrix<T>& b,
        const Matrix<T>& c)
    {
        Matrix<T> result;
        for (size_t y = 0; y != a.getRows(); ++y) {
            for (size_t x = 0; x != a.getCols(); ++x) {
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

        value_type operator() (size_t x, size_t y) const {

            if constexpr (Verbose) {
                value_type l = lhs(x, y);
                value_type r = rhs(x, y);
                std::cout << "MatrixSum:: adding " << l << '+' << r << std::endl;
                value_type tmp = l + r;
                return tmp;
            }
            else {
                return lhs(x, y) + rhs(x, y);
            }
        }

    private:
        const LHS& lhs;
        const RHS& rhs;
    };

    // ========================================================================

    void test_01()
    {
        std::cout << "Expression Template 01: Classical Approach" << std::endl;

        Matrix<double> a;
        Matrix<double> b;
        Matrix<double> c;
        Matrix<double> d;

        // initialize matrices
        for (size_t y = 0; y != a.getRows(); ++y) {
            for (size_t x = 0; x != a.getCols(); ++x) {
                a(x, y) = 1.0;
                b(x, y) = 2.0;
                c(x, y) = 3.0;
                d(x, y) = 4.0;
            }
        }

        Matrix<double> result = a + b + c + d;  // result(x, y) = 10 
    }

    void test_02()
    {
        std::cout << "Expression Template 02:" << std::endl;

        Matrix<double> a;
        Matrix<double> b;
        Matrix<double> c;
        Matrix<double> d;
        Matrix<double> result;

        // initialize matrices
        for (size_t y = 0; y != a.getRows(); ++y) {
            for (size_t x = 0; x != a.getCols(); ++x) {
                a(x, y) = 1.0;
                b(x, y) = 2.0;
                c(x, y) = 3.0;
                d(x, y) = 4.0;
            }
        }

        // adding 2 matrices
        MatrixSum<Matrix<double>, Matrix<double>> sumAB(a, b);
        for (size_t y = 0; y != a.getRows(); ++y) {
            for (size_t x = 0; x != a.getCols(); ++x) {
                result(x, y) = sumAB(x, y);
            }
        }

        // adding 3 matrices
        MatrixSum<MatrixSum<Matrix<double>, Matrix<double>>, Matrix<double>> sumABC(sumAB, c);
        for (size_t y = 0; y != a.getRows(); ++y) {
            for (size_t x = 0; x != a.getCols(); ++x) {
                result(x, y) = sumABC(x, y);
            }
        }

        // adding 4 matrices
        MatrixSum<MatrixSum<MatrixSum<Matrix<double>, Matrix<double>>, Matrix<double>>, Matrix<double>> sumABCD{ sumABC, d };
        for (size_t y = 0; y != a.getRows(); ++y) {
            for (size_t x = 0; x != a.getCols(); ++x) {
                result(x, y) = sumABCD(x, y);
            }
        }
    }

    void test_03()
    {
        std::cout << "Expression Template 03: Expression Templates Approach" << std::endl;

        Matrix<double> a;
        Matrix<double> b;
        Matrix<double> c;
        Matrix<double> d;
        Matrix<double> result;

        // initialize matrices
        for (size_t y = 0; y != a.getRows(); ++y) {
            for (size_t x = 0; x != a.getCols(); ++x) {
                a(x, y) = 1.0;
                b(x, y) = 2.0;
                c(x, y) = 3.0;
                d(x, y) = 4.0;
            }
        }

        // adding 4 matrices using modified operator=
        MatrixSum<Matrix<double>, Matrix<double>> sumAB{ a, b };
        MatrixSum<MatrixSum<Matrix<double>, Matrix<double>>, Matrix<double>> sumABC{ sumAB, c };
        MatrixSum<MatrixSum<MatrixSum<Matrix<double>, Matrix<double>>, Matrix<double>>, Matrix<double>> sumABCD{ sumABC, d };

        result = sumABCD;
    }

    // =====================================================================================

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
        MatrixSum<Matrix<double>, Matrix<double>> sumAB{ a1, a2 };
        MatrixSum<MatrixSum<Matrix<double>, Matrix<double>>, Matrix<double>> sumABC{ sumAB, a3 };
        MatrixSum<MatrixSum<MatrixSum<Matrix<double>, Matrix<double>>, Matrix<double>>, Matrix<double>> sumABCD{ sumABC, a4 };
        MatrixSum<MatrixSum<MatrixSum<MatrixSum<Matrix<double>, Matrix<double>>, Matrix<double>>, Matrix<double>>, Matrix<double>> sumABCDE{ sumABCD, a5 };

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            result = sumABCDE;
        }
        auto end = std::chrono::high_resolution_clock::now();

        std::cout
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << " milliseconds." << std::endl;
    }

    void test_04_benchmark()
    {
        std::cout << "Expression Templates 04 (Benchmark):" << std::endl;

        Matrix<double> a(BenchmarkCols, BenchmarkRows);
        Matrix<double> b(BenchmarkCols, BenchmarkRows);
        Matrix<double> c(BenchmarkCols, BenchmarkRows);
        Matrix<double> d(BenchmarkCols, BenchmarkRows);
        Matrix<double> e(BenchmarkCols, BenchmarkRows);
        Matrix<double> result(BenchmarkCols, BenchmarkRows);

        // initialize matrices
        for (size_t y = 0; y != a.getRows(); ++y) {
            for (size_t x = 0; x != a.getCols(); ++x) {
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

void main_expression_templates()
{
    using namespace ExpressionTemplates;
    //test_01();                  // <== classical approach
    //test_02();
    //test_03();                  // <== expression templates approach
    test_04_benchmark();        // <== benchmark
}

// =====================================================================================
// End-of-File
// =====================================================================================
