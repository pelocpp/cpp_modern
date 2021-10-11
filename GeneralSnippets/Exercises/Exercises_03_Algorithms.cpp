// =====================================================================================
// Exercises_03_Algorithms.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <numeric>
#include <vector>
#include <algorithm>

namespace Exercises_Algorithms {

    namespace Exercise_01 {

        bool andAll(std::initializer_list<bool> vec) {

            return std::accumulate(
                std::begin(vec),
                std::end(vec),
                true, // starting value
                [](bool first, bool next) {
                    return first and next;
                }
            );
        }

        bool orAll(std::initializer_list<bool> vec) {

            return std::accumulate(
                std::begin(vec),
                std::end(vec),
                false, // starting value
                [](bool first, bool next) {
                    return first or next;
                }
            );
        }

        void testExercise_01a() {
            bool result = andAll({ true, false, true });
            std::cout << std::boolalpha << result << std::endl;

            result = andAll({ true, true, true, true, true, true, true, true, true, true });
            std::cout << std::boolalpha << result << std::endl;
        }

        void testExercise_01b() {
            bool result = orAll({ false, true, false });
            std::cout << std::boolalpha << result << std::endl;

            result = orAll({ false, false, false, false, false, false, false, false, false, false });
            std::cout << std::boolalpha << result << std::endl;
        }

        void testExercise_01() {
            testExercise_01a();
            testExercise_01b();
        }
    }

    namespace Exercise_02 {

        void testExercise_02() {

            std::vector<int> numbers(20);

            auto fibo = [p = std::pair{ 0, 1 }]() mutable {
                auto [a, b] = p;
                p = { b, a + b };
                return a;
            };

            std::generate(
                std::begin(numbers),
                std::end(numbers),
                fibo
            );

            std::for_each(
                std::begin(numbers),
                std::end(numbers),
                [](const auto& n) {
                    std::cout << n << ' ';
                }
            );
            std::cout << std::endl;
        }
    }
}

void test_exercises_algorithms()
{
    using namespace Exercises_Algorithms;
    Exercise_01::testExercise_01();
    Exercise_02::testExercise_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
