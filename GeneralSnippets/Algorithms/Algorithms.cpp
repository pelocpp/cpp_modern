// =====================================================================================
// Algorithms.cpp // std::fill, std::for_each, std::generate and more ...
// =====================================================================================

module;

#include "../ScopedTimer/ScopedTimer.h"

module modern_cpp:algorithms;

namespace Algorithms {

    // =================================================================================
    // Global constants and types
    // =================================================================================

#ifdef _DEBUG
    static constexpr int VectorSize = 10'000'000;         // debug
    static constexpr int ArraySize = 10'000'000;          // debug
#else
    static constexpr int VectorSize = 100'000'000;        // release
    static constexpr int ArraySize = 50'000'000;          // release
#endif

    // need array in global data space, stack isn't suited for large objects
    std::array<double, ArraySize> values;
    std::array<double, ArraySize> source;
    std::array<double, ArraySize> target;
}

namespace Algorithms {

    namespace Initialization_Vector_Constant_Value {

        // =============================================================================
        // Initialization of std::vector with a constant value
        // =============================================================================

        static auto test_vector_constant_initialize_classic_for_loop()
        {
            std::println("std::vector: using a classic for-loop");

            std::vector<double> values(VectorSize);

            ScopedTimer watch{};

            for (size_t i{}; i != values.size(); ++i) {
                values[i] = 123.0;
            }
        }

        static auto test_vector_constant_initialize_iterator_based()
        {
            std::println("std::vector: using an iterator-based for-loop");

            std::vector<double> values(VectorSize);

            ScopedTimer watch{};

            for (auto it{ values.begin() }; it != values.end(); ++it) {
                *it = 123.0;
            }
        }

        static auto test_vector_constant_initialize_std_fill()
        {
            std::println("std::vector: using std::fill");

            std::vector<double> values(VectorSize);

            ScopedTimer watch{};

            std::fill(
                values.begin(),
                values.end(),
                123.0
            );
        }

        static auto test_vector_constant_initialize_std_fill_parallelized()
        {
            std::println("std::vector: using std::fill - using execution policy ");

            std::vector<double> values(VectorSize);

            ScopedTimer watch{};

            std::fill(
                std::execution::par,
                values.begin(),
                values.end(),
                123.0
            );
        }

        static auto test_vector_constant_initialize_std_for_each()
        {
            std::println("std::vector: using std::for_each");

            std::vector<double> values(VectorSize);

            ScopedTimer watch{};

            std::for_each(
                values.begin(),
                values.end(),
                [](auto& elem) { elem = 123.0; }
            );
        }

        static auto test_vector_constant_initialize_range_based_for_loop()
        {
            std::println("std::vector: using range-based for loop");

            std::vector<double> values(VectorSize);

            ScopedTimer watch{};

            for (auto& elem : values) {
                elem = 123.0;
            }
        }

        static auto test_vector_constant_initialize_std_generate()
        {
            std::println("std::vector: using std::generate");

            std::vector<double> values(VectorSize);

            ScopedTimer watch{};

            std::generate(
                values.begin(),
                values.end(),
                []() { return 123.0; }
            );
        }

        static auto test_vector_constant_initialize_user_defined_ctor()
        {
            std::println("std::vector: using special std::vector c'tor (Note: time includes initialization of std::vector!)");

            ScopedTimer watch{};

            std::vector<double> values(VectorSize, 123.0);
        }

        static void test_vector_constant_initialization()
        {
            test_vector_constant_initialize_classic_for_loop();
            test_vector_constant_initialize_iterator_based();
            test_vector_constant_initialize_std_fill();
            test_vector_constant_initialize_std_fill_parallelized();
            test_vector_constant_initialize_std_for_each();
            test_vector_constant_initialize_range_based_for_loop();
            test_vector_constant_initialize_std_generate();
            test_vector_constant_initialize_user_defined_ctor();
        }
    }
}

namespace Algorithms {

    namespace Initialization_Array_Constant_Value {

        // =============================================================================
        // Initialization of std::array with a constant value
        // =============================================================================

        static auto test_array_constant_initialize_classic_for_loop()
        {
            std::println("std::array: using a classic for-loop");

            ScopedTimer watch{};

            for (size_t i{}; i != values.size(); ++i) {
                values[i] = 123.0;
            }
        }

        static auto test_array_constant_initialize_iterator_based()
        {
            std::println("std::array: using an iterator-based for-loop");

            ScopedTimer watch{};

            for (auto it{ values.begin() }; it != values.end(); ++it) {
                *it = 123.0;
            }
        }

        static auto test_array_constant_initialize_std_fill()
        {
            std::println("std::array: using std::fill");

            ScopedTimer watch{};

            std::fill(
                values.begin(),
                values.end(),
                123.0
            );
        }

