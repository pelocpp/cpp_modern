// =====================================================================================
// Algorithms.cpp // std::fill, std::for_each, std::generate and more ...
// =====================================================================================

module;

#include <span>     // module implementation too unstable

module modern_cpp:algorithms;

import std;
import scoped_timer;

namespace {

    // =================================================================================
    // Global constants and types
    // =================================================================================

#ifdef _DEBUG
    static constexpr std::size_t VectorSize = 10'000'000;         // debug
    static constexpr std::size_t ArraySize = 10'000'000;          // debug
#else
    static constexpr std::size_t VectorSize = 100'000'000;        // release
    static constexpr std::size_t ArraySize = 50'000'000;          // release
#endif

    // need array in global data space, stack isn't suited for large objects
    std::array<double, ArraySize> values;
    std::array<double, ArraySize> source;
    std::array<double, ArraySize> target;
}

namespace {

    // =============================================================================
    // Initialization of std::vector with a constant value
    // =============================================================================

    void vector_constant_initialize_classic_for_loop()
    {
        std::println("std::vector: using a classic for-loop");

        std::vector<double> values(VectorSize);

        ScopedTimer watch;

        for (std::size_t i{}; i != values.size(); ++i) {
            values[i] = 123.0;
        }
    }

    void vector_constant_initialize_iterator_based()
    {
        std::println("std::vector: using an iterator-based for-loop");

        std::vector<double> values(VectorSize);

        ScopedTimer watch;

        for (auto it{ values.begin() }; it != values.end(); ++it) {
            *it = 123.0;
        }
    }

    void vector_constant_initialize_std_fill()
    {
        std::println("std::vector: using std::fill");

        std::vector<double> values(VectorSize);

        ScopedTimer watch;

        std::fill(
            values.begin(),
            values.end(),
            123.0
        );
    }

    void vector_constant_initialize_std_fill_parallelized()
    {
        std::println("std::vector: using std::fill - using execution policy ");

        std::vector<double> values(VectorSize);

        ScopedTimer watch;

        std::fill(
            std::execution::par,
            values.begin(),
            values.end(),
            123.0
        );
    }

    void vector_constant_initialize_std_for_each()
    {
        std::println("std::vector: using std::for_each");

        std::vector<double> values(VectorSize);

        ScopedTimer watch;

        std::for_each(
            values.begin(),
            values.end(),
            [](auto& elem) { elem = 123.0; }
        );
    }

    void vector_constant_initialize_range_based_for_loop()
    {
        std::println("std::vector: using range-based for loop");

        std::vector<double> values(VectorSize);

        ScopedTimer watch;

        for (auto& elem : values) {
            elem = 123.0;
        }
    }

    void vector_constant_initialize_std_generate()
    {
        std::println("std::vector: using std::generate");

        std::vector<double> values(VectorSize);

        ScopedTimer watch;

        std::generate(
            values.begin(),
            values.end(),
            []() { return 123.0; }
        );
    }

    void vector_constant_initialize_user_defined_ctor()
    {
        std::println("std::vector: using special std::vector c'tor (Note: time includes initialization of std::vector!)");

        ScopedTimer watch;

        std::vector<double> values(VectorSize, 123.0);
    }

    void algorithms_vector_constant_initialization()
    {
        vector_constant_initialize_classic_for_loop();
        vector_constant_initialize_iterator_based();
        vector_constant_initialize_std_fill();
        vector_constant_initialize_std_fill_parallelized();
        vector_constant_initialize_std_for_each();
        vector_constant_initialize_range_based_for_loop();
        vector_constant_initialize_std_generate();
        vector_constant_initialize_user_defined_ctor();
    }

    // =============================================================================
    // Initialization of std::array with a constant value
    // =============================================================================

    void array_constant_initialize_classic_for_loop()
    {
        std::println("std::array: using a classic for-loop");

        ScopedTimer watch;

        for (std::size_t i{}; i != values.size(); ++i) {
            values[i] = 123.0;
        }
    }

    void array_constant_initialize_iterator_based()
    {
        std::println("std::array: using an iterator-based for-loop");

        ScopedTimer watch;

        for (auto it{ values.begin() }; it != values.end(); ++it) {
            *it = 123.0;
        }
    }

    void array_constant_initialize_std_fill()
    {
        std::println("std::array: using std::fill");

        ScopedTimer watch;

        std::fill(
            values.begin(),
            values.end(),
            123.0
        );
    }

