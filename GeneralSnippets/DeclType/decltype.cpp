// =====================================================================================
// decltype and std::declval
// =====================================================================================

#include <iostream>
#include <vector>

namespace Decltype {

    // decltype may modify type deduction, e.g. in generic lamdas
    // (decltype (t + u), decltype (t) or decltype (u) are valid)
    template <typename T, typename U>
    auto add(const T& t, const U& u) -> decltype (t + u)
    {
        return t + u;
    }

    void test_decltype_01() {

        int n = 1;
        double d = 2.7;

        auto result = add(n, d);
        std::cout << result << std::endl;
    }

    // demonstrating decltype with entities / instances of types:
    void test_decltype_02() {

        std::vector<int> vec;

        // decltype(vec) yields std::vector<int>,
        // so the next line is equivalent to 'std::vector<int> v2;'
        decltype(vec) vec2;

        // foo returns the type of f, in this case float,
        // so this is equivalent to float foo(int b);
        float f;
        auto foo(int b) -> decltype(f);
    }

    // demonstrating decltype with expressions:
    void test_decltype_03() {
        // decltype(foo()) yields the type of whatever foo() returns,
        // in this case, float:
        float foo();
        decltype(foo()) b;

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

    void test_decltype_04() {
        sum_t<int, float> result = summe(123, 123.99F);
        std::cout << result << std::endl;
    }
}

int main_decltype()
{
    using namespace Decltype;
    test_decltype_01();
    test_decltype_02();
    test_decltype_03();
    test_decltype_04();
    return 1;
}

// =====================================================================================
// End-of-File
// =====================================================================================
