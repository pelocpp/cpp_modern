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
}

void test_exercises_initialization()
{
    using namespace Exercises_Initialization;
    Exercise_01::testExercise_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
