// =====================================================================================
// Algorithms.cpp // std::fill, std::for_each, std::generate, std::accumulate
// =====================================================================================

module;

#include "../ScopedTimer/ScopedTimer.h"

module modern_cpp:algorithms;

namespace Algorithms {

    //static constexpr int Size = 100'000'000;  // release
    static constexpr int Size = 10'000'000;     // debug

    // =================================================================================
    // Initialization with a constant value
    // =================================================================================

    static auto test_constant_initialize_classic_for_loop()
    {
        std::println("Using a classic for-loop");

        ScopedTimer watch{};

        std::vector<double> values(Size);

        for (size_t i{}; i != values.size(); ++i) {
            values[i] = 123.0;
        }
    }

    static auto test_constant_initialize_iterator_based()
    {
        std::println("Using an iterator-based for-loop");

        ScopedTimer watch{};

        std::vector<double> values(Size);

        for (auto it{ values.begin() }; it != values.end(); ++it) {
            *it = 123.0;
        }
    }

    static auto test_constant_initialize_std_fill()
    {
        std::println("Using std::fill");

        ScopedTimer watch{};

        std::vector<double> values(Size);

        std::fill(
            values.begin(),
            values.end(),
            123.0
        );
    }

    static auto test_constant_initialize_std_fill_parallelized ()
    {
        std::println("Using std::fill - using execution policy ");

        ScopedTimer watch{};

        std::vector<double> values(Size);

        std::fill(
            std::execution::par,
            values.begin(),
            values.end(),
            123.0
        );
    }

    static auto test_constant_initialize_std_for_each()
    {
        std::println("Using std::for_each");

        ScopedTimer watch{};

        std::vector<double> values(Size);

        std::for_each(
            values.begin(),
            values.end(),
            [](auto& elem) { elem = 123.0; }
        );
    }

    static auto test_constant_initialize_range_based_for_loop()
    {
        std::println("Using range-based for loop");

        ScopedTimer watch{};

        std::vector<double> values(Size);

        for (auto& elem : values) {
            elem = 123.0;
        }
    }

    static auto test_constant_initialize_std_generate()
    {
        std::println("Using std::generate");

        ScopedTimer watch{};

        std::vector<double> values(Size);

        std::generate(
            values.begin(),
            values.end(),
            [] () { return 123.0; }
        );
    }

    static auto test_constant_initialize_user_defined_ctor()
    {
        std::println("Using special std::vector c'tor");

        ScopedTimer watch{};

        std::vector<double> values(Size, 123.0);
    }

    static void test_const_initialization()
    {
        test_constant_initialize_classic_for_loop();
        test_constant_initialize_iterator_based();
        test_constant_initialize_std_fill();
        test_constant_initialize_std_fill_parallelized();
        test_constant_initialize_std_for_each();
        test_constant_initialize_range_based_for_loop();
        test_constant_initialize_std_generate();
        test_constant_initialize_user_defined_ctor();
    }

    // =================================================================================
    // Initialization with a varying value
    // =================================================================================

    static auto test_initialize_classic_for_loop()
    {
        std::println("Classic for-loop");

        ScopedTimer watch{};

        std::vector<double> values(Size);

        for (size_t i{}; i != values.size(); ++i) {
            values[i] = 2.0 * i;
        }
    }

    static auto test_initialize_iterator_based()
    {
        std::println("Iterator-based for-loop");

        ScopedTimer watch{};

        std::vector<double> values(Size);

        size_t i{};
        for (auto it{ values.begin() }; it != values.end(); ++it) {
            *it = 2.0 * i++;
        }
    }

    static auto test_initialize_std_for_each()
    {
        std::println("Using std::for_each");

        ScopedTimer watch{};

        std::vector<double> values(Size);

        std::for_each(
            values.begin(),
            values.end(),
            [i = 0.0] (auto& elem) mutable { elem = 2.0 * i++; }
        );
    }

    static auto test_initialize_range_based_for_loop()
    {
        std::println("Using range-based for loop");

        ScopedTimer watch{};

        std::vector<double> values(Size);

        for (int i{}; auto& elem : values) {
            elem = 2.0 * i++;
        }
    }

    static auto test_initialize_std_for_generate()
    {
        std::println("Using std::generate");

        ScopedTimer watch{};

        std::vector<double> values(Size);

        std::generate(
            values.begin(),
            values.end(),
            [i = 0.0] () mutable { return 2.0 * i++; }
        );
    }

    static void test_initialization()
    {
        test_initialize_classic_for_loop();
        test_initialize_iterator_based();
        test_initialize_std_for_each();
        test_initialize_range_based_for_loop();
        test_initialize_std_for_generate();
    }

