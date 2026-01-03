// =====================================================================================
// Exercises_03_Algorithms.cpp
// =====================================================================================

module;

#include "../ScopedTimer/ScopedTimer.h"

module modern_cpp_exercises:stl;

namespace Exercises_STL {

    namespace Exercise_01 {

        template <typename T>
        static void print(const std::vector<T>& v)
        {
            std::println("Size: {}, Capacity: {}", v.size(), v.capacity());

            for (auto elem : v) {
                std::print("{} ", elem);
            }
            std::println();
            std::println();
        }

        static void testExercise_01()
        {
            // "wrong" implementation (usage of invalid iterator)

            std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            print(vec);

            // erase all even numbers
            for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
            {
                if (*it % 2 == 0) {
                    vec.erase(it);
                }
            }

            print(vec);
        }

        static void testExercise_02()
        {
            // correct implementation, but inefficient runtime behaviour

            std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            print(vec);

            // erase all even numbers
            for (std::vector<int>::iterator it = vec.begin(); it != vec.end();)
            {
                if (*it % 2 == 0)
                    it = vec.erase(it);
                else
                    ++it;
            }

            print(vec);
        }

        static void testExercise_03()
        {
            // again correct implementation, but efficient (good) runtime behaviour

            std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            print(vec);

            std::vector<int>::iterator pos = std::remove_if(
                vec.begin(),
                vec.end(),
                [](auto elem) { return elem % 2 == 0; }
            );

            vec.erase(pos, vec.end());

            print(vec);
        }

        // =======================================
        // 2 benchmarks:
        // constexpr std::size_t Max = 20;
        // constexpr std::size_t NumIterations = 1;

        constexpr std::size_t Max = 5000;
        constexpr std::size_t NumIterations = 100;

        static void testExercise_benchmark_01()
        {
            std::vector<int> original(Max);

            std::iota(original.begin(), original.end(), 1);

            ScopedTimer watch{};

            for (std::size_t i{}; i != NumIterations; ++i) {

                // demonstration of inefficient implementation

                std::vector<int> vec{ original };

                // print(vec);

                for (std::vector<int>::iterator it = vec.begin(); it != vec.end();)
                {
                    if (*it % 2 == 0)
                        it = vec.erase(it);
                    else
                        ++it;
                }

                // print(vec);
            }
        }

        static void testExercise_benchmark_02()
        {
            std::vector<int> original(Max);

            std::iota(original.begin(), original.end(), 1);

            ScopedTimer watch{};

            for (std::size_t i{}; i != NumIterations; ++i) {

                // demonstration of a better, (hopefully) efficient implementation

                std::vector<int> vec{ original };

                // print(vec);

                std::vector<int>::iterator pos = std::remove_if(
                    vec.begin(),
                    vec.end(),
                    [](auto elem) { return elem % 2 == 0; }
                );

                vec.erase(pos, vec.end());

                // print(vec);
            }
        }

        static void testExercise() {

            // testExercise_01();  // crashes - by design
            testExercise_02();
            testExercise_03();

            testExercise_benchmark_01();
            testExercise_benchmark_02();
        }
    }

    namespace Exercise_02 {

        static void testExercise() {

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

    namespace Exercise_03 {

        static bool andAll(std::initializer_list<bool> vec) {

            return std::accumulate(
                std::begin(vec),
                std::end(vec),
                true, // starting value
                [](bool first, bool next) {
                    return first and next;
                }
            );
        }

        static bool orAll(std::initializer_list<bool> vec) {

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

        static void testExercise() {
            testExercise_01a();
            testExercise_01b();
        }
    }
}

void test_exercises_stl()
{
    using namespace Exercises_STL;

    Exercise_01::testExercise();
    Exercise_02::testExercise();
    Exercise_03::testExercise();
}

// =====================================================================================
// End-of-File
// =====================================================================================
