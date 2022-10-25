// =====================================================================================
// Exercises_07_Metaprogramming.cpp
// =====================================================================================

#include <iostream>
#include <string>

namespace Exercises_Metaprogramming {

    namespace Exercise_01 {

        // runtime versions
        size_t convert1(size_t number)
        {
            // prepend higher bits to lowest bit
            return (number == 0) ? 0 : (number % 10) | (convert1(number / 10) << 1);
        }

        size_t convert2(size_t number)
        {
            return number == 0 ? 0 : number % 10 + 2 * convert2(number / 10);
        }

        // compile time version - no error handling
        template <size_t N>
        struct Binary
        {
            static constexpr size_t value = Binary<N / 10>::value << 1 | N % 10;
            // or
            // static constexpr size_t value = N % 10 + 2 * Binary<N / 10>::value;
        };

        // explicit template specialization
        template <>
        struct Binary<0>
        {
            static constexpr size_t value = 0;
        };

        // compile time version - with error handling
        template <size_t N>
        struct BinaryEx
        {
            static_assert((N % 10) == 0 || (N % 10) == 1);

            static constexpr size_t value = BinaryEx<N / 10>::value << 1 | N % 10;
            // or
            // static constexpr size_t value = N % 10 + 2 * BinaryEx<N / 10>::value;
        };

        // explicit template specialization
        template <>
        struct BinaryEx<0>
        {
            static constexpr size_t value = 0;
        };

        void testExercise_01a() {

            size_t number{ 11111111 };
            size_t result{};
            result = convert1(number);
            std::cout << result << std::endl;
            result = convert2(number);
            std::cout << result << std::endl;

            number = 1001;
            result = convert1(number);
            std::cout << result << std::endl;
            result = convert2(number);
            std::cout << result << std::endl;
        }

        void testExercise_01b() {

            constexpr size_t one = Binary<1>::value;
            constexpr size_t three = Binary<11>::value;
            constexpr size_t five = Binary<101>::value;
            constexpr size_t seven = Binary<111>::value;
            constexpr size_t nine = Binary<1001>::value;
            constexpr size_t big = Binary<1000'0010'0011'0101>::value;
            constexpr size_t wrong1 = Binary<2>::value;
            constexpr size_t wrong2 = Binary<12345>::value;
            
            std::cout << one << std::endl;
            std::cout << three << std::endl;
            std::cout << five << std::endl;
            std::cout << seven << std::endl;
            std::cout << nine << std::endl;
            std::cout << big << std::endl;
            std::cout << wrong1 << std::endl;
            std::cout << wrong2 << std::endl;
        }

        void testExercise_01c() {

            constexpr size_t one = BinaryEx<1>::value;
            constexpr size_t three = BinaryEx<11>::value;
            constexpr size_t five = BinaryEx<101>::value;
            constexpr size_t seven = BinaryEx<111>::value;
            constexpr size_t nine = BinaryEx<1001>::value;
            constexpr size_t big = BinaryEx<1000'0010'0011'0101>::value;
            //constexpr size_t wrong1 = BinaryEx<2>::value;       // doesn't compile
            //constexpr size_t wrong2 = BinaryEx<12345>::value;   // doesn't compile

            std::cout << one << std::endl;
            std::cout << three << std::endl;
            std::cout << five << std::endl;
            std::cout << seven << std::endl;
            std::cout << nine << std::endl;
            std::cout << big << std::endl;
        }

        void testExercise_01() {
            testExercise_01a();
            testExercise_01b();
            testExercise_01c();
        }
    }

    namespace Exercise_02 {

        template<size_t N>
        struct FibImpl {
            static constexpr size_t value =
                FibImpl<N - 1>::value + FibImpl<N - 2>::value;
        };

        template<>
        struct FibImpl<1> {
            static constexpr size_t value = 1;
        };

        template<>
        struct FibImpl<0> {
            static constexpr size_t value = 0;
        };

        template<size_t N>
        struct Fibonacci {
            static_assert(N >= 0, "Error: Fibonacci can't be called with a negative integer");
            static constexpr size_t value = FibImpl<N>::value;
        };

        void testExercise_02() {
            std::cout << 1 << ":  " << Fibonacci<1>::value << std::endl;
            std::cout << 2 << ":  " << Fibonacci<2>::value << std::endl;
            std::cout << 5 << ":  " << Fibonacci<5>::value << std::endl;
            std::cout << 10 << ": " << Fibonacci<10>::value << std::endl;
            std::cout << 15 << ": " << Fibonacci<15>::value << std::endl;
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

void test_exercices_metaprogramming()
{
    using namespace Exercises_Metaprogramming;
    Exercise_01::testExercise_01();
    Exercise_02::testExercise_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
