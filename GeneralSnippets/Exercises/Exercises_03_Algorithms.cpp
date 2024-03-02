// =====================================================================================
// Exercises_03_Algorithms.cpp
// =====================================================================================

module modern_cpp_exercises:algorithms;

import std;

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

        static void testExercise_01a() {
            bool result = andAll({ true, false, true });
            std::cout << std::boolalpha << result << std::endl;

            result = andAll({ true, true, true, true, true, true, true, true, true, true });
            std::cout << std::boolalpha << result << std::endl;
        }

        static void testExercise_01b() {
            bool result = orAll({ false, true, false });
            std::cout << std::boolalpha << result << std::endl;

            result = orAll({ false, false, false, false, false, false, false, false, false, false });
            std::cout << std::boolalpha << result << std::endl;
        }

        static void testExercise_01() {
            testExercise_01a();
            testExercise_01b();
        }
    }

    namespace Exercise_02 {

        static void testExercise_02() {

            std::vector<int> numbers(20);

            // uses structured binding
            auto fibo = [p = std::pair{ 0, 1 }]() mutable {
                auto [a, b] = p;
                p = { b, a + b };
                return a;
            };

            // without structured binding
            auto fibo2 = [p = std::pair{ 0, 1 }]() mutable {
                int n1 = p.first;
                int n2 = p.second;
                p = { n2, n1 + n2 };
                return n1;
            };

            // using a 'state' variable in the scope / "closure"
            auto pLocal = std::pair{ 0, 1 };
            auto fibo3 = [&] {
                int n1 = pLocal.first;
                int n2 = pLocal.second;
                pLocal = { n2, n1 + n2 };
                return n1;
            };

            std::generate(
                std::begin(numbers),
                std::end(numbers),
                fibo3
            );

            for (int n : numbers) {
                std::cout << n << ' ';
            }

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
