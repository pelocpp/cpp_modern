// =====================================================================================
// Decltype.cpp // decltype and std::declval
// =====================================================================================

module modern_cpp:decltype_keyword;

namespace Decltype {

    // decltype may modify type deduction, e.g. in generic lambdas
    // (decltype (t + u), decltype (t) or decltype (u) are valid)
    template <typename T, typename U>
    auto add(const T& t, const U& u) -> decltype (t + u)
    {
        return t + u;
    }

    // or without trailing return type:

    template <typename T, typename U>
    decltype (std::declval<T>() + std::declval<U>())
    add2(const T& t, const U& u)
    {
        return t + u;
    }

    static void test_01()
    {
        int n{ 1 };
        double d{ 2.7 };

        auto result = add(n, d);
        std::cout << result << std::endl;
    }

    static void test_02()
    {
         /* decltype in combination with metaprogramming techiques
         */

        std::vector<int> vec{ 1 };

        // yiedling a lvalue reference
        vec[0] = 123;

        std::vector<int>::value_type value = 123;

        // doesn't compile !!! type is int&, not int
        // decltype (vec[0]) anotherValue = 123;

        // int&
        decltype (vec[0]) anotherValue = value;

        // retrieve value type from vector
        using ValueType = std::remove_reference <decltype (vec[0])>::type;
        ValueType yetAnotherValue = 123;

        // same as:
        using AnotherValueType = std::remove_reference<int&>::type;
        AnotherValueType oneMoreValue = 123;

        // using std::vector's reference type
        std::vector<int>::reference refWert = value;

        // doesn't compile !!! type is int&, not int
        // std::vector<int>::reference refWert = 123;
    }

    // demonstrating decltype with entities / instances of types:
    static void test_03()
    {
        std::vector<int> vec;

        // decltype(vec) yields std::vector<int>,
        // so the next line is equivalent to 'std::vector<int> vec2;'
        decltype(vec) vec2;

        // foo returns the type of f, in this case float,
        // so this is equivalent to float foo(int b);
        float f{};
        auto foo(int b) -> decltype(f);
    }

    // demonstrating decltype with expressions:
    static void test_04()
    {
        // decltype(foo()) yields the type of 
        // whatever foo() returns, in this case: float:
        float foo();
        decltype(foo()) b = decltype(foo()){};

        //decltype yields void, so this is the same as void bar();
        std::vector<int> vec;
        auto bar() -> decltype(vec.push_back(int{}));
    }

    template<typename T, typename U>
    using sum_t = decltype(std::declval<T>() + std::declval<U>());

    template<typename T, typename U>
    sum_t<T, U> summe(T a, U b)
    {
        return a + b;
    }

    static void test_05()
    {
        sum_t<int, float> result{ summe(123, 123.99F) };
        std::cout << result << std::endl;
    }
}

namespace Decltype_Auto_Vs_Templates {

    // a) using auto, no trailing return type deduction
    static auto mimimum1(auto n, auto m) // -> decltype (n + m)
    {
        decltype (n + m) result;

        result = (n < m) ? n : m;

        return result;
    }

    // b) using auto and trailing return type deduction
    static auto mimimum2(auto n, auto m) -> decltype (n + m)
    {
        if (n < m)
            return n;
        else
            return m;
    }

    template <typename T, typename U>
    static auto mimimum3(T n, U m) -> decltype (n + m)
    {
        if (n < m)
            return n;
        else
            return m;
    }

    // c) *Not* using auto and *not* using trailing return type deduction
    //    demonstrating how return data type can be 'computed'
    template <typename T, typename U>
    decltype (std::declval<T>() + std::declval<U>()) static mimimum4(T n, U m)
    {
        if (n < m)
            return n;
        else
            return m;
    }

    static void test_06() {

        auto result1 = mimimum1(100.0, 200l);
        auto result2 = mimimum2(100.0, 200l);
        auto result3 = mimimum3(100.0, 200l);
        auto result4 = mimimum4(100.0, 200l);
    }
}

void main_decltype()
{
    using namespace Decltype;
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();

    using namespace Decltype_Auto_Vs_Templates;
    test_06();
}

// =====================================================================================
// End-of-File
// =====================================================================================
