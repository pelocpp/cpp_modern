// =====================================================================================
// Apply.cpp // std::apply // std::integer_sequence
// =====================================================================================

module modern_cpp:apply;

namespace ApplyIntegerSequence {

    // class definition (type which holds sequences)
    template <int ... NS>
    struct sequence
    {};

    // helper class template declaration
    template <int ... NS>
    struct sequence_helper;

    // helper class template: recursion case
    template <int N, int ... NS>
    struct sequence_helper<N, NS ...>
    {
        using type = typename sequence_helper<N-1, N-1, NS ...>::type;
    };

    // recursion termination
    template <int ... NS>
    struct sequence_helper<0, NS ...>
    {
        using type = sequence<NS ...>;
    };

    template <int N>
    using make_index_sequence = typename sequence_helper<N>::type;

    // -----------------------------------------------------------

    static void test01()
    {
        auto seq = make_index_sequence<4>{};
        sequence<0, 1, 2, 3> seq2 = make_index_sequence<4>{};
    }

    // ===========================================================

    // alternate implementation - using inheritance
    template <std::size_t ...>
    struct sequence_ex
    {};

    template <std::size_t N, std::size_t ... NS>
    struct sequence_helper_ex : public sequence_helper_ex<N - 1U, N - 1U, NS ...>
    {};

    template <std::size_t ... NS>
    struct sequence_helper_ex<0U, NS ... >
    {
        using type = sequence_ex<NS ... >;
    };

    template <std::size_t N>
    using make_index_sequence_ex = typename sequence_helper_ex<N>::type;

    // -----------------------------------------------------------

    static void test02()
    {
        auto seq = make_index_sequence_ex<4U>{};
        sequence_ex<0U, 1U, 2U, 3U> seq2 = make_index_sequence_ex<4U>{};
    }

    // ===========================================================

    // demonstrating mapping a function call to arguments of a tuple
    // with the help of an int sequence:

    static void f(double x, std::string y, int z)
    {
        std::cout << x << std::endl;
        std::cout << y << std::endl;
        std::cout << z << std::endl;
    }

    template <typename TFUNC, typename TUPLE, int ... TINDICES>
    static void tuple_call_(TFUNC func, TUPLE tuple, sequence<TINDICES...>)
    {
        func(std::get<TINDICES>(tuple) ...);
    }

    template <typename TFUNC, typename ... TS>
    static void tuple_call(TFUNC func, std::tuple<TS ...> tuple)
    {
        tuple_call_(func, tuple, make_index_sequence<sizeof...(TS)> {});
    }

    // self-written 'tuple_call' function
    static void test03()
    {
        std::tuple<double, std::string, int> someTuple = std::make_tuple<>(123.456, std::string("ABC"), 789);
        f(std::get<0>(someTuple), std::get<1>(someTuple), std::get<2>(someTuple));
        tuple_call(f, someTuple); // same effect
    }

    // using standard STL function 'std::apply'
    static void test04()
    {
        std::tuple<double, std::string, int> someTuple = std::make_tuple<>(123.456, std::string("ABC"), 789);
        f(std::get<0>(someTuple), std::get<1>(someTuple), std::get<2>(someTuple));
        std::apply(f, someTuple); // same effect
    }

    // ===========================================================

    // https://riptutorial.com/cplusplus/example/4331/iterating-with-std--integer-sequence

    // https://stackoverflow.com/questions/24109737/what-are-some-uses-of-decltypeauto

    static int g(double x, std::string y, int z, char ch)
    {
        std::cout << x << std::endl;
        std::cout << y << std::endl;
        std::cout << z << std::endl;
        std::cout << ch << std::endl;

        return 999;
    }

    namespace detail
    {
        template <class F, class Tuple, std::size_t... Is>
        decltype(auto) apply_impl(F&& f, Tuple&& tpl, std::index_sequence<Is...>) {
            return std::forward<F>(f)(std::get<Is>(std::forward<Tuple>(tpl))...);
        }

        template <class F, class Tuple, std::size_t... Is>
        decltype(auto) apply_impl_ex(F&& f, Tuple&& tpl, sequence<Is...>) {
            return std::forward<F>(f)(std::get<Is>(std::forward<Tuple>(tpl))...);
        }
    }

#if ! defined(__GNUC__)
    namespace pelo
    {
        template <class F, class Tuple>
        decltype(auto) apply(F&& f, Tuple&& tpl) {
            return detail::apply_impl(
                std::forward<F>(f),
                std::forward<Tuple>(tpl),
                std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{});
        }

        template <class F, class Tuple>
        decltype(auto) apply_ex(F&& f, Tuple&& tpl) {
            return detail::apply_impl_ex(
                std::forward<F>(f),
                std::forward<Tuple>(tpl),
                make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{});
        }
    }

    static void test05()
    {
        auto some_args = std::make_tuple(43.43, std::string{ "ABCD" }, 123, '?');
        auto result = pelo::apply(g, some_args); // calls g(43.43, "ABCD", 123, '?')
        std::cout << result << std::endl;

        auto some_args_ex = std::make_tuple(43.43, std::string{ "ABCD" }, 123, '?');
        auto result_ex = pelo::apply_ex(g, some_args); // calls g(43.43, "ABCD", 123, '?')
        std::cout << result_ex << std::endl;
    }
#endif
}

void main_apply()
{
    using namespace ApplyIntegerSequence;
    test01();
    test02();
    test03();
    test04();

#if ! defined(__GNUC__)
    test05();
#endif
}

// =====================================================================================
// End-of-File
// =====================================================================================
