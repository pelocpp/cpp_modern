// =====================================================================================
// RangeBasedForLoop.cpp
// =====================================================================================

module;

#include "../ScopedTimer/ScopedTimer.h"

module modern_cpp:range_based_for_loop;

/*
 *  12 ways to iterate through a vector 
 */

namespace RangeBasedForLoop {

    // global function
    static void processElement(int n)
    {
        std::cout << n << " ";
    }

    // functor: "callable object" - class which implements operator()
    class ElementProcessor
    {
    public:
        void operator() (int n) const { 
            std::cout << n << " ";
        }
    };

    static void test()
    {
        // container of integral data type
        std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        // =========================================================================
        // "Classic style" examples

        // a) Very, very classic style ... C-stylistic
        for (size_t i = 0; i != vec.size(); ++i) {
            std::cout << vec[i] << " ";
        }
        std::cout << std::endl;

        // b) Looks like C++, very classic style
        std::for_each(
            vec.cbegin(),                   // Iterator-object for begin of range
            vec.cend(),                     // Iterator-object for end of range
            processElement                 // function pointer
        );
        std::cout << std::endl;

        // c) Same as b), modified ranges
        std::for_each(
            std::next(vec.cbegin()),        // Iterator-object for begin of range
            std::prev(vec.cend()),          // Iterator-object for end of range
            processElement                 // function pointer
        );
        std::cout << std::endl;

        // d) Looks like C++, classic style, 'Functor'-stylistic
        std::for_each(
            vec.cbegin(),                   // Iterator-object for begin of range
            vec.cend(),                     // Iterator-object for end of range
            ElementProcessor{}             // "callable" object
        );
        std::cout << std::endl;

        // e) Using STL algorithm std::for_each with a lambda: Modern style
        std::for_each(
            vec.cbegin(),                   // Iterator-object for begin of range
            vec.cend(),                     // Iterator-object for end of range
            [](int n) {                    // anonymous method (lambda)
                std::cout << n << " ";
            }
        );
        std::cout << std::endl;

        // =========================================================================
        // Range-based 'for' Loop examples

        // f) Using Range-based 'for' Loop: Very modern style
        for (int n : vec) {
            std::cout << n << " ";
            if (n == 2)  // break is possible
                break;
        }
        std::cout << std::endl;

        // g) Same as f), using 'const int&'
        for (const int& n : vec) {
            std::cout << n << " ";
        }
        std::cout << std::endl;

        // h) Same as f): Using 'auto' keyword to cause type inference to be used
        for (auto n : vec) {
            std::cout << n << " ";
        }
        std::cout << std::endl;

        // i) Same as g), using 'const auto&': type inference by reference
        for (const auto& n : vec) {
            std::cout << n << " ";
        }
        std::cout << std::endl;

        // j) Real C++: How the compiler 'sees' a Range-based 'for' Loop
        std::vector<int>::const_iterator begin = vec.cbegin();
        std::vector<int>::const_iterator end = vec.cend();

        while (begin != end) {

            int n{ *begin };
            std::cout << n << " ";
            ++begin;
        }
        std::cout << std::endl;

        // k) Same as h), using 'auto'
        auto begin2 = vec.cbegin();
        auto end2 = vec.cend();

        while (begin2 != end2) {

            int n{ *begin2 };
            std::cout << n << " ";
            ++begin2;
        }
        std::cout << std::endl;

        // l) Range-based 'for' loop with initializer,
        // we can now use the index variable inside the for statement
        for (int index{}; int n : vec) {
            std::cout << index << ": " << n << " " << std::endl;
            ++index;
        }
    }
}

namespace RangeBasedForLoop {

    static auto calculate_sum_classic(const std::vector<double>& values) noexcept
    {
        std::println("Classic Loop: ");

        double sum{};

        ScopedTimer watch{};

        for (size_t i = 0; i != values.size(); ++i) {
            sum += values[i];
        }

        return sum;
    }

    static auto calculate_sum_iterator(const std::vector<double>& values) noexcept
    {
        std::println("Iterator Loop: ");

        double sum{};

        ScopedTimer watch{};

        for (auto it = values.cbegin(); it != values.cend(); ++it) {
            sum += *it;
        }

        return sum;
    }

    static auto calculate_sum_range_based_loop (const std::vector<double>& values) noexcept
    {
        std::println("Range-based Loop: ");

        double sum{};

        ScopedTimer watch{};

        for (const auto& value : values) {
            sum += value;
        }

        return sum;
    }

    static auto calculate_sum_standard_algorithm (const std::vector<double>& values) noexcept
    {
        std::println("Standard Algorithm - std::for_each:");

        double sum{};

        ScopedTimer watch{};

        std::for_each(
            values.cbegin(),
            values.cend(),
            [&sum] (const auto& value) {sum += value; }
        );

        return sum;
    }

    static auto calculate_sum_accumulate(const std::vector<double>& values) noexcept
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

    static void benchmark() {

        constexpr int Length = 100'000'000;   // use with release mode
        //constexpr int Length = 10'000'000;        // use with debug mode
        //constexpr int Length = 10;             // just for testing software

        std::vector<double> values(Length);

        std::generate(
            values.begin(),
            values.end(), 
            [value = 0.0]() mutable { ++value; return value; }
        );

        double sum{};

        sum = calculate_sum_classic(values);
        std::println("sum: {:15.20g}", sum);

        sum = calculate_sum_iterator(values);
        std::println("sum: {:15.20g}", sum);

        sum = calculate_sum_range_based_loop(values);
        std::println("sum: {:15.20g}", sum);
        
        sum = calculate_sum_standard_algorithm(values);
        std::println("sum: {:15.20g}", sum);
        
        sum = calculate_sum_accumulate(values);
        std::println("sum: {:15.20g}", sum);
    }

    static void benchmarks()
    {
        benchmark();
    }
}

void main_range_based_for_loop()
{
    using namespace RangeBasedForLoop;
    test(); 
    benchmarks();
}

// =====================================================================================
// End-of-File
// =====================================================================================