    // =================================================================================
    // Using algorithms for elementary calculations
    // =================================================================================

    static auto test_calculate_sum_classic_for_loop(const std::vector<double>& values)
    {
        std::println("Classic Loop: ");

        ScopedTimer watch{};

        double sum{};
        for (size_t i{}; i != values.size(); ++i) {
            sum += values[i];
        }

        return sum;
    }

    static auto test_calculate_sum_iterator_based(const std::vector<double>& values)
    {
        std::println("Iterator Loop: ");

        ScopedTimer watch{};

        double sum{};
        for (auto it{ values.cbegin() }; it != values.cend(); ++it) {
            sum += *it;
        }

        return sum;
    }

    static auto test_calculate_sum_range_based_for_loop(const std::vector<double>& values)
    {
        std::println("Using range-based for loop");

        ScopedTimer watch{};

        double sum{};
        for (const auto& value : values) {
            sum += value;
        }

        return sum;
    }

    static auto test_calculate_sum_std_for_each(const std::vector<double>& values)
    {
        std::println("Standard Algorithm - std::for_each:");

        ScopedTimer watch{};

        double sum{};
        std::for_each(
            values.cbegin(),
            values.cend(),
            [&sum](const auto& value) {sum += value; }
        );

        return sum;
    }

    static auto test_calculate_sum_std_accumulate(const std::vector<double>& values)
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
        std::vector<double> values(Size);

        auto initArray = [&] {
            std::generate(
                values.begin(),
                values.end(),
                [value = 0.0] () mutable { return ++value; }
            );
        };

        double sum{};

        initArray();
        sum = test_calculate_sum_classic_for_loop(values);
        std::println("Sum: {:15.20g}", sum);

        initArray();
        sum = test_calculate_sum_iterator_based(values);
        std::println("Sum: {:15.20g}", sum);

        initArray();
        sum = test_calculate_sum_range_based_for_loop(values);
        std::println("Sum: {:15.20g}", sum);

        initArray();
        sum = test_calculate_sum_std_for_each(values);
        std::println("Sum: {:15.20g}", sum);

        initArray();
        sum = test_calculate_sum_std_accumulate(values);
        std::println("Sum: {:15.20g}", sum);
    }

    // =================================================================================
    // Using algorithms for copying ranges
    // =================================================================================

    static auto test_copying_classic_for_loop()
    {
        std::println("Copying: Using a classic for-loop");

        ScopedTimer watch{};

        std::vector<double> source(Size, 123.0);
        std::vector<double> target(Size);

        for (size_t i{}; i != source.size(); ++i) {
            target[i] = source[i];
        }
    }

    static auto test_copying_iterator_based()
    {
        std::println("Copying: Using an iterator-based for-loop");

        ScopedTimer watch{};
        
        std::vector<double> source(Size, 123.0);
        std::vector<double> target(Size);

        auto itSource{ source.begin() };
        auto itTarget{ target.begin() };

        for (auto it{ source.begin() }; it != source.end(); ++it) {
            *itTarget = *itSource;
        }
    }

    static auto test_copying_std_copy()
    {
        std::println("Standard Algorithm - std::copy:");

        ScopedTimer watch{};

        std::vector<double> source(Size, 123.0);
        std::vector<double> target(Size);

        std::copy(
            source.begin(),
            source.end(),
            target.begin()
        );
    }

    static auto test_copying_std_copy_parallelized()
    {
        std::println("Using std::copy - using execution policy");

        ScopedTimer watch{};

        std::vector<double> source(Size, 123.0);
        std::vector<double> target(Size);

        std::copy(
            std::execution::par,
            source.begin(),
            source.end(),
            target.begin()
        );
    }

    static auto test_copying_std_memcpy()
    {
        std::println("Using std::memcpy");

        ScopedTimer watch{};

        std::vector<double> source(Size, 123.0);
        std::vector<double> target(Size);

        // take care: works only with continuous memory
        std::memcpy(
            target.data(),
            source.data(),
            Size * sizeof (double)
        );
    }

    static void test_copying()
    {
        test_copying_classic_for_loop();
        test_copying_iterator_based();
        test_copying_std_copy();
        test_copying_std_copy_parallelized();
        test_copying_std_memcpy();
    }
}

void main_algorithms()
{
    using namespace Algorithms;
    test_const_initialization();
    test_initialization();
    test_sum_calculation();
    test_copying();
}

// =====================================================================================
// End-of-File
// =====================================================================================