        static auto test_array_constant_initialize_std_fill_parallelized()
        {
            std::println("std::array: using std::fill - using execution policy ");

            ScopedTimer watch{};

            std::fill(
                std::execution::par,
                values.begin(),
                values.end(),
                123.0
            );
        }

        static auto test_array_constant_initialize_std_for_each()
        {
            std::println("std::array: using std::for_each");

            ScopedTimer watch{};

            std::for_each(
                values.begin(),
                values.end(),
                [](auto& elem) { elem = 123.0; }
            );
        }

        static auto test_array_constant_initialize_range_based_for_loop()
        {
            std::println("std::array: using range-based for loop");

            ScopedTimer watch{};

            for (auto& elem : values) {
                elem = 123.0;
            }
        }

        static auto test_array_constant_initialize_std_generate()
        {
            std::println("std::array: using std::generate");

            ScopedTimer watch{};

            std::generate(
                values.begin(),
                values.end(),
                []() { return 123.0; }
            );
        }

        static void test_array_constant_initialization()
        {
            test_array_constant_initialize_classic_for_loop();
            test_array_constant_initialize_iterator_based();
            test_array_constant_initialize_std_fill();
            test_array_constant_initialize_std_fill_parallelized();
            test_array_constant_initialize_std_for_each();
            test_array_constant_initialize_range_based_for_loop();
            test_array_constant_initialize_std_generate();
        }
    }
}

namespace Algorithms {

    namespace Initialization_Vector_Varying_Value {

        // =================================================================================
        // Initialization of std::vector with a varying value
        // =================================================================================

        static auto test_vector_varying_initialize_classic_for_loop()
        {
            std::println("std::vector: using a classic for-loop");

            std::vector<double> values(VectorSize);

            ScopedTimer watch{};

            for (size_t i{}; i != values.size(); ++i) {
                values[i] = 2.0 * i;
            }
        }

        static auto test_vector_varying_initialize_iterator_based()
        {
            std::println("std::vector: using an iterator-based for-loop");

            std::vector<double> values(VectorSize);

            ScopedTimer watch{};

            size_t i{};
            for (auto it{ values.begin() }; it != values.end(); ++it) {
                *it = 2.0 * i++;
            }
        }

        static auto test_vector_varying_initialize_std_for_each()
        {
            std::println("std::vector: using std::for_each");

            std::vector<double> values(VectorSize);

            ScopedTimer watch{};

            std::for_each(
                values.begin(),
                values.end(),
                [i = 0.0](auto& elem) mutable { elem = 2.0 * i++; }
            );
        }

        static auto test_vector_varying_initialize_range_based_for_loop()
        {
            std::println("std::vector: using range-based for loop");

            std::vector<double> values(VectorSize);

            ScopedTimer watch{};

            for (int i{}; auto & elem : values) {
                elem = 2.0 * i++;
            }
        }

        static auto test_vector_varying_initialize_std_for_generate()
        {
            std::println("std::vector: using std::generate");

            std::vector<double> values(VectorSize);

            ScopedTimer watch{};

            std::generate(
                values.begin(),
                values.end(),
                [i = 0.0]() mutable { return 2.0 * i++; }
            );
        }

        static void test_vector_varying_initialization()
        {
            test_vector_varying_initialize_classic_for_loop();
            test_vector_varying_initialize_iterator_based();
            test_vector_varying_initialize_std_for_each();
            test_vector_varying_initialize_range_based_for_loop();
            test_vector_varying_initialize_std_for_generate();
        }
    }
}

namespace Algorithms {

    namespace Initialization_Array_Varying_Value {

        // =================================================================================
        // Initialization of std::array with a varying value
        // =================================================================================

        static auto test_array_varying_initialize_classic_for_loop()
        {
            std::println("std::array: using a classic for-loop");

            ScopedTimer watch{};

            for (size_t i{}; i != values.size(); ++i) {
                values[i] = 2.0 * i;
            }
        }

        static auto test_array_varying_initialize_iterator_based()
        {
            std::println("std::array: using an iterator-based for-loop");

            ScopedTimer watch{};

            size_t i{};
            for (auto it{ values.begin() }; it != values.end(); ++it) {
                *it = 2.0 * i++;
            }
        }

        static auto test_array_varying_initialize_std_for_each()
        {
            std::println("std::array: using std::for_each");

            ScopedTimer watch{};

            std::for_each(
                values.begin(),
                values.end(),
                [i = 0.0](auto& elem) mutable { elem = 2.0 * i++; }
            );
        }

