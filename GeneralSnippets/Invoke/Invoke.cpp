// =====================================================================================
// Invoke.cpp // std::invoke
// =====================================================================================

module modern_cpp:invoke;

import std;

namespace {

    // helper functions / classes
    int add(int a, int b)
    {
        return a + b;
    }

    class Incrementer
    {
    public:
        int m_x;

    public:
        Incrementer() : m_x{} {}
        Incrementer(int x) : m_x{ x } {}

        void incrementBy(int n) { m_x += n; }
        void operator()() { std::println("m_x: {}", m_x); }
    };

    class TimesThree
    {
    public:
        int operator()(int n) { return 3 * n; }
    };

    // testing scenarios for std::invoke
    void invoke_01()
    {
        int result{};

        // free function:
        result = std::invoke(add, 1, 2);
        std::println("result: {}", result);
        // => 3

        // free function through pointer to function:
        result = std::invoke(&add, 3, 4);
        std::println("result: {}", result);
        // => 7

        int(*fadd) (int, int) { &add };
        result = std::invoke(fadd, 5, 6);
        std::println("result: {}", result);
        // => 11

        // member function through pointer to member function:
        Incrementer inc{};
        std::invoke(&Incrementer::incrementBy, &inc, 5);
        inc();  // output
        // => 5

        // invoke (access) a (public) data member (!):
        // C++20: useful for 'projections'
        result = std::invoke(&Incrementer::m_x, &inc);
        std::println("result: {}", result);

        // (nested) function objects:
        Incrementer inc2{ 10 };
        result = std::invoke(std::plus<>(), std::invoke(&Incrementer::m_x, &inc2), 3);
        std::println("result: {}", result);
        // => 13

        result = std::invoke(TimesThree{}, 5);
        std::println("result: {}", result);
        // => 15

        // lambda expression:
        result = std::invoke([](auto a, auto b) {return a + b; }, 11, 12);
        std::println("result: {}", result);
        // => 23
    }
}

void main_invoke()
{
    invoke_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