    void array_constant_initialize_std_fill_parallelized()
    {
        std::println("std::array: using std::fill - using execution policy ");

        ScopedTimer watch;

        std::fill(
            std::execution::par,
            values.begin(),
            values.end(),
            123.0
        );
    }

    void array_constant_initialize_std_for_each()
    {
        std::println("std::array: using std::for_each");

        ScopedTimer watch;

        std::for_each(
            values.begin(),
            values.end(),
            [](auto& elem) { elem = 123.0; }
        );
    }

    void array_constant_initialize_range_based_for_loop()
    {
        std::println("std::array: using range-based for loop");

        ScopedTimer watch;

        for (auto& elem : values) {
            elem = 123.0;
        }
    }

    void array_constant_initialize_std_generate()
    {
        std::println("std::array: using std::generate");

        ScopedTimer watch;

        std::generate(
            values.begin(),
            values.end(),
            []() { return 123.0; }
        );
    }

    void algorithms_array_constant_initialization()
    {
        array_constant_initialize_classic_for_loop();
        array_constant_initialize_iterator_based();
        array_constant_initialize_std_fill();
        array_constant_initialize_std_fill_parallelized();
        array_constant_initialize_std_for_each();
        array_constant_initialize_range_based_for_loop();
        array_constant_initialize_std_generate();
    }

    // =================================================================================
    // Initialization of std::vector with a varying value
    // =================================================================================

    void vector_varying_initialize_classic_for_loop()
    {
        std::println("std::vector: using a classic for-loop");

        std::vector<double> values(VectorSize);

        ScopedTimer watch;

        for (std::size_t i{}; i != values.size(); ++i) {
            values[i] = 2.0 * i;
        }
    }

    void vector_varying_initialize_iterator_based()
    {
        std::println("std::vector: using an iterator-based for-loop");

        std::vector<double> values(VectorSize);

        ScopedTimer watch;

        std::size_t i{};
        for (auto it{ values.begin() }; it != values.end(); ++it) {
            *it = 2.0 * i++;
        }
    }

    void vector_varying_initialize_std_for_each()
    {
        std::println("std::vector: using std::for_each");

        std::vector<double> values(VectorSize);

        ScopedTimer watch;

        std::for_each(
            values.begin(),
            values.end(),
            [i = 0.0](auto& elem) mutable { elem = 2.0 * i++; }
        );
    }

    void vector_varying_initialize_range_based_for_loop()
    {
        std::println("std::vector: using range-based for loop");

        std::vector<double> values(VectorSize);

        ScopedTimer watch;

        for (int i{}; auto & elem : values) {
            elem = 2.0 * i++;
        }
    }

    void vector_varying_initialize_std_for_generate()
    {
        std::println("std::vector: using std::generate");

        std::vector<double> values(VectorSize);

        ScopedTimer watch;

        std::generate(
            values.begin(),
            values.end(),
            [i = 0.0]() mutable { return 2.0 * i++; }
        );
    }

    void algorithms_vector_varying_initialization()
    {
        vector_varying_initialize_classic_for_loop();
        vector_varying_initialize_iterator_based();
        vector_varying_initialize_std_for_each();
        vector_varying_initialize_range_based_for_loop();
        vector_varying_initialize_std_for_generate();
    }

    // =================================================================================
    // Initialization of std::array with a varying value
    // =================================================================================

    void array_varying_initialize_classic_for_loop()
    {
        std::println("std::array: using a classic for-loop");

        ScopedTimer watch;

        for (std::size_t i{}; i != values.size(); ++i) {
            values[i] = 2.0 * i;
        }
    }

    void array_varying_initialize_iterator_based()
    {
        std::println("std::array: using an iterator-based for-loop");

        ScopedTimer watch;

        std::size_t i{};
        for (auto it{ values.begin() }; it != values.end(); ++it) {
            *it = 2.0 * i++;
        }
    }

    void array_varying_initialize_std_for_each()
    {
        std::println("std::array: using std::for_each");

        ScopedTimer watch;

        std::for_each(
            values.begin(),
            values.end(),
            [i = 0.0](auto& elem) mutable { elem = 2.0 * i++; }
        );
    }

    void array_varying_initialize_range_based_for_loop()
    {
        std::println("std::array: using range-based for loop");

        ScopedTimer watch;

        for (int i{}; auto & elem : values) {
            elem = 2.0 * i++;
        }
    }

