// =====================================================================================
// Exercises_11_Initialization.cpp
// =====================================================================================

module;

#include "../ScopedTimer/ScopedTimer.h"

module modern_cpp_exercises:initialization;

namespace Exercises_Initialization {

    namespace Exercise_01 {

        class IntegerContainer {
        private:
            std::vector<int> m_data;

        public:
            IntegerContainer() {
                std::cout << "default c'tor" << std::endl;
            }

            IntegerContainer(int n1, int n2) {
                std::cout << "c'tor (int, int)" << std::endl;
                m_data.push_back(n1);
                m_data.push_back(n2);
            }

            IntegerContainer(std::initializer_list<int> data) : m_data{ data } {
                std::cout << "c'tor (std::initializer_list<int>)" << std::endl;
            }

            IntegerContainer(const std::vector<int>& data) : m_data{ data } {
                std::cout << "c'tor (std::vector<int>)" << std::endl;
            }
        };

        static void testExercise_01() {

            IntegerContainer container1{ {1, 2, 3, 4, 5, 6, 7, 8, 9, 10} };
            IntegerContainer container2;
            IntegerContainer container3{};
            IntegerContainer container4(1, 2);
            IntegerContainer container5{ 1, 2 };
            IntegerContainer container6{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        }
    }

    namespace Exercise_02 {

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

        static void testExercise_02() {
            {
                ScopedTimer watch{};

                for (size_t i{}; i != MaxIteration; ++i) {

                    // heap-based transfer of strings
                    SomeStrings::transferData(
                        std::vector<std::string> { 
                        "A", "B", "C", "D", "E", "F", "G", "H", "I",
                        "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                        "S", "T", "U", "V", "W", "X", "Y", "Z"
                    });
                }

                std::cout << "std::vector: " << std::endl;
            }

            {
                ScopedTimer watch{};

                for (size_t i{}; i != MaxIteration; ++i) {

                    // stack-based transfer of strings
                    SomeStrings::transferData(
                        std::initializer_list<std::string> {
                        "A", "B", "C", "D", "E", "F", "G", "H", "I",
                        "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                        "S", "T", "U", "V", "W", "X", "Y", "Z"
                    });
                }

                std::cout << "std::initializer_list: " << std::endl;;
            }
        }
    }
}

void test_exercises_initialization()
{
    using namespace Exercises_Initialization;
    Exercise_01::testExercise_01();
    Exercise_02::testExercise_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
