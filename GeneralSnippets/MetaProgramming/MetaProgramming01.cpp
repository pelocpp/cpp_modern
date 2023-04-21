// =====================================================================================
// MetaProgramming01.cpp // Metaprogramming: Part I
// =====================================================================================

module modern_cpp:metaprogramming;

namespace Metaprogramming {

    template <long N>
    struct Factorial {
        static constexpr long result = N * Factorial<N - 1>::result;
    };

    template <>
    struct Factorial<1> {
        static constexpr long result = 1;
    };

    void test_01() {

        std::cout << Factorial<1>::result << std::endl;
        std::cout << Factorial<2>::result << std::endl;
        std::cout << Factorial<3>::result << std::endl;
        std::cout << Factorial<4>::result << std::endl;
        std::cout << Factorial<5>::result << std::endl;
        std::cout << Factorial<6>::result << std::endl;
        std::cout << Factorial<7>::result << std::endl;
        std::cout << Factorial<8>::result << std::endl;
        std::cout << Factorial<9>::result << std::endl;
        std::cout << Factorial<10>::result << std::endl;
        std::cout << Factorial<11>::result << std::endl;
        std::cout << Factorial<12>::result << std::endl;
        //std::cout << Factorial<13>::result << std::endl;
        //std::cout << Factorial<14>::result << std::endl;
        //std::cout << Factorial<15>::result << std::endl;
        //std::cout << Factorial<16>::result << std::endl;
        //std::cout << Factorial<17>::result << std::endl;
    }

    // =================================================================================

    template <size_t N, size_t D>
    struct Frac {
        static constexpr size_t Num = N;
        static constexpr size_t Den = D;
    };

    template <size_t N, typename F>
    struct ScalarMultiplication {
        using result = Frac<N * F::Num, F::Den>;
    };

    void test_02() {
        using TwoThirds = Frac<2, 3>;
        using FourThirds = ScalarMultiplication<2, TwoThirds>::result;
        std::cout << FourThirds::Num << "/" << FourThirds::Den << std::endl;
    }

    template <size_t X, size_t Y>
    struct GGT {
        static constexpr size_t result = GGT<Y, X % Y>::result;
    };

    template <size_t X>
    struct GGT<X, 0> {
        static constexpr size_t result = X;
    };

    template <typename F>
    struct FracNormalizedVerbose {
        static constexpr size_t ggt = GGT<F::Num, F::Den>::result;
        static constexpr size_t newNum = F::Num / ggt;
        static constexpr size_t newDen = F::Den / ggt;
        using result = Frac<newNum, newDen>;
    };

    template <typename F>
    struct FracNormalized {
        static constexpr size_t ggt = GGT<F::Num, F::Den>::result;
        using result = Frac<F::Num / ggt, F::Den / ggt>;
    };

    void test_03() {
        using Four = Frac<16, 4>;
        using FourNormalized = FracNormalizedVerbose<Four>::result;
        std::cout << FourNormalized::Num << "/" << FourNormalized::Den << std::endl;
        using Eight = Frac<32, 4>;
        using EightNormalized = FracNormalized<Eight>::result;
        std::cout << EightNormalized::Num << "/" << EightNormalized::Den << std::endl;
    }

    template <typename X1, typename Y1>
    struct SameBase {
        using X = typename ScalarMultiplication<Y1::Den, X1>::result;
        using Y = typename ScalarMultiplication<X1::Den, Y1>::result;
    };

    template <typename X, typename Y>
    struct Sum {
        using Base = SameBase<X, Y>;
        static constexpr size_t Num = Base::X::Num + Base::Y::Num;
        static constexpr size_t Den = Base::X::Den * Base::Y::Den;
        using result = typename FracNormalized<Frac<Num, Den>>::result;
    };

    void test_04() {
        using Frac1 = Frac<1, 3>;
        using Frac2 = Frac<4, 7>;
        using Result = Sum<Frac1, Frac2>::result;
        std::cout << Result::Num << "/" << Result::Den << std::endl;
    }

    // =================================================================================

    template <long N>
    struct E {
        // e = 1/0! + 1/1! + 1/2! + ...
        static constexpr long Den = Factorial<N>::result;
        using Term = Frac<1, Den>;
        using NextTerm = typename E<N - 1>::result;
        using result = typename Sum<Term, NextTerm>::result;
    };

    template <>
    struct E<0> {
        using result = Frac<1, 1>;
    };

    void test_05() {
        using X = E<8>::result;
        std::cout << "e = " << (1.0 * X::Num / X::Den) << std::endl;
        std::cout << "e = " << X::Num << "/" << X::Den << std::endl;
    }
}

void main_metaprogramming_01()
{
    using namespace Metaprogramming;
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
}

// =====================================================================================
// End-of-File
// =====================================================================================