        static auto test_array_varying_initialize_range_based_for_loop()
        {
            std::println("std::array: using range-based for loop");

            ScopedTimer watch{};

            for (int i{}; auto & elem : values) {
                elem = 2.0 * i++;
            }
        }

        static auto test_array_varying_initialize_std_for_generate()
        {
            std::println("std::array: using std::generate");

            ScopedTimer watch{};

            std::generate(
                values.begin(),
                values.end(),
                [i = 0.0]() mutable { return 2.0 * i++; }
            );
        }

        static void test_array_varying_initialization()
        {
            using namespace Initialization_Array_Varying_Value;

            test_array_varying_initialize_classic_for_loop();
            test_array_varying_initialize_iterator_based();
            test_array_varying_initialize_std_for_each();
            test_array_varying_initialize_range_based_for_loop();
            test_array_varying_initialize_std_for_generate();
        }
    }
}

namespace Algorithms {

    // =================================================================================
    // Using algorithms for copying ranges (std::vector)
    // =================================================================================

    namespace Copying_Vectors {
    
        static auto test_vector_copying_classic_for_loop()
        {
            std::println("std::vector: Copying: Using a classic for-loop");

            std::vector<double> source(VectorSize, 123.0);
            std::vector<double> target(VectorSize);

            ScopedTimer watch{};

            for (size_t i{}; i != source.size(); ++i) {
                target[i] = source[i];
            }
        }

        static auto test_vector_copying_iterator_based()
        {
            std::println("std::vector: Copying: Using an iterator-based for-loop");

            std::vector<double> source(VectorSize, 123.0);
            std::vector<double> target(VectorSize);

            ScopedTimer watch{};

            auto itTarget{ target.begin() };
            for (auto it{ source.begin() }; it != source.end(); ++it) {
                *itTarget = *it;
                ++itTarget;
            }
        }

        static auto test_vector_copying_std_copy()
        {
            std::println("std::vector: Standard Algorithm - std::copy:");

            std::vector<double> source(VectorSize, 123.0);
            std::vector<double> target(VectorSize);

            ScopedTimer watch{};

            std::copy(
                source.begin(),
                source.end(),
                target.begin()
            );
        }

        static auto test_vector_copying_std_copy_parallelized()
        {
            std::println("std::vector: Using std::copy - using execution policy");

            std::vector<double> source(VectorSize, 123.0);
            std::vector<double> target(VectorSize);

            ScopedTimer watch{};

            std::copy(
                std::execution::par,
                source.begin(),
                source.end(),
                target.begin()
            );
        }

        static auto test_vector_copying_std_memcpy()
        {
            std::println("std::vector: Using std::memcpy");

            std::vector<double> source(VectorSize, 123.0);
            std::vector<double> target(VectorSize);

            ScopedTimer watch{};

            // take care: works only with continuous memory
            std::memcpy(
                target.data(),
                source.data(),
                VectorSize * sizeof(double)
            );
        }

        static void test_vector_copying()
        {
            test_vector_copying_classic_for_loop();
            test_vector_copying_iterator_based();
            test_vector_copying_std_copy();
            test_vector_copying_std_copy_parallelized();
            test_vector_copying_std_memcpy();
        }
    }
}

namespace Algorithms {

    // =================================================================================
    // Using algorithms for copying ranges (std::array)
    // =================================================================================

    namespace Copying_Arrays {

        static auto test_array_copying_classic_for_loop()
        {
            std::println("std::array: Copying: Using a classic for-loop");

            ScopedTimer watch{};

            for (size_t i{}; i != source.size(); ++i) {
                target[i] = source[i];
            }
        }

        static auto test_array_copying_iterator_based()
        {
            std::println("std::array: Copying: Using an iterator-based for-loop");

            ScopedTimer watch{};

            auto itTarget{ target.begin() };
            for (auto it{ source.begin() }; it != source.end(); ++it) {
                *itTarget = *it;
                ++itTarget;
            }
        }

        static auto test_array_copying_std_copy()
        {
            std::println("std::array: Standard Algorithm - std::copy:");

            ScopedTimer watch{};

            std::copy(
                source.begin(),
                source.end(),
                target.begin()
            );
        }

        static auto test_array_copying_std_copy_parallelized()
        {
            std::println("std::array: Using std::copy - using execution policy");

            ScopedTimer watch{};

            std::copy(
                std::execution::par,
                source.begin(),
                source.end(),
                target.begin()
            );
        }

        static auto test_array_copying_std_memcpy()
        {
            std::println("std::array: Using std::memcpy");

            ScopedTimer watch{};

            // take care: works only with continuous memory
            std::memcpy(
                target.data(),
                source.data(),
                ArraySize * sizeof(double)
            );
        }

