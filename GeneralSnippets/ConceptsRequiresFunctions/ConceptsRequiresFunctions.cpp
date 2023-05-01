// =====================================================================================
// ConceptsRequiresFunctions.cpp
// =====================================================================================

module modern_cpp:concepts_requires_functions;

// using <concepts>
template <typename T>
concept Numerical = std::integral<T> || std::floating_point<T>;

// using <type_traits>
template <typename T>
concept NumericalEx = std::is_integral<T>::value || std::is_floating_point<T>::value;

namespace Requires_Clause {

    template <typename T>
    requires Numerical<T>
    auto add(T a, T b)
    {
        return a + b;
    }

    // "inlining" constraints on template parameter types
    template <typename T>
    requires std::integral<T> || std::floating_point<T>
    auto addEx(T a, T b)
    {
        return a + b;
    }

    void test_concepts_requires_variant_01_a()
    {
        float sum1 = add(123.456f, 654.321f);
        std::cout << sum1 << std::endl;

        auto sum2 = add(123.456, 654.321);
        std::cout << sum2 << std::endl;

        // no instance of function template "add" matches the argument list
        // auto sum3 = add(123.456, 654.321F);
    }

    template <typename T, typename U>
    requires Numerical<T> && Numerical<U>
    auto add(T a, U b)
    {
        return a + b;
    }

    void test_concepts_requires_variant_01_b()
    {
        auto sum = add(123.456, 654.321F);
        std::cout << sum << std::endl;
    }
    
    void test_concepts_requires_variant_01_c()
    {
        std::string s1{ "ABC" };
        std::string s2{ "ABC" };

        // the associated constraints are not satisfied:
        // auto result = add(s1, s2);
    }

    // using <type_traits>
    template<typename T>
    requires std::is_integral<T>::value
    double avg(const std::vector<T>& vec)
    {
        double sum{
            std::accumulate(
                vec.begin(),
                vec.end(),
                0.0
            )
        };

        return sum / vec.size();
    }

    void test_concepts_requires_variant_01_d()
    {
        std::vector<int> numbers{ 1, 2, 3, 4, 5 };
        std::vector<double> moreNumbers{ 1, 2, 3, 4, 5 };
 
        auto average = avg(numbers);

        // the associated constraints are not satisfied:
        // auto anotherAverage = avg(moreNumbers);
    }

    void test_concepts_requires_variant_01()
    {
        test_concepts_requires_variant_01_a();
        test_concepts_requires_variant_01_b();
        test_concepts_requires_variant_01_c();
        test_concepts_requires_variant_01_d();
    }
}

namespace Trailing_Requires_Clause {

    template <typename T>
    auto add(T a, T b) requires Numerical<T>
    {
        return a + b;  
    }

    template <typename T>
    auto addEx(T a, T b) requires std::integral<T> || std::floating_point<T>
    {
        return a + b;
    }

    template <typename T, typename U>
    auto add(T a, U b) requires Numerical<T> && Numerical<U>
    {
        return a + b;
    }

    void test_concepts_requires_variant_02()
    {
        float sum1 = add(123.456f, 654.321f);
        std::cout << sum1 << std::endl;

        auto sum2 = add(123.456, 654.321);
        std::cout << sum2 << std::endl;

        auto sum3 = add(123.456, 654.321F);
        std::cout << sum3 << std::endl;
    }
}

namespace Constrained_Template_Parameters {

    template <Numerical T>
    auto add(T a, T b)
    {
        return a + b;
    }

    template <Numerical T, Numerical U>
    auto add(T a, U b)
    {
        return a + b;
    }

    void test_concepts_requires_variant_03()
    {
        float sum1 = add(123.456f, 654.321f);
        std::cout << sum1 << std::endl;

        auto sum2 = add(123.456, 654.321);
        std::cout << sum2 << std::endl;

        auto sum3 = add(123.456, 654.321F);
        std::cout << sum3 << std::endl;
    }
}

namespace Abbreviated_Function_Templates {

    auto add(Numerical auto a, Numerical auto b)
    {
        return a + b;
    }

    void test_concepts_requires_variant_04()
    {
        float sum1 = add(123.456f, 654.321f);
        std::cout << sum1 << std::endl;

        auto sum2 = add(123.456, 654.321);
        std::cout << sum2 << std::endl;

        auto sum3 = add(123.456, 654.321F);
        std::cout << sum3 << std::endl;
    }
}

namespace Usedefined_Concept {

    template<typename T>
    constexpr bool isGreaterThanWord{ sizeof(T) > 2 };

    // using <type_traits>
    template <typename T>
    concept GreatIntegral = std::is_integral<T>::value && isGreaterThanWord<T>;

    template<GreatIntegral T>
    T incrementByOne(const T& arg) {
        return arg + 1;
    }

    void test_concepts_requires_variant_05()
    {
        int n{ 123 };
        n = incrementByOne(n);

        // short s{ 1 };
        // the associated constraints are not satisfied:
        // s = incrementByOne(s);
    }
}

void main_concepts_requires_functions()
{
    Requires_Clause::test_concepts_requires_variant_01();
    Trailing_Requires_Clause::test_concepts_requires_variant_02();
    Constrained_Template_Parameters::test_concepts_requires_variant_03();
    Abbreviated_Function_Templates::test_concepts_requires_variant_04();
    Usedefined_Concept::test_concepts_requires_variant_05();
}

// =====================================================================================
// End-of-File
// =====================================================================================

