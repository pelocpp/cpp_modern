// =====================================================================================
// Generate.cpp // std::generate
// =====================================================================================

module;

#include <print>    // module implementation too unstable

module modern_cpp:generate;

import std;

namespace {

    void generate_01()
    {
        std::vector<int> values(10);

        for (std::size_t i{}; i != values.size(); ++i) {
            values[i] = 1;
        } 

        std::for_each (
            values.begin(),
            values.end(),
            [](auto n) { std::print("{} ", n); }
        );

        std::println();
    }

    void generate_02()
    {
        std::vector<int> values(10);

        std::fill(
            values.begin(),
            values.end(),
            2
        );

        std::for_each(
            values.begin(),
            values.end(),
            [](auto n) { std::print("{} ", n); }
        );

        std::println();
    }

    void generate_03()
    {
        std::vector<int> values(10);

        std::for_each(
            values.begin(),
            values.end(),
            [count = 1] (auto& n) mutable { n = count; count++; }
        );

        std::for_each(
            values.begin(),
            values.end(),
            [](auto n) { std::print("{} ", n); }
        );

        std::println();
    }


    void generate_04()
    {
        std::vector<int> values(10);

        std::generate(
            values.begin(),
            values.end(),
            [count = 1]() mutable { return count++; }
        );

        std::for_each(
            values.begin(),
            values.end(),
            [](auto n) { std::print("{} ", n); }
        );

        std::println();
    }

    void generate_05()
    {
        constexpr std::size_t Size = 10;

        std::vector<int> values(Size);

        std::generate_n(
            values.begin(),
            Size,
            [count = 1]() mutable { return count++; }
        );

        std::for_each(
            values.begin(),
            values.end(),
            [](auto n) { std::print("{} ", n); }
        );

        std::println();
    }


    void generate_06()
    {
        constexpr std::size_t Size = 10;

        std::vector<int> values;
        values.reserve(Size);

        std::generate_n(
            std::back_inserter(values),
            Size,
            [count = 1] () mutable { return count++; }
        );

        std::for_each(
            values.begin(),
            values.end(),
            [](auto n) { std::print("{} ", n); }
        );

        std::println();
    }

    void generate_07()
    {
        std::vector<int> values(10);

        std::iota(
            values.begin(),
            values.end(),
            1
        );

        std::for_each(
            values.begin(),
            values.end(),
            [](auto n) { std::print("{} ", n); }
        );

        std::println();
    }
}

void main_generate()
{
    generate_01();
    generate_02();
    generate_03();
    generate_04();
    generate_05();
    generate_06();
    generate_07();
}

// =====================================================================================
// End-of-File
// =====================================================================================


