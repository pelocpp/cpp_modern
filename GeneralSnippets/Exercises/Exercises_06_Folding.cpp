// =====================================================================================
// Exercises_06_Folding.cpp
// =====================================================================================

module modern_cpp_exercises:folding;

namespace Exercises_Folding {

    namespace Exercise_01 {

        // =============================================================
        // Logical And - with folding expression

        template<typename ... TArgs>
        bool andAll(TArgs ... args) {
            return (... && args);  // unary left fold
        }

        static void testExercise_01a() {

            bool result{ andAll(true, (1 > 2), true) };
            std::cout << std::boolalpha << result << std::endl;

            result = andAll(true, true, true);
            std::cout << std::boolalpha << result << std::endl;
        }

        // =============================================================
        // Logical Or - with folding expression

        template<typename ... TArgs>
        bool orAll(TArgs... args) {
            return (args || ...);  // unary right fold
        }

        static void testExercise_01b() {

            bool result{ orAll(false, false, true) };
            std::cout << std::boolalpha << result << std::endl;

            result = orAll(false, false, false, false, false);
            std::cout << std::boolalpha << result << std::endl;
        }

        static void testExercise_01() {
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

        template<typename T, typename ... TArgs>
        constexpr bool sameType(T, TArgs...)
        {
            return (std::is_same_v<T, TArgs> && ...);
        }

        template<typename T, typename ... TArgs>
        constexpr bool sameTypeEx(T arg, TArgs... args)
        {
            return (std::is_same_v<decltype(arg), decltype(args)> && ...);
        }

        static void testExercise_02() {

            constexpr bool result1{ sameType(1, 2, 3, 4, '?', 6, 7, 8, 9) };
            std::cout << std::boolalpha << result1 << std::endl;

            constexpr bool result2{ sameType(43, false, "hello") };
            std::cout << std::boolalpha << result2 << std::endl;

            constexpr bool result3{ sameTypeEx(1, 2, 3, 4, 5, 6, 7, 8, 9) };
            std::cout << std::boolalpha << result3 << std::endl;

            constexpr bool result4{ sameTypeEx(1, 2, 3, 4, '?', 5, 6, 7, 8, 9) };
            std::cout << std::boolalpha << result4 << std::endl;
        }
    }

    namespace Exercise_03 {

        template <typename T, typename ...  TArgs>
        auto minimum(const T& x, const T& y, const TArgs&... args)
        {
            auto m{ (x < y) ? x : y };

            if constexpr (sizeof... (args) > 0)
            {
                auto helper = [&] (const auto& value) {
                    if (value < m) {
                        m = value;
                    }
                };

                ( ... , helper(args) );
            }

            return m;
        }

        template <typename T, typename ...  TArgs>
        auto maximum(const T& x, const T& y, const TArgs&... args)
        {
            auto m{ (x > y) ? x : y };

            if constexpr (sizeof... (args) > 0)
            {
                auto helper = [&] (const auto& value) {
                    if (value > m) {
                        m = value;
                    }
                };

                ( ... , helper(args) );
            }

            return m;
        }

        static void testExercise_03a() {
            std::cout << minimum(1, 2) << std::endl;
            std::cout << minimum(2, 3, 4) << std::endl;
            std::cout << minimum(4, 3, 2, 1) << std::endl;
            std::cout << minimum(6, 2, 5, 7, 4, 3) << std::endl;
            std::cout << std::endl;
        }

        static void testExercise_03b() {
            std::cout << maximum(1, 2) << std::endl;
            std::cout << maximum(2, 3, 4) << std::endl;
            std::cout << maximum(4, 3, 2, 1) << std::endl;
            std::cout << maximum(6, 1, 5, 2, 4, 3) << std::endl;
        }

        static void testExercise_03() {
            testExercise_03a();
            testExercise_03b();
        }
    }

    namespace Exercise_04 {

        // ===================================================================
        // folding

        template <typename T, typename ...  TArgs>
        void pushBackAll_01(std::vector<T>& vec, const TArgs&... args)
        {
            (vec.push_back(args) , ...);  // unary right fold or
            (... , vec.push_back(args));  // unary left fold
        }

        // or better - using perfect forwarding:

        //template <typename T, typename ...  TArgs>
        //void pushBackAll_01(std::vector<T>& vec, TArgs&&... args)
        //{
        //    (vec.push_back(std::forward<TArgs>(args)) , ...);  // unary right fold or
        //    (..., vec.push_back(std::forward<TArgs>(args)));   // unary left fold
        //}

        static void testExercise_04a()
        {
            std::vector<double> values;

            pushBackAll_01<double>(values, 30.0, 31.0, 32.0);

            for (auto elem : values) {
                std::cout << elem << ' ';
            }

            std::cout << std::endl;
        }

        // ===================================================================
        // variadic templates

        template <typename T, typename TArg>
        void pushBackAll_02(std::vector<T>& vec, TArg&& arg)
        {
            vec.push_back(std::forward<TArg>(arg));
        }

