// =====================================================================================
// Exercices
// =====================================================================================

#include <iostream>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <optional>
#include <tuple>
#include <array>
#include <complex>
#include <variant>
#include <numeric>
#include <iterator>
#include <chrono>
#include <thread>

namespace Exercises_Metaprogramming {

    namespace Exercise_01 {

        template<long long n>
        struct FibImpl {
            static constexpr long long value =
                FibImpl<n - 1>::value + FibImpl<n - 2>::value;
        };

        template<>
        struct FibImpl<1> {
            static constexpr long long value = 1;
        };

        template<>
        struct FibImpl<0> {
            static constexpr long long value = 0;
        };

        template<long long n>
        struct Fibonacci {
            static_assert(n >= 0, "Error: Fibonacci can't be called with a negative integer");
            static constexpr long long value = FibImpl<n>::value;
        };

        void testExercise_01() {
            std::cout << 1 << ":  " << Fibonacci<1>::value << std::endl;
            std::cout << 2 << ":  " << Fibonacci<2>::value << std::endl;
            std::cout << 10 << ": " << Fibonacci<10>::value << std::endl;
            std::cout << 20 << ": " << Fibonacci<20>::value << std::endl;
            std::cout << 30 << ": " << Fibonacci<30>::value << std::endl;
            std::cout << 40 << ": " << Fibonacci<40>::value << std::endl;
            std::cout << 50 << ": " << Fibonacci<50>::value << std::endl;
            std::cout << 60 << ": " << Fibonacci<60>::value << std::endl;
            std::cout << 70 << ": " << Fibonacci<70>::value << std::endl;
            std::cout << 80 << ": " << Fibonacci<80>::value << std::endl;
            std::cout << 90 << ": " << Fibonacci<90>::value << std::endl;
            std::cout << 92 << ": " << Fibonacci<92>::value << std::endl;
        }
    }
}

void main_exercices_metaprogramming()
{
    using namespace Exercises_Metaprogramming;
    Exercise_01::testExercise_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
