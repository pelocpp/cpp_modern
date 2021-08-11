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

namespace Exercises_Folding {

    namespace Exercise_01 {

        // =============================================================
        // Logical And - with folding expression

        template<typename ...Args>
        bool andAll(Args ...args) {
            return (args && ... && true);  // binary right fold (init == true)
        }

        void testExercise_01a() {

            bool result = andAll(true, (1 > 2), true);
            std::cout << std::boolalpha << result << std::endl;

            result = andAll(true, true, true);
            std::cout << std::boolalpha << result << std::endl;
        }

        // =============================================================
        // Logical Or - with folding expression

        template<typename ...Args>
        bool orAll(Args ...args) {
            return (args || ...);  // unary right fold
        }

        void testExercise_01b() {

            bool result = orAll(false, false, true);
            std::cout << std::boolalpha << result << std::endl;

            result = orAll(false, false, false, false, false);
            std::cout << std::boolalpha << result << std::endl;
        }

        void testExercise_01() {
            testExercise_01a();
            testExercise_01b();
        }
    }

    namespace Exercise_02 {

        // Beachte:
        // Bei Anwendung eines Folding Expression wird nach dem "Ausrollen" des Folding Ausdrucks
        // das 1. mit dem 2., das 1. mit dem 3., das 1. mit dem 4. Element usw. verglichen. 
        // Beim Lösungsansatz mit variadischen Templates wird
        // das 1. mit dem 2., das 2. mit dem 3., das 3. mit dem 4. Element usw. verglichen!

        template<typename T, typename... TREST>
        constexpr bool sameType(T arg, TREST... args)
        {
            // since C++17: folding expression !
            return (std::is_same_v<decltype(arg), decltype(args)> && ...);
        }

        void testExercise_02() {

            bool result;
            result = sameType(1, 2, 3, 4, '?', 6, 7, 8, 9);
            std::cout << std::boolalpha << result << std::endl;

            result = sameType(43, false, "hello");
            std::cout << std::boolalpha << result << std::endl;

            result = sameType(1, 2, 3, 4, 5, 6, 7, 8, 9);
            std::cout << std::boolalpha << result << std::endl;

            result = sameType(1, 2, 3, 4, '?', 5, 6, 7, 8, 9);
            std::cout << std::boolalpha << result << std::endl;

            result = sameType("123", std::string("456"), "789", "111", "999");
            std::cout << std::boolalpha << result << std::endl;
        }
    }

    namespace Exercise_03 {

        template <typename T, typename ... TARGS>
        auto minimum(const T& x, const T& y, const TARGS& ... args)
        {
            auto m = (x < y) ? x : y;

            if (sizeof ... (args) > 0) {

                auto helper = [&](const auto& value) {
                    if (value < m) {
                        m = value;
                    }
                };

                (..., helper(args));
            }

            return m;
        }

        template <typename T, typename ... TARGS>
        auto maximum(const T& x, const T& y, const TARGS& ... args)
        {
            auto m = (x > y) ? x : y;

            if (sizeof ... (args) > 0) {

                auto helper = [&](const auto& value) {
                    if (value > m) {
                        m = value;
                    }
                };

                (..., helper(args));
            }

            return m;
        }

        void testExercise_03a() {
            std::cout << minimum(1, 2) << std::endl;
            std::cout << minimum(2, 3, 4) << std::endl;
            std::cout << minimum(4, 3, 2, 1) << std::endl;
            std::cout << minimum(6, 2, 5, 7, 4, 3) << std::endl;
            std::cout << std::endl;
        }

        void testExercise_03b() {
            std::cout << maximum(1, 2) << std::endl;
            std::cout << maximum(2, 3, 4) << std::endl;
            std::cout << maximum(4, 3, 2, 1) << std::endl;
            std::cout << maximum(6, 1, 5, 2, 4, 3) << std::endl;
        }

        void testExercise_03() {
            testExercise_03a();
            testExercise_03b();
        }
    }
}

void test_exercices()
{
    using namespace Exercises_Folding;
    Exercise_01::testExercise_01();
    Exercise_02::testExercise_02();
    Exercise_03::testExercise_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