        template <typename T, typename TArg, typename ...  TArgs>
        void pushBackAll_02(std::vector<T>& vec, TArg&& arg, TArgs&&... args)
        {
            vec.push_back(std::forward<TArg>(arg));
            pushBackAll_02(vec, std::forward<TArgs>(args) ...);
        }

        static void testExercise_04b()
        {
            std::vector<double> values;

            pushBackAll_02<double>(values, 20.0, 21.0, 22.0);

            for (auto elem : values) {
                std::cout << elem << ' ';
            }

            std::cout << std::endl;
        }

        // ===================================================================
        // initializer list

        template <typename T, typename ...  TArgs>
        void pushBackAll_03(std::vector<T>& vec, TArgs&&... args)
        {
            std::initializer_list<int> { (vec.push_back(std::forward<TArgs>(args)), 0) ... };
        }

        static void testExercise_04c()
        {
            std::vector<double> values;

            pushBackAll_03<double>(values, 10.0, 11.0, 12.0);

            for (auto elem : values) {
                std::cout << elem << ' ';
            }

            std::cout << std::endl;
        }

        static void testExercise_04() {
            testExercise_04a();
            testExercise_04b();
            testExercise_04c();
        }
    }

    namespace Exercise_05 {

        // ---------------------------------------------------------
        // no separator

        template <typename ... TArgs>
        void printer1(TArgs... args) {
            (std::cout << ... << args);
        }

        // ---------------------------------------------------------
        // with separator - but also with trailing separator

        template <typename ... TArgs>
        void printer2(TArgs... args) {
            ((std::cout << args << ", ") , ...);
        }

        // ---------------------------------------------------------
        // This solution uses a template argument for the first parameter
        // and then a variadic parameter list for the remaining parameters.
        // We print then the first element and then add a separator
        // before all remaining entries are being printed

        template <typename T, typename ... TArgs>
        void printer3(T first, TArgs... args) {
            std::cout << first;
            ((std::cout << ", " << args) , ...);
        }

        /* Miscellaneous implementation variants:
        */

        // ---------------------------------------------------------
        // using range-based for-loop and std::initializer_list object

        template <typename T>
        void printCommaAndValue(T arg) {
            std::cout << ", " << arg;
        }

        template <typename T, typename ... TArgs>
        void printer4(T first, TArgs ... args) {
            std::cout << first;
            for (auto value : { args ... }) {
                printCommaAndValue(value);
            }
        }

        // ----------------------------------------------------
        // similar to printer3 - just using a helper function

        template <typename T, typename ... TArgs>
        void printer5(T first, TArgs ... args) {
            std::cout << first;
            (printCommaAndValue(args) , ...);
        }

        // ----------------------------------------------------
        // using a lambda helper function

        auto lambdaPrintCommaAndValue = [] (auto value) {
            std::cout << ", " << value;
        };

        template <typename T, typename ... TArgs>
        void printer6(T first, TArgs ... args) {
            std::cout << first;
            (lambdaPrintCommaAndValue(args) , ...);
        }

        // ----------------------------------------------------
        // hiding lambda helper function inside printer function

        template <typename T, typename ... TArgs>
        void printer7(T first, TArgs ... args) {

            auto localLambdaPrintCommaAndValue = [](auto value) {
                std::cout << ", " << value;
            };

            std::cout << first;
            (localLambdaPrintCommaAndValue(args), ...);
        }

        // ----------------------------------------------------
        // using self-invoking lambda helper function

        template <typename T, typename ... TArgs>
        void printer8(T first, TArgs ... args) {
            std::cout << first;
            // IIFE - Immediately Invoked Functional Expression :
            ([](auto value) { std::cout << ", " << value; } (args), ...);
        }

        // ----------------------------------------------------
        // using binary folding: extract first parameter
        // and print this parameter with the help of an 'init object':
        // print the remaining parameters with 'binary folding over a comma'

        template <typename T, typename ... TArgs>
        void printer9(T first, TArgs ... args) {

            ( (std::cout << first) , ..., (std::cout << ", " << args) );
            std::cout << std::endl;
        }

        // ----------------------------------------------------

        static void testExercise_05() {
            printer1(1, "ABC", 2, "DEF", 3, "GHI");
            std::cout << std::endl;
            printer2(1, "ABC", 2, "DEF", 3, "GHI");
            std::cout << std::endl;
            printer3(1, "ABC", 2, "DEF", 3, "GHI");
            std::cout << std::endl;
            printer4(1, 2, 3, 4, 5);     // note: parameter types must be the same
            std::cout << std::endl;
            printer5(1, "ABC", 2, "DEF", 3, "GHI");
            std::cout << std::endl;
            printer6(1, "ABC", 2, "DEF", 3, "GHI");
            std::cout << std::endl;
            printer7(1, "ABC", 2, "DEF", 3, "GHI");
            std::cout << std::endl;
            printer8(1, "ABC", 2, "DEF", 3, "GHI");
            std::cout << std::endl;
            printer9(1, "ABC", 2, "DEF", 3, "GHI");
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
