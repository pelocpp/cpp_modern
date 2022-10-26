// =====================================================================================
// Exercises_06_Folding.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <type_traits>
#include <algorithm>
#include <vector>
#include <iterator>

namespace Exercises_Folding {

    namespace Exercise_01 {

        // =============================================================
        // Logical And - with folding expression

        template<typename... TArgs>
        bool andAll(const TArgs... args) {
            return (... && args);  // unary left fold
        }

        void testExercise_01a() {

            bool result = andAll(true, (1 > 2), true);
            std::cout << std::boolalpha << result << std::endl;

            result = andAll(true, true, true);
            std::cout << std::boolalpha << result << std::endl;
        }

        // =============================================================
        // Logical Or - with folding expression

        template<typename... TArgs>
        bool orAll(const TArgs... args) {
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

        template<typename T, typename... TRest>
        constexpr bool sameType([[maybe_unused]] T arg, [[maybe_unused]] TRest... args)
        {
            // since C++17: folding expression !
            return (std::is_same_v<T, TRest> && ...);
            // or
            // return (std::is_same_v<decltype(arg), decltype(args)> && ...);
        }

        void testExercise_02() {

            constexpr bool result1 = sameType(1, 2, 3, 4, '?', 6, 7, 8, 9);
            std::cout << std::boolalpha << result1 << std::endl;

            constexpr bool result2 = sameType(43, false, "hello");
            std::cout << std::boolalpha << result2 << std::endl;

            constexpr bool result3 = sameType(1, 2, 3, 4, 5, 6, 7, 8, 9);
            std::cout << std::boolalpha << result3 << std::endl;

            constexpr bool result4 = sameType(1, 2, 3, 4, '?', 5, 6, 7, 8, 9);
            std::cout << std::boolalpha << result4 << std::endl;
        }
    }

    namespace Exercise_03 {

        template <typename T, typename...  TArgs>
        auto minimum(const T& x, const T& y, const TArgs&... args)
        {
            auto m = (x < y) ? x : y;

            if constexpr (sizeof... (args) > 0) {

                auto helper = [&](const auto& value) {
                    if (value < m) {
                        m = value;
                    }
                };

                (..., helper(args));
            }

            return m;
        }

        template <typename T, typename...  TArgs>
        auto maximum(const T& x, const T& y, const TArgs&... args)
        {
            auto m = (x > y) ? x : y;

            if constexpr (sizeof... (args) > 0) {

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

    namespace Exercise_04 {

        // ===================================================================
        // folding

        template <typename T, typename...  TArgs>
        void pushBackAll_01(std::vector<T>& vec, const TArgs&... args)
        {
            (vec.push_back(args) , ...);  // unary right fold or
            (... , vec.push_back(args));  // unary left fold
        }

        // or better - using perfect forwarding:

        //template <typename T, typename...  TArgs>
        //void pushBackAll_01(std::vector<T>& vec, TArgs&&... args)
        //{
        //    (vec.push_back(std::forward<TArgs>(args)) , ...);  // unary right fold or
        //    (..., vec.push_back(std::forward<TArgs>(args)));   // unary left fold
        //}


        void testExercise_04a()
        {
            std::vector<double> values;

            pushBackAll_01<double>(values, 30.0, 31.0, 32.0);

            std::copy(
                std::begin(values),
                std::end(values),
                std::ostream_iterator<double>(std::cout, " ")
            );

            std::cout << std::endl;
        }

        // ===================================================================
        // variadic templates

        template <typename T, typename TArg>
        void pushBackAll_02(std::vector<T>& vec, TArg&& arg)
        {
            vec.push_back(std::forward<TArg>(arg));
        }

        template <typename T, typename TArg, typename...  TArgs>
        void pushBackAll_02(std::vector<T>& vec, TArg&& arg, TArgs&&... args)
        {
            vec.push_back(std::forward<TArg>(arg));
            pushBackAll_02(vec, std::forward<TArgs>(args) ...);
        }

        void testExercise_04b()
        {
            std::vector<double> values;

            pushBackAll_02<double>(values, 20.0, 21.0, 22.0);

            std::copy(
                std::begin(values),
                std::end(values),
                std::ostream_iterator<double>(std::cout, " ")
            );

            std::cout << std::endl;
        }

        // ===================================================================
        // initializer list

        template <typename T, typename...  TArgs>
        void pushBackAll_03(std::vector<T>& vec, TArgs&&... args)
        {
            std::initializer_list<int> { (vec.push_back(std::forward<TArgs>(args)), 0) ... };
        }

        void testExercise_04c()
        {
            std::vector<double> values;

            pushBackAll_03<double>(values, 10.0, 11.0, 12.0);

            std::copy(
                std::begin(values),
                std::end(values),
                std::ostream_iterator<double>(std::cout, " ")
            );

            std::cout << std::endl;
        }

        void testExercise_04() {
            testExercise_04a();
            testExercise_04b();
            testExercise_04c();
        }
    }

    namespace Exercise_05 {

        template <typename... TArgs>
        void printer1(TArgs... args) {
            (std::cout << ... << args);
            std::cout << std::endl;
        }

        template <typename... TArgs>
        void printer2(TArgs... args) {
            ((std::cout << args << ", "), ...);
            std::cout << std::endl;
        }

        template <typename T, typename... TArgs>
        void printer3(T first, TArgs... rest) {
            std::cout << first;
            ((std::cout << ", " << rest), ...);
            std::cout << std::endl;
        }

        /* The solution uses a template argument for the first parameter and then
           a variadic parameter list for the rest. We print then the first element
           and then add a separator before all other entries.
        */

        void testExercise_05() {
            printer1(1, "ABC", 2, "DEF", 3, "GHI");
            printer2(1, "ABC", 2, "DEF", 3, "GHI");
            printer3(1, "ABC", 2, "DEF", 3, "GHI");
        }
    }
}

void test_exercises_folding()
{
    using namespace Exercises_Folding;
    Exercise_01::testExercise_01();
    Exercise_02::testExercise_02();
    Exercise_03::testExercise_03();
    Exercise_04::testExercise_04();
    Exercise_05::testExercise_05();
}

// =====================================================================================
// End-of-File
// =====================================================================================