        static void test_array_copying()
        {
            test_array_copying_classic_for_loop();
            test_array_copying_iterator_based();
            test_array_copying_std_copy();
            test_array_copying_std_copy_parallelized();
            test_array_copying_std_memcpy();
        }
    }
}

namespace Algorithms {

    namespace Elementary_Calculations {

        // =================================================================================
        // Using algorithms for elementary calculations both suited for std::vector or std::array
        // =================================================================================

        static auto test_calculate_sum_classic_for_loop(std::span<const double> values)
        {
            std::println("Classic Loop: ");

            ScopedTimer watch{};

            double sum{};
            for (size_t i{}; i != values.size(); ++i) {
                sum += values[i];
            }

            return sum;
        }

        static auto test_calculate_sum_iterator_based(std::span<const double> values)
        {
            std::println("Iterator Loop: ");

            ScopedTimer watch{};

            double sum{};
            for (auto it{ values.cbegin() }; it != values.cend(); ++it) {
                sum += *it;
            }

            return sum;
        }

        static auto test_calculate_sum_range_based_for_loop(std::span<const double> values)
        {
            std::println("Using range-based for loop");

            ScopedTimer watch{};

            double sum{};
            for (const auto& value : values) {
                sum += value;
            }

            return sum;
        }

        static auto test_calculate_sum_std_for_each(std::span<const double> values)
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

        static auto test_calculate_sum_std_accumulate(std::span<const double> values)
        {
            std::println("Standard Algorithm - std::accumulate:");

            ScopedTimer watch{};

            double sum{
                std::accumulate(
                    values.cbegin(),
                    values.cend(),
                    0.0
                )
            };

            return sum;
        }
    }
}

namespace Algorithms {

    namespace Elementary_Calculations_With_Vectors {

        static void test_vector_sum_calculation()
        {
            using namespace Elementary_Calculations;

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
            sum = test_calculate_sum_classic_for_loop(std::span{ values });
            std::println("std::vector: Sum: {:15.20g}", sum);

            initArray();
            sum = test_calculate_sum_iterator_based(std::span{ values });
            std::println("std::vector: Sum: {:15.20g}", sum);

            initArray();
            sum = test_calculate_sum_range_based_for_loop(std::span{ values });
            std::println("std::vector: Sum: {:15.20g}", sum);

            initArray();
            sum = test_calculate_sum_std_for_each(std::span{ values });
            std::println("std::vector: Sum: {:15.20g}", sum);

            initArray();
            sum = test_calculate_sum_std_accumulate(std::span{ values });
            std::println("std::vector: Sum: {:15.20g}", sum);
        }
    }

    namespace Elementary_Calculations_With_Arrays {

        static void test_array_sum_calculation()
        {
            using namespace Elementary_Calculations;

            auto initArray = [&] {
                std::generate(
                    values.begin(),
                    values.end(),
                    [value = 0.0]() mutable { return ++value; }
                );
                };

            double sum{};

            initArray();
            sum = test_calculate_sum_classic_for_loop(std::span{ values });
            std::println("std::array: Sum: {:15.20g}", sum);

            initArray();
            sum = test_calculate_sum_iterator_based(std::span{ values });
            std::println("std::array: Sum: {:15.20g}", sum);

            initArray();
            sum = test_calculate_sum_range_based_for_loop(std::span{ values });
            std::println("std::array: Sum: {:15.20g}", sum);

            initArray();
            sum = test_calculate_sum_std_for_each(std::span{ values });
            std::println("std::array: Sum: {:15.20g}", sum);

            initArray();
            sum = test_calculate_sum_std_accumulate(std::span{ values });
            std::println("std::array: Sum: {:15.20g}", sum);
        }
    }
}

void main_algorithms()
{
    // initialization of std::vector or std::array with a constant value
    Algorithms::Initialization_Vector_Constant_Value::test_vector_constant_initialization();
    Algorithms::Initialization_Array_Constant_Value::test_array_constant_initialization();

    // initialization of std::vector or std::array with a a varying value
    Algorithms::Initialization_Vector_Varying_Value::test_vector_varying_initialization();
    Algorithms::Initialization_Array_Varying_Value::test_array_varying_initialization();

    // using algorithms for copying ranges (std::vector or std::array)
    Algorithms::Copying_Vectors::test_vector_copying();
    Algorithms::Copying_Arrays::test_array_copying();

    // using algorithms for elementary calculations (std::vector or std::array)
    Algorithms::Elementary_Calculations_With_Vectors::test_vector_sum_calculation();
    Algorithms::Elementary_Calculations_With_Arrays::test_array_sum_calculation();
}

// =====================================================================================
// End-of-File
// =====================================================================================
