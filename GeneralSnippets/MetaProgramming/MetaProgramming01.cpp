// =====================================================================================
// Metaprogramming: Part I
// =====================================================================================

#include <iostream>

namespace Metaprogramming {

    template <int N>
    struct Factorial {
        static const int result = N * Factorial<N - 1>::result;
    };

    template <>
    struct Factorial<1> {
        static const int result = 1;
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
        //std::cout << Factorial<11>::result << std::endl;
        //std::cout << Factorial<12>::result << std::endl;
        //std::cout << Factorial<13>::result << std::endl;
        //std::cout << Factorial<14>::result << std::endl;
        //std::cout << Factorial<15>::result << std::endl;
        //std::cout << Factorial<16>::result << std::endl;
        //std::cout << Factorial<17>::result << std::endl;
    }

    template <int N, int D>
    struct Frak {
        static const long Num = N;
        static const long Den = D;
    };

    template <int N, typename F>
    struct ScalarMultiplication {
        using result = Frak<N * F::Num, N * F::Den>;
    };

    void test_02() {
        using TwoThirds = Frak< 2, 3 >;
        using Four_Sixths = ScalarMultiplication< 2, TwoThirds >::result;
        std::cout << Four_Sixths::Num << "/" << Four_Sixths::Den << std::endl;
    }

    template <int X, int Y>
    struct GGT {
        static const long result = GGT<Y, X % Y>::result;
    };

    template <int X>
    struct GGT<X, 0> {
        static const long result = X;
    };

    template <class F>
    struct FrakNormalizedVerbose {
        static const long ggt = GGT<F::Num, F::Den>::result;
        static const long newNum = F::Num / ggt;
        static const long newDen = F::Den / ggt;
        using result = Frak<newNum, newDen>;
    };

    template <class F>
    struct FrakNormalized {
        static const long ggt = GGT<F::Num, F::Den>::result;
        using result = Frak<F::Num / ggt, F::Den / ggt>;
    };

    void test_03() {
        using Four = Frak<16, 4>;
        using FourNormalized = FrakNormalizedVerbose<Four>::result;
        std::cout << FourNormalized::Num << "/" << FourNormalized::Den << std::endl;
        using Eight = Frak<32, 4>;
        using EightNormalized = FrakNormalized<Eight>::result;
        std::cout << EightNormalized::Num << "/" << EightNormalized::Den << std::endl;
    }

    template <typename X1, typename Y1>
    struct SameBase {
        using X = typename ScalarMultiplication<Y1::Den, X1>::result;
        using Y = typename ScalarMultiplication<X1::Den, Y1>::result;
    };

    template <typename X, typename Y>
    struct Sum {
        using BASE = SameBase<X, Y>;
        static const long Num = BASE::X::Num + BASE::Y::Num;
        static const long Den = BASE::Y::Den; // same as BASE::X::Den
        using result = typename FrakNormalized<Frak<Num, Den>>::result;
    };

    void test_04() {
        using Frak1 = Frak<3, 7>;
        using Frak2 = Frak<1, 7>;
        using Result = Sum<Frak1, Frak2>::result;
        std::cout << Result::Num << "/" << Result::Den << std::endl;
    }

    template <int N>
    struct E {
        // e = 1/0! + 1/1! + 1/2! + ...
        static const long Den = Factorial<N>::result;
        using Term = Frak<1, Den>;
        using NextTerm = typename E<N - 1>::result;
        using result = typename Sum<Term, NextTerm>::result;
    };

    template <>
    struct E<0> {
        using result = Frak<1, 1>;
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
