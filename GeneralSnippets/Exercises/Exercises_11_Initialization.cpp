// =====================================================================================
// Exercises_11_Initialization.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

namespace Exercises_Initialization {

    namespace Exercise_01 {

        template <typename T>
        class MyContainer {
        private:
            std::vector<T> m_data;

        public:
            MyContainer() = default;

            MyContainer(const T& d1, const T& d2) {
                std::cout << "c'tor (const T&, const T&)" << std::endl;
                m_data.push_back(d1);
                m_data.push_back(d2);
            }

            MyContainer(std::initializer_list<T> data) : m_data(data) {
                std::cout << "c'tor (std::initializer_list<T>)" << std::endl;
            }

            void operator()() {
                std::cout << "  [";
                for (auto data : m_data) {
                    std::cout << data << ' ';
                }
                std::cout << ']' << std::endl;
            }
        };

        void testExercise_01() {
            // using MyContainer with int
            MyContainer<int> container1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            container1();

            // using MyContainer with std::string
            MyContainer<std::string> container2{ "range", "-", "based", "for", "loop" };
            container2();

            MyContainer<int> container3;
            container3();
            MyContainer<int> container4{};
            container4();
            MyContainer<int> container5(1, 2);
            container5();
            MyContainer<int> container6{ 1, 2 };
            container6();
        }
    }

    namespace Exercise_02 {

        void printResults(
            std::string tag,
            std::chrono::high_resolution_clock::time_point startTime,
            std::chrono::high_resolution_clock::time_point endTime)
        {
            std::cout
                << tag
                << std::fixed
                << std::setprecision(6)
                << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime).count()
                << " msecs."
                << std::endl;
        }

        class SomeStrings
        {
        public:
            static auto transferData(const std::vector<std::string>& strings)
            {
                // prevent optimizer to work too hard ...
                auto& first = strings.front();
                auto& last = strings.back();
                return first + last;
                //std::cout << "first=" << first << std::endl;
                //std::cout << "last=" << last << std::endl;
            }

            static auto transferData(const std::initializer_list<std::string> strings)
            {
                // prevent optimizer to work too hard ...
                const auto& first = strings.begin();
                const auto& last = std::prev(strings.end());
                return *first + *last;
                //std::cout << "first=" << *first << std::endl;
                //std::cout << "last=" << *last << std::endl;
            }
        };

        // Note: Debug vs Release Mode
        constexpr int MaxIteration = 10'000;

        void testExercise_02() {
            {
                const auto startTime{ std::chrono::high_resolution_clock::now() };

                for (size_t i{}; i != MaxIteration; ++i) {

                    // heap-based transfer of strings
                    SomeStrings::transferData(
                        std::vector<std::string> { 
                        "A", "B", "C", "D", "E", "F", "G", "H", "I",
                        "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                        "S", "T", "U", "V", "W", "X", "Y", "Z"
                    });
                }

                const auto endTime{ std::chrono::high_resolution_clock::now() };
                printResults("std::vector:           ", startTime, endTime);
            }

            {
                const auto startTime{ std::chrono::high_resolution_clock::now() };

                for (size_t i{}; i != MaxIteration; ++i) {

                    // stack-based transfer of strings
                    SomeStrings::transferData(
                        std::initializer_list<std::string> {
                        "A", "B", "C", "D", "E", "F", "G", "H", "I",
                        "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                        "S", "T", "U", "V", "W", "X", "Y", "Z"
                    });
                }

                const auto endTime{ std::chrono::high_resolution_clock::now() };
                printResults("std::initializer_list: ", startTime, endTime);
            }
        }
    }
}

void test_exercises_initialization()
{
    using namespace Exercises_Initialization;
    // Exercise_01::testExercise_01();
    Exercise_02::testExercise_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