    void array_varying_initialize_std_for_generate()
    {
        std::println("std::array: using std::generate");

        ScopedTimer watch;

        std::generate(
            values.begin(),
            values.end(),
            [i = 0.0]() mutable { return 2.0 * i++; }
        );
    }

    void algorithms_array_varying_initialization()
    {
        array_varying_initialize_classic_for_loop();
        array_varying_initialize_iterator_based();
        array_varying_initialize_std_for_each();
        array_varying_initialize_range_based_for_loop();
        array_varying_initialize_std_for_generate();
    }

    // =================================================================================
    // Using algorithms for copying ranges (std::vector)
    // =================================================================================

    void vector_copying_classic_for_loop()
    {
        std::println("std::vector: Copying: Using a classic for-loop");

        std::vector<double> source(VectorSize, 123.0);
        std::vector<double> target(VectorSize);

        ScopedTimer watch;

        for (std::size_t i{}; i != source.size(); ++i) {
            target[i] = source[i];
        }
    }

    void vector_copying_iterator_based()
    {
        std::println("std::vector: Copying: Using an iterator-based for-loop");

        std::vector<double> source(VectorSize, 123.0);
        std::vector<double> target(VectorSize);

        ScopedTimer watch;

        auto itTarget{ target.begin() };
        for (auto it{ source.begin() }; it != source.end(); ++it) {
            *itTarget = *it;
            ++itTarget;
        }
    }

    void vector_copying_std_copy()
    {
        std::println("std::vector: Standard Algorithm - std::copy:");

        std::vector<double> source(VectorSize, 123.0);
        std::vector<double> target(VectorSize);

        ScopedTimer watch;

        std::copy(
            source.begin(),
            source.end(),
            target.begin()
        );
    }

    void vector_copying_std_copy_parallelized()
    {
        std::println("std::vector: Using std::copy - using execution policy");

        std::vector<double> source(VectorSize, 123.0);
        std::vector<double> target(VectorSize);

        ScopedTimer watch;

        std::copy(
            std::execution::par,
            source.begin(),
            source.end(),
            target.begin()
        );
    }

    void vector_copying_std_memcpy()
    {
        std::println("std::vector: Using std::memcpy");

        std::vector<double> source(VectorSize, 123.0);
        std::vector<double> target(VectorSize);

        ScopedTimer watch;

        // take care: works only with continuous memory
        std::memcpy(
            target.data(),
            source.data(),
            VectorSize * sizeof(double)
        );
    }

    void algorithms_vector_copying()
    {
        vector_copying_classic_for_loop();
        vector_copying_iterator_based();
        vector_copying_std_copy();
        vector_copying_std_copy_parallelized();
        vector_copying_std_memcpy();
    }

    // =================================================================================
    // Using algorithms for copying ranges (std::array)
    // =================================================================================

    void array_copying_classic_for_loop()
    {
        std::println("std::array: Copying: Using a classic for-loop");

        ScopedTimer watch;

        for (std::size_t i{}; i != source.size(); ++i) {
            target[i] = source[i];
        }
    }

    void array_copying_iterator_based()
    {
        std::println("std::array: Copying: Using an iterator-based for-loop");

        ScopedTimer watch;

        auto itTarget{ target.begin() };
        for (auto it{ source.begin() }; it != source.end(); ++it) {
            *itTarget = *it;
            ++itTarget;
        }
    }

    void array_copying_std_copy()
    {
        std::println("std::array: Standard Algorithm - std::copy:");

        ScopedTimer watch;

        std::copy(
            source.begin(),
            source.end(),
            target.begin()
        );
    }

    void array_copying_std_copy_parallelized()
    {
        std::println("std::array: Using std::copy - using execution policy");

        ScopedTimer watch;

        std::copy(
            std::execution::par,
            source.begin(),
            source.end(),
            target.begin()
        );
    }

    void array_copying_std_memcpy()
    {
        std::println("std::array: Using std::memcpy");

        ScopedTimer watch;

        // take care: works only with continuous memory
        std::memcpy(
            target.data(),
            source.data(),
            ArraySize * sizeof(double)
        );
    }

    void algorithms_array_copying()
    {
        array_copying_classic_for_loop();
        array_copying_iterator_based();
        array_copying_std_copy();
        array_copying_std_copy_parallelized();
        array_copying_std_memcpy();
    }

