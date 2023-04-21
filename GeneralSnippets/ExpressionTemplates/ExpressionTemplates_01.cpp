// =====================================================================================
// ExpressionTemplates_01.cpp // Expression Templates
// =====================================================================================

module modern_cpp:expression_templates;

namespace ExpressionTemplates {

    constexpr bool Verbose{ false };

    using ElemType = double;                 // <== modify values here

    // default sizes
    constexpr size_t DefaultSize{ 5 };

    // benchmark sizes
    constexpr int Iterations{ 500000 };
    constexpr size_t BenchmarkSize{ 50 };

    // actual sizes
    constexpr size_t Size{ DefaultSize };    // <== modify values here

    template<size_t N, typename T = ElemType>
    class Matrix 
    {
    private:
        std::array<std::array<T, N>, N> m_values;

    public:
        // c'tor(s)
        Matrix() : Matrix{ T{} } {}

        Matrix(T preset) {
            std::for_each(
                std::begin(m_values),
                std::end(m_values),
                [=](auto& row) {
                    row.fill(preset);
                }
            );
        }

        // getter
        size_t inline getSize() const { return N; };

        // functor - representing index operator
        const T& operator()(size_t x, size_t y) const {
            return m_values[x][y];
        };

        T& operator()(size_t x, size_t y) {
            return m_values[x][y];
        }

        // operator+ --> classical implementation
        Matrix<N> operator+(const Matrix<N>& other) const
        {
            Matrix<N> result;
            for (size_t y{}; y != N; ++y) {
                for (size_t x{}; x != N; ++x) {
                    result.m_values[x][y] = m_values[x][y] + other.m_values[x][y];
                }
            }
            return result;
        }

        // operator= --> expression template approach
        template <typename TExpr>
        Matrix<N>& operator=(const TExpr& expr)
        {
            for (size_t y{}; y != N; ++y) {
                for (size_t x{}; x != N; ++x) {
                    m_values[x][y] = expr(x, y);
                }
            }
            return *this;
        }

        // just for demonstration purposes
        static Matrix<N> add3(const Matrix<N>& a, const Matrix<N>& b, const Matrix<N>& c)
        {
            Matrix<N> result;

            for (size_t y{}; y != a.getSize(); ++y) {
                for (size_t x{}; x != a.getSize(); ++x) {
                    result.m_values[x][y] = a.m_values[x][y] + b.m_values[x][y] + c.m_values[x][y];
                }
            }
            return result;
        }
    };

    // ========================================================================

    template <typename TLhs, typename TRhs, typename T = ElemType>
    class MatrixExpr
    {
    private:
        const TLhs& m_lhs;
        const TRhs& m_rhs;

    public:
        MatrixExpr(const TLhs& lhs, const TRhs& rhs) : m_rhs{ rhs }, m_lhs{ lhs } {}

        T operator() (size_t x, size_t y) const {
            return m_lhs(x, y) + m_rhs(x, y);
        }
    };

    template <typename TLhs, typename TRhs>
    MatrixExpr<TLhs, TRhs> operator+(const TLhs& lhs, const TRhs& rhs) {
        return MatrixExpr<TLhs, TRhs>(lhs, rhs);
    }

    // ========================================================================

    void test_00()
    {
        std::cout << "Expression Template 00: Very Classical Approach" << std::endl;

        Matrix<Size> result{};
        Matrix<Size> a{ 1.0 }, b{ 2.0 }, c{ 3.0 }, d{ 4.0 };

        result = Matrix<Size>::add3(a, b, c);
    }

    void test_01()
    {
        std::cout << "Expression Template 01: Classical Approach" << std::endl;

        Matrix<Size> result{};
        Matrix<Size> a{ 1.0 }, b{ 2.0 }, c{ 3.0 }, d{ 4.0 };
        result = a + b;          // result(x, y) = 3.0
        result = a + b + c + d;  // result(x, y) = 10 
    }

    void test_02()
    {
        std::cout << "Expression Template 02:" << std::endl;

        Matrix<Size> a{ 1.0 }, b{ 2.0 }, c{ 3.0 }, d{ 4.0 };
        Matrix<Size> result{};

        // adding 2 matrices
        MatrixExpr<Matrix<Size>, Matrix<Size>> sumAB(a, b);
        for (size_t y{}; y != a.getSize(); ++y) {
            for (size_t x{}; x != a.getSize(); ++x) {
                result(x, y) = sumAB(x, y);
            }
        }

        // adding 3 matrices
        MatrixExpr<MatrixExpr<Matrix<Size>, Matrix<Size>>, Matrix<Size>> sumABC(sumAB, c);
        for (size_t y{}; y != a.getSize(); ++y) {
            for (size_t x{}; x != a.getSize(); ++x) {
                result(x, y) = sumABC(x, y);
            }
        }

        // adding 4 matrices
        MatrixExpr<MatrixExpr<MatrixExpr<Matrix<Size>, Matrix<Size>>, Matrix<Size>>, Matrix<Size>> sumABCD{ sumABC, d };
        for (size_t y{}; y != a.getSize(); ++y) {
            for (size_t x{}; x != a.getSize(); ++x) {
                result(x, y) = sumABCD(x, y);
            }
        }
    }

