// =====================================================================================
// MetaProgramming02.cpp // Metaprogramming: Part II
// =====================================================================================

module modern_cpp:metaprogramming;

namespace Metaprogramming {

    struct Nil {
        using Head = Nil;
        using Tail = Nil;
    };

    template <typename H, typename T = Nil>
    struct List {
        using Head = H;
        using Tail = T;
    };

    template <int N>
    struct Int { static constexpr int result = N; };

    static void test_06() {
        // List(1, List(2, List(3, Nil)))
        using OneTwoThree = List<Int<1>, List<Int<2>, List<Int<3>>>>;
    }

    template <typename LIST>
    struct LengthVerbose {
        using Tail = typename LIST::Tail;
        static constexpr unsigned int tailLength = LengthVerbose<Tail>::result;
        static constexpr unsigned int result = 1 + tailLength;
    };

    template <>
    struct LengthVerbose<Nil> {
        static constexpr unsigned int result = 0;
    };

    // or 

    template <typename LIST>
    struct Length {
        static constexpr unsigned int result = 1 + Length<typename LIST::Tail>::result;
    };

    template <>
    struct Length<Nil> {
        static constexpr unsigned int result = 0;
    };

    static void test_07() {
        // List (1, 2, 3, 4, 5) 
        using List12345 = List<Int<1>, List<Int<2>, List<Int<3>, List<Int<4>, List<Int<5>>>>>>;
        std::cout << LengthVerbose<List12345>::result << std::endl;
    }

    template <typename LIST, int N>
    struct Nth {
        using Tail = typename LIST::Tail;
        using result = typename Nth<Tail, N - 1>::result;
    };

    template <typename LIST>
    struct Nth<LIST, 0> {
        using result = typename LIST::Head;
    };

    static void test_08() {
        using List12345 = List<Int<1>, List<Int<2>, List<Int<3>, List<Int<4>, List<Int<5>>>>>>;
        std::cout << Nth<List12345, 3>::result::result << std::endl;
    }

    static void test_08a() {
        // out of range: doesn't compile
        // using List12345 = List<Int<1>, List<Int<2>, List<Int<3>, List<Int<4>, List<Int<5>>>>>>;
        // std::cout << Nth<List12345, 99>::result::result << std::endl;
    }

    template <typename X, typename Y>
    struct Equals { static constexpr bool result = false; };

    template <typename X>
    struct Equals<X, X> { static constexpr bool result = true; };

    template <typename Elm, typename LIST>
    struct Contains {
        using Head = typename LIST::Head;
        using Tail = typename LIST::Tail;

        static constexpr bool result = Equals<Elm, Head>::result || Contains<Elm, Tail>::result;

        // shorter
        // static constexpr bool result = Equals<Elm, typename LIST::Head>::result ||
        //    Contains<Elm, typename LIST::Tail>::result;
    };

    template <typename Elm>
    struct Contains<Elm, Nil> {
        static constexpr bool result = false;
    };

    static void test_09() {
        using List12345 = List<Int<1>, List<Int<2>, List<Int<3>, List<Int<4>, List<Int<5>>>>>>;
        std::cout << Contains<Int<5>, List12345>::result << std::endl;
        std::cout << Contains<Int<10>, List12345>::result << std::endl;
    }

    template <typename Elm, typename LIST = Nil>
    struct Prepend {
        using result = List<Elm, LIST>;
    };

    template <typename Elm, typename LIST>
    struct Append {
        using Head = typename LIST::Head;
        using Tail = typename LIST::Tail;

        using Next = typename Append<Elm, Tail>::result;
        using result = List<Head, Next>;
    };

    template <typename Elm>
    struct Append<Elm, Nil> {
        using result = List<Elm>;
    };

    static void test_10() {

        using List12345 = List<Int<1>, List<Int<2>, List<Int<3>, List<Int<4>, List<Int<5>>>>>>;

        using newList = Prepend<Int<0>, List12345>::result;
        std::cout << Length<newList>::result << std::endl;
        std::cout << Length<Prepend <Int<0>, List12345>::result>::result << std::endl;
        std::cout << Length<Prepend <Int<1>, newList>::result>::result << std::endl;

        std::cout << Length<Append <Int<6>, List12345>::result>::result << std::endl;
        std::cout << Length<Append <Int<7>, newList>::result>::result << std::endl;
    }
}

void main_metaprogramming_02()
{
    using namespace Metaprogramming;
    test_06();
    test_07();
    test_08();
    test_09();
    test_10();
}

// =====================================================================================
// End-of-File
// =====================================================================================