    // =================================================================================
    // Using algorithms for elementary calculations both suited for std::vector or std::array
    // =================================================================================

    auto calculate_sum_classic_for_loop(std::span<const double> values)
    {
        std::println("Classic Loop: ");

        ScopedTimer watch;

        double sum{};
        for (std::size_t i{}; i != values.size(); ++i) {
            sum += values[i];
        }

        return sum;
    }

    auto calculate_sum_iterator_based(std::span<const double> values)
    {
        std::println("Iterator Loop: ");

        ScopedTimer watch;

        double sum{};
        for (auto it{ values.cbegin() }; it != values.cend(); ++it) {
            sum += *it;
        }

        return sum;
    }

    auto calculate_sum_range_based_for_loop(std::span<const double> values)
    {
        std::println("Using range-based for loop");

        ScopedTimer watch;

        double sum{};
        for (const auto& value : values) {
            sum += value;
        }

        return sum;
    }

    auto calculate_sum_std_for_each(std::span<const double> values)
    {
        std::println("Standard Algorithm - std::for_each:");

        ScopedTimer watch;

        double sum{};
        std::for_each(
            values.cbegin(),
            values.cend(),
            [&sum](const auto& value) {sum += value; }
        );

        return sum;
    }

    auto calculate_sum_std_accumulate(std::span<const double> values)
    {
        std::println("Standard Algorithm - std::accumulate:");

        ScopedTimer watch;

        double sum{
            std::accumulate(
                values.cbegin(),
                values.cend(),
                0.0
            )
        };

        return sum;
    }

    // =================================================================================
    // Using algorithms for elementary calculations suited for std::vector
    // =================================================================================

    void algorithms_vector_sum_calculation()
    {
        std::vector<double> values(VectorSize);

        auto initArray = [&] {
            std::generate(
                values.begin(),
                values.end(),
                [value = 0.0]() mutable { return ++value; }
            );
            };

        double sum{};

        initArray();
        sum = calculate_sum_classic_for_loop(std::span{ values });
        std::println("std::vector: Sum: {:15.20g}", sum);

        initArray();
        sum = calculate_sum_iterator_based(std::span{ values });
        std::println("std::vector: Sum: {:15.20g}", sum);

        initArray();
        sum = calculate_sum_range_based_for_loop(std::span{ values });
        std::println("std::vector: Sum: {:15.20g}", sum);

        initArray();
        sum = calculate_sum_std_for_each(std::span{ values });
        std::println("std::vector: Sum: {:15.20g}", sum);

        initArray();
        sum = calculate_sum_std_accumulate(std::span{ values });
        std::println("std::vector: Sum: {:15.20g}", sum);
    }

    // =================================================================================
    // Using algorithms for elementary calculations suited for std::vector
    // =================================================================================

    void algorithms_array_sum_calculation()
    {
        auto initArray = [&] {
            std::generate(
                values.begin(),
                values.end(),
                [value = 0.0]() mutable { return ++value; }
            );
            };

        double sum{};

        initArray();
        sum = calculate_sum_classic_for_loop(std::span{ values });
        std::println("std::array: Sum: {:15.20g}", sum);

        initArray();
        sum = calculate_sum_iterator_based(std::span{ values });
        std::println("std::array: Sum: {:15.20g}", sum);

        initArray();
        sum = calculate_sum_range_based_for_loop(std::span{ values });
        std::println("std::array: Sum: {:15.20g}", sum);

        initArray();
        sum = calculate_sum_std_for_each(std::span{ values });
        std::println("std::array: Sum: {:15.20g}", sum);

        initArray();
        sum = calculate_sum_std_accumulate(std::span{ values });
        std::println("std::array: Sum: {:15.20g}", sum);
    }
}

void main_algorithms()
{
    // initialization of std::vector or std::array with a constant value
    algorithms_vector_constant_initialization();
    algorithms_array_constant_initialization();

    // initialization of std::vector or std::array with a a varying value
    algorithms_vector_varying_initialization();
    algorithms_array_varying_initialization();

    // using algorithms for copying ranges (std::vector or std::array)
    algorithms_vector_copying();
    algorithms_array_copying();

    // using algorithms for elementary calculations (std::vector or std::array)
    algorithms_vector_sum_calculation();
    algorithms_array_sum_calculation();
}

// =====================================================================================
// End-of-File
// =====================================================================================
