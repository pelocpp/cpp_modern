// =====================================================================================
// Algorithms.cpp // std::fill, std::for_each, std::generate, std::accumulate
// =====================================================================================

module;

#include "../ScopedTimer/ScopedTimer.h"

module modern_cpp:algorithms;

namespace Algorithms {

    //static constexpr int MaxIterations = 100'000'000;  // release
    static constexpr int MaxIterations = 10'000'000;     // debug

    static std::vector<double> values(MaxIterations);

    // =================================================================================
    // Initialization with a constant value
    // =================================================================================

    static auto test_constant_initialize_classic_loop ()
    {
        std::println("Using a classic for-loop");

        ScopedTimer watch{};

        for (size_t i{}; i != values.size(); ++i) {
            values[i] = 123.0;
        }
    }

    static auto test_constant_initialize_iterator_based()
    {
        std::println("Using an iterator-based for-loop");

        ScopedTimer watch{};

        for (auto it{ values.begin() }; it != values.end(); ++it) {
            *it = 123.0;
        }
    }

    static auto test_constant_initialize_std_fill()
    {
        std::println("Using std::fill");

        ScopedTimer watch{};

        std::fill(
            values.begin(),
            values.end(),
            123.0
        );
    }

    static auto test_constant_initialize_std_for_each()
    {
        std::println("Using std::for_each");

        ScopedTimer watch{};

        std::for_each(
            values.begin(),
            values.end(),
            [](auto& elem) { elem = 123.0; }
        );
    }

    static auto test_constant_initialize_std_generate()
    {
        std::println("Using std::generate");

        ScopedTimer watch{};

        std::generate(
            values.begin(),
            values.end(),
            [] { return 123.0; }
        );
    }

    static void test_const_initialization()
    {
        test_constant_initialize_classic_loop();
        test_constant_initialize_iterator_based();
        test_constant_initialize_std_fill();
        test_constant_initialize_std_for_each();
        test_constant_initialize_std_generate();
    }

    // =================================================================================
    // Initialization with a varying value
    // =================================================================================

    static auto test_initialize_classic_loop()
    {
        std::println("Classic for-loop");

        ScopedTimer watch{};

        for (size_t i{}; i != values.size(); ++i) {
            values[i] = 2.0 * i;
        }
    }

    static auto test_initialize_iterator_based()
    {
        std::println("Iterator-based for-loop");

        ScopedTimer watch{};

        size_t i{};
        for (auto it{ values.begin() }; it != values.end(); ++it) {
            *it = 2.0 * i++;
        }
    }

    static auto test_initialize_std_for_each()
    {
        std::println("Using std::for_each");

        ScopedTimer watch{};

        std::for_each(
            values.begin(),
            values.end(),
            [i = 0.0] (auto& elem) mutable { elem = 2.0 * i++; }
        );
    }

    static auto test_initialize_std_for_generate()
    {
        std::println("Using std::generate");

        ScopedTimer watch{};

        std::generate(
            values.begin(),
            values.end(),
            [i = 0.0]() mutable { return 2.0 * i++; }
        );
    }

    static void test_initialization()
    {
        test_initialize_classic_loop();
        test_initialize_iterator_based();
        test_initialize_std_for_each();
        test_initialize_std_for_generate();
    }

    // =================================================================================
    // Using algorithms for elementary calculations
    // =================================================================================

    static auto test_calculate_sum_classic()
    {
        std::println("Classic Loop: ");

        double sum{};

        ScopedTimer watch{};

        for (size_t i{}; i != values.size(); ++i) {
            sum += values[i];
        }

        return sum;
    }

    static auto test_calculate_sum_iterator()
    {
        std::println("Iterator Loop: ");

        double sum{};

        ScopedTimer watch{};

        for (auto it{ values.cbegin() }; it != values.cend(); ++it) {
            sum += *it;
        }

        return sum;
    }

    static auto test_calculate_sum_range_based_loop()
    {
        std::println("Range-based Loop: ");

        double sum{};

        ScopedTimer watch{};

        for (const auto& value : values) {
            sum += value;
        }

        return sum;
    }

    static auto test_calculate_sum_standard_algorithm()
    {
        std::println("Standard Algorithm - std::for_each:");

        double sum{};

        ScopedTimer watch{};

        std::for_each(
            values.cbegin(),
            values.cend(),
            [&sum](const auto& value) {sum += value; }
        );

        return sum;
    }

    static auto test_calculate_sum_accumulate()
    {
        std::println("Standard Algorithm - std::accumulate:");

        ScopedTimer watch{};

        double sum {
            std::accumulate(
                values.cbegin(),
                values.cend(),
                0.0
            )
        };

        return sum;
    }

    static void test_sum_calculation()
    {
        auto initArray = [] {
            std::generate(
                values.begin(),
                values.end(),
                [value = 0.0] () mutable { return ++value; }
            );
        };

        double sum{};

        initArray();
        sum = test_calculate_sum_classic();
        std::println("Sum: {:15.20g}", sum);

        initArray();
        sum = test_calculate_sum_iterator();
        std::println("Sum: {:15.20g}", sum);

        initArray();
        sum = test_calculate_sum_range_based_loop();
        std::println("Sum: {:15.20g}", sum);

        initArray();
        sum = test_calculate_sum_standard_algorithm();
        std::println("Sum: {:15.20g}", sum);

        initArray();
        sum = test_calculate_sum_accumulate();
        std::println("Sum: {:15.20g}", sum);
    }
}

void main_algorithms()
{
    using namespace Algorithms;
    test_const_initialization();
    test_initialization();
    test_sum_calculation();
}

// =====================================================================================
// End-of-File
// =====================================================================================
