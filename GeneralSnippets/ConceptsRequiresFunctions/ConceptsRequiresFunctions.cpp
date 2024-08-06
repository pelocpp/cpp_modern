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

    static void test_concepts_requires_01()
    {
        auto sum1{ add(123.456f, 654.321f) };
        std::cout << sum1 << std::endl;

        auto sum2{ add(123.456, 654.321) };
        std::cout << sum2 << std::endl;

        // 'add': no matching overloaded function found		
        // template parameter 'T' is ambiguous
        //   could be 'float'
        //   or 'double'
        // auto sum3 = add(123.456, 654.321F);

        //'add': no matching overloaded function found
        //    the associated constraints are not satisfied
        //    the concept 'Numerical<std::string>' evaluated to false
        //    the concept 'std::floating_point<std::string>' evaluated to false
        //    the concept 'std::integral<std::string>' evaluated to false
        // auto sum4 = add(std::string { "ABC" }, std::string { "DEF" });
    }

    // ---------------------------------------------------------------------------------
    // several, different template parameters

    template <typename T, typename U>
        requires Numerical<T> && Numerical<U>
    auto add(T a, U b)
    {
        return a + b;
    }

    static void test_concepts_requires_02()
    {
        auto sum{ add(123.456, 654.321F) };
        std::cout << sum << std::endl;
    }
    
    static void test_concepts_requires_03()
    {
        std::string s1{ "ABC" };
        std::string s2{ "DEF" };

        // the associated constraints are not satisfied:
        // auto result{ add(s1, s2) };
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

    static void test_concepts_requires_04()
    {
        std::vector<int> numbers{ 1, 2, 3, 4, 5 };
        std::vector<double> moreNumbers{ 1, 2, 3, 4, 5 };
 
        auto average{ avg(numbers) };

        // the associated constraints are not satisfied:
        // auto anotherAverage{ avg(moreNumbers) };
    }

    static void test_concepts_requires_basic_usage()
    {
        test_concepts_requires_01();
        test_concepts_requires_02();
        test_concepts_requires_03();
        test_concepts_requires_04();
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

    static void test_trailing_requires_clause()
    {
        auto sum1{ add(123.456f, 654.321f) };
        std::cout << sum1 << std::endl;

        auto sum2{ add(123.456, 654.321) };
        std::cout << sum2 << std::endl;

        auto sum3{ add(123.456, 654.321F) };
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

    static void test_constrained_template_parameters()
    {
        auto sum1{ add(123.456f, 654.321f) };
        std::cout << sum1 << std::endl;

        auto sum2{ add(123.456, 654.321) };
        std::cout << sum2 << std::endl;

        auto sum3{ add(123.456, 654.321F) };
        std::cout << sum3 << std::endl;
    }
}

namespace Abbreviated_Function_Templates {

    static auto add(Numerical auto a, Numerical auto b)
    {
        return a + b;
    }

    static void test_abbreviated_function_template_syntax()
    {
        auto sum1{ add(123.456f, 654.321f) };
        std::cout << sum1 << std::endl;

        auto sum2{ add(123.456, 654.321) };
        std::cout << sum2 << std::endl;

        auto sum3{ add(123.456, 654.321F) };
        std::cout << sum3 << std::endl;
    }
}

namespace UserDefined_Concept {

    template<typename T>
    constexpr bool isGreaterThanWord{ sizeof(T) > 2 };

    // using <type_traits>
    template <typename T>
    concept GreatIntegral = std::is_integral<T>::value && isGreaterThanWord<T>;

    template<GreatIntegral T>
    T incrementByOne(const T& arg) {
        return arg + 1;
    }

    auto incrementByTwo(GreatIntegral auto arg) {
        return arg + 2;
    }

    static void test_user_defined_concept()
    {
        auto n{ 123 };

        n = incrementByOne(n);

        // short s{ 1 };
        // the associated constraints are not satisfied:
        // s = incrementByOne(s);

        n = incrementByTwo(n);

        // short s{ 1 };
        // the associated constraints are not satisfied:
        // s = incrementByTwo(s);
    }
}

void main_concepts_requires_functions()
{
    Requires_Clause::test_concepts_requires_basic_usage();
    Trailing_Requires_Clause::test_trailing_requires_clause();
    Constrained_Template_Parameters::test_constrained_template_parameters();
    Abbreviated_Function_Templates::test_abbreviated_function_template_syntax();
    UserDefined_Concept::test_user_defined_concept();
}

// =====================================================================================
// End-of-File
// =====================================================================================