    void test_03_00()
    {
        std::cout << "Expression Template 03: Expression Templates Approach" << std::endl;

        Matrix<Size> a{ 1.0 };
        Matrix<Size> b{ 2.0 };
        Matrix<Size> c{ 3.0 };
        Matrix<Size> d{ 4.0 };
        Matrix<Size> result{};

        // adding 4 matrices using modified operator=
        //MatrixExpr<Matrix<Size>, Matrix<Size>> sumAB{ a, b };
        //MatrixExpr<MatrixExpr<Matrix<Size>, Matrix<Size>>, Matrix<Size>> sumABC{ sumAB, c };
        //MatrixExpr<MatrixExpr<MatrixExpr<Matrix<Size>, Matrix<Size>>, Matrix<Size>>, Matrix<Size>> sumABCD{ sumABC, d };

        // or - using template argument type deduction:
        MatrixExpr sumAB{ a, b };
        MatrixExpr sumABC{ sumAB, c };
        MatrixExpr sumABCD{ sumABC, d };

        result = sumABCD;
    }

    void test_03()
    {
        std::cout << "Expression Template 03: Expression Templates Approach" << std::endl;

        Matrix<Size> a{ 1.0 }, b{ 2.0 }, c{ 3.0 }, d{ 4.0 };
        Matrix<Size> result{};

        // adding 4 matrices using modified operator=
        // MatrixExpr<Matrix, Matrix> sumAB{ a, b };
        // MatrixExpr<MatrixExpr<Matrix, Matrix>, Matrix> sumABC{ sumAB, c };
        // MatrixExpr<MatrixExpr<MatrixExpr<Matrix, Matrix>, Matrix>, Matrix> sumABCD{ sumABC, d };

        // or - using template argument type deduction:
        MatrixExpr sumAB{ a, b };
        MatrixExpr sumABC{ sumAB, c };
        MatrixExpr sumABCD{ sumABC, d };

        result = sumABCD;
    }

    // =====================================================================================

    void test_04a_benchmark(
        int iterations,
        Matrix<Size>& result,
        const Matrix<Size>& a1,
        const Matrix<Size>& a2,
        const Matrix<Size>& a3,
        const Matrix<Size>& a4,
        const Matrix<Size>& a5)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (size_t i{}; i != iterations; ++i) {
            result = a1 + a2 + a3 + a4 + a5;
        }
        auto end = std::chrono::high_resolution_clock::now();

        std::cout
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << " milliseconds." << std::endl;
    }

    void test_04b_benchmark(
        int iterations,
        Matrix<Size>& result,
        const Matrix<Size>& a1,
        const Matrix<Size>& a2,
        const Matrix<Size>& a3,
        const Matrix<Size>& a4,
        const Matrix<Size>& a5)
    {
        // adding 5 matrices with expression template approach
        //MatrixExpr<Matrix<Size>, Matrix<Size>> sumAB{ a1, a2 };
        //MatrixExpr<MatrixExpr<Matrix<Size>, Matrix<Size>>, Matrix<Size>> sumABC{ sumAB, a3 };
        //MatrixExpr<MatrixExpr<MatrixExpr<Matrix<Size>, Matrix<Size>>, Matrix<Size>>, Matrix<Size>> sumABCD{ sumABC, a4 };
        //MatrixExpr<MatrixExpr<MatrixExpr<MatrixExpr<Matrix<Size>, Matrix<Size>>, Matrix<Size>>, Matrix<Size>>, Matrix<Size>> sumABCDE{ sumABCD, a5 };

        // or - using template argument type deduction:
        MatrixExpr sumAB{ a1, a2 };
        MatrixExpr sumABC{ sumAB, a3 };
        MatrixExpr sumABCD{ sumABC, a4 };
        MatrixExpr sumABCDE{ sumABCD, a5 };

        auto start = std::chrono::high_resolution_clock::now();
        for (size_t i{}; i != iterations; ++i) {
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

        Matrix<Size> a{ 1.0 }, b{ 2.0 }, c{ 3.0 }, d{ 4.0 }, e{ 5.0 };
        Matrix<Size> result{};

        std::cout << "Start:" << std::endl;
        test_04a_benchmark(Iterations, result, a, b, c, d, e);
        test_04b_benchmark(Iterations, result, a, b, c, d, e);
        std::cout << "Done." << std::endl;
    }
}

void main_expression_templates()
{
    using namespace ExpressionTemplates;
    test_01();            // <== classical approach
    test_02();            // <== expression templates approach
    test_03();            // <== expression templates approach using modified operator=
    test_04_benchmark();  // <== benchmark
}

// =====================================================================================
// End-of-File
// =====================================================================================