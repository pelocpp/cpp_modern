// =====================================================================================
// Sfinae02.cpp // SFINAE and enable_if
// =====================================================================================

module modern_cpp:sfinae;

namespace SFINAE_02 {

    // =================================================================================
    // Beispiel stammt aus dem Buch von Peter Gottschling, "Modernes C++"
    // =================================================================================

    template <typename T>
    struct Magnitude
    {
        using type = T;
    };

    template <typename T>
    struct Magnitude<std::complex<T>>
    {
        using type = T;
    };

    template <typename T>
    struct Magnitude<std::vector<T>>
    {
        using type = T;
    };

    template <typename T>
    using Magnitude_t = typename Magnitude<T>::type;

    template <typename T>
    auto inline min_abs(const T& x, const T& y) -> typename Magnitude<T>::type
    {
        auto ax = std::abs(x);
        auto ay = std::abs(y);

        return (ax < ay) ? ax : ay;
    }

    // ==============================================

    template <bool B, typename T>
    struct enable_if_c
    {
        using type = T;
    };

    template <typename T>
    struct enable_if_c<false, T>
    {};

    // ==============================================

    template <typename T>
    struct is_vector : std::false_type
    {};

    template <typename T>
    struct is_vector<std::vector<T>> : std::true_type
    {};

    // ==============================================

    // https://stackoverflow.com/questions/41438493/how-to-identifying-whether-a-template-argument-is-stdcomplex

    template<typename T>
    struct is_complex_t : public std::false_type {};

    template<typename T>
    struct is_complex_t<std::complex<T>> : public std::true_type {};

    template<typename T>
    constexpr bool is_complex() { return is_complex_t<T>::value; }

    // ==============================================

    template <typename T>
    typename enable_if_c<is_complex_t<T>::value, typename Magnitude<T>::type>::type
        norm(const T& c)
    {
        Magnitude_t<T> mag{ std::abs(c) };
        return mag;
    }

    template <typename T>
    typename enable_if_c<is_vector<T>::value, typename Magnitude<T>::type>::type
        norm(const T& v)
    {
        Magnitude_t<T> sum{};
        for (unsigned r = 0; r < size(v); r++)
            sum += std::abs(v[r]);
        return sum;
    }

    // ==============================================

    void test_is_complex() {
        constexpr bool int_is_complex = is_complex<int>(); //false
        constexpr bool complex_is_complex = is_complex<std::complex<float>>(); //true
    }

    void test_enable_if_01() {
        std::complex<double> number(1.0, 4.0);
        double m = norm(number);
        std::cout << number << ", Magnitude: " << m << std::endl;

        std::vector<int> numbers{ 1, 2, 3, 4, 5 };
        m = norm(numbers);
        std::cout << "Vector Magnitude: " << m << std::endl;
    }

    void test_enable_if_02() {
        std::complex<double> number(1.0, 4.0);
        double m = norm(number);
        std::cout << number << ", Magnitude: " << m << std::endl;

        std::vector<int> numbers{ 1, 2, 3, 4, 5 };
        m = norm(numbers);
        std::cout << "Vector Magnitude: " << m << std::endl;

        std::complex<double> number1(1.0, 4.0);
        std::complex<double> number2(1.0, 4.0);
        std::cout << "min_abs: " << min_abs(number1, number2) << std::endl;
    }
}

void main_sfinae_02()
{
    using namespace SFINAE_02;
    test_is_complex();
    test_enable_if_01();
    test_enable_if_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
