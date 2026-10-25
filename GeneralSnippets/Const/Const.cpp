// =====================================================================================
// Const.cpp
// =====================================================================================

module modern_cpp:const_variants;

import std;

namespace {

    // ============================================================
    // const

    int computeNumber() {
        return 456;
    }

    void const_01()
    {
        const int importantNum{ 123 };

        // will be initialized at runtime
        const int anotherImportantNumber{ computeNumber() };
    }

    // ============================================================
    // constexpr

    class Point
    {
    private:
        double m_x{ 0 };
        double m_y{ 0 };

    public:
        // c'tor
        constexpr Point() : m_x{}, m_y{} {}
        constexpr Point(double x, double y) : m_x{ x }, m_y{ y } {}

        // getter
        constexpr double getX() const { return m_x; }
        constexpr double getY() const { return m_y; }
    };

    void const_02()
    {
        // computed at compile time
        constexpr Point a{ 123, 456 };

        static_assert(a.getX() == 123.0);
        static_assert(a.getY() == 456);

        constexpr double x = a.getX();

        // computed at runtime
        Point b{ 111, 222 };
        // constexpr double y = b.getY();  // does not compile
        double z = b.getY();
    }

    // ============================================================
    // consteval

    consteval int sum_consteval(int a, int b)
    {
        return a + b;
    }

    constexpr int sum_constexpr(int a, int b)
    {
        return a + b;
    }

    void const_03()
    {
        // consteval auto x = 123; // error: 'x' cannot be declared with 'consteval' specifier

        constexpr auto a{ sum_consteval(111, 222) };
        static_assert(a == 333);

        auto b{ 10 };

        auto c{ sum_constexpr(b, 10) };        // fine with constexpr function

        // auto d{ sum_consteval(b, 10) };     // Error! the value of 'b' cannot be used as constant
    }

    // ============================================================
    // constinit

    // init at compile time
    constexpr int power(int n) { return n * n; }

    constinit int g_global{ power(10) };

    // constinit int another{ global };  // does not compile

    void const_04()
    {
        // it's allowed to change a constinit variable later...
        g_global = 123;

        ++g_global;
    }

    constinit int g_len{ 10 };
    // std::array<int, g_len> arr;      // does not compile


    // ============================================================
    // mixing

    // possible and compiles... constexpr would probably be a better choice
    constinit const int i{};

    // constexpr constinit int j{};   // does not compile

    // compiles
    const constexpr int k{};

    // ============================================================
    // comparison of const variants: functions

    int productRunTime(int n, int m)
    {
        return n * m;
    }

    consteval int productCompileTime(int n, int m)
    {
        return n * m;
    }

    constexpr int productRunOrCompileTime(int n, int m)
    {
        return n * m;
    }

    void const_05()
    {
        // constexpr int prod1{ productRunTime(5, 10) };    // Error: expression did not evaluate to a constant

        constexpr int prod2{ productCompileTime(5, 10) };

        constexpr int prod3{ productRunOrCompileTime(5, 10) };

        int x{ 123 };

        int prod4{ productRunTime(5, x) };

        // int prod5{ productCompileTime(5, x) };          // Error: call to immediate function is not a constant expression

        int prod6{ productRunOrCompileTime(5, x) };
    }

    // ============================================================
    // comparison of const variants: variables

    constexpr int constexprVal{ 123 };

    constinit int constinitVal{ 456 };

    int inc(int val) {
        return ++val;
    }

    void const_06()
    {
        auto value{ 123 };

        const auto result{ inc(value) };

        std::println("Result: {}", result);

        // ++result;         // Error: Expression must be a modifiable lvalue

        // ++constexprVal;   // Error: Expression must be a modifiable lvalue

        ++constinitVal;

        constexpr auto localConstexpr{ 123 };

        // constinit auto localConstinit{ 123 }; // Error: 'constinit' only allowed on a variable declaration with static or thread storage
    }
}

void main_const_variants()
{
    const_01();
    const_02();
    const_03();
    const_04();
    const_05();
    const_06();
}

// =====================================================================================
// End-of-File
// =====================================================================================
