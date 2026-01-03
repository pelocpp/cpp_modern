// =====================================================================================
// Exercises_14_ConstExpr.cpp
// =====================================================================================

module modern_cpp_exercises:const_expr;

namespace Exercises_ConstExpr {

    namespace Exercise_01 {

        // works for int arguments
        static constexpr auto maximum (int a, int b, int c) {

            if (a > b && a > c)
            {
                return a;
            }
            else if (b > a && b > c)
            {
                return b;
            }
            else
            {
                return c;
            }
        };

        template <typename T>
        static constexpr auto maximumGeneric (T a, T b, T c) {

            if (a > b && a > c)
            {
                return a;
            }
            else if (b > a && b > c)
            {
                return b;
            }
            else
            {
                return c;
            }
        };

        static constexpr auto maximumAuto(auto a, auto b, auto c) {

            if (a > b && a > c)
            {
                return a;
            }
            else if (b > a && b > c)
            {
                return b;
            }
            else
            {
                return c;
            }
        };

        // works for int arguments
        static auto maximumLambda = [](int a, int b, int c) constexpr {

            if (a > b && a > c)
            {
                return a;
            }
            else if (b > a && b > c)
            {
                return b;
            }
            else
            {
                return c;
            }
        };

        // works for arguments of different type (?!?)
        // type of the ternary ?: expression is
        // the common type of its second and third argument
        static auto maximumAutoLambda = [](auto a, auto b, auto c) constexpr {
            return (a > b && a > c) ? a : ((b > a && b > c) ? b : c  );
        };

        // works for arguments of different type (?!?)
        // type of the ternary ?: expression is
        // the common type of its second and third argument
        static auto maximumMoreAutoLambda = [](auto a, auto b, auto c) constexpr {

            if (a > b && a > c)
            {
                return a;
            }
            else if (b > a && b > c)
            {
                return b;
            }
            else
            {
                return c;
            }
        };

        // works for arbitrary arguments of the same type (!)
        template <typename T>
        static auto maximumGenericLambda = [](T a, T b, T c) constexpr {
            return (a > b && a > c) ? a : ((b > a && b > c) ? b : c);
        };

        // works for arbitrary arguments of the same type (!)
        // different syntax
        static auto maximumMoreGenericLambda = []<typename T>(T a, T b, T c) constexpr {
            return (a > b && a > c) ? a : ((b > a && b > c) ? b : c);
        };

        static void testExercise()
        {
            constexpr auto result01 = maximum(1, 2, 3);

            constexpr auto result02 = maximumGeneric(1.5, 2.5, 3.5);
            // constexpr auto result03 = maximumGeneric(1.5, 2.5f, 3.5);          // does NOT compile (!)
            constexpr auto result04 = maximumGeneric<double>(1.5, 2.5f, 3.5);

            constexpr auto result05 = maximumAuto(1.5, 2.5, 3.5);
            // constexpr auto result06 = maximumAuto(1.5, 2.5f, 3.5);             // does NOT compile (!)
            // constexpr auto result07 = maximumAuto<double>(1.5, 2.5f, 3.5);     // does NOT compile (!)

            constexpr auto result08 = maximumLambda(1, 2, 3);

            constexpr auto result09 = maximumAutoLambda(3, 1, 2);
            constexpr auto result10 = maximumAutoLambda(3, 2, 1);                 // Why does this compile, different argument types (?)

            constexpr auto result11 = maximumMoreAutoLambda(1.5, 3.5, 2.5);
            // constexpr auto result12 = maximumMoreAutoLambda(1.5, 3.5f, 2.5);   // does NOT compile (!)

            constexpr auto result13 = maximumAutoLambda(1.5, 3.5f, 2.5);          // Why does this compile (?)

            constexpr auto result14 = maximumGenericLambda<int>(5, 7, 6);
            constexpr auto result15 = maximumGenericLambda<double>(7.5, 8.5, 6.5f);  // Compiles, but different argument types (!)

            constexpr auto result16 = maximumMoreGenericLambda(5, 4, 3);
            // constexpr auto result17 = maximumMoreGenericLambda(5.5f, 4.5, 3.5);   // does NOT compile (!), compare with 'maximumGeneric' (?!?!)
        }
    }

    namespace Exercise_02 {

        template <typename T, typename ... TArgs>
        constexpr T maximum(T first, TArgs ... args)
        {
            T result{ first };

            ((result = result > args ? result : args) , ... );

            return result;
        }

        constexpr auto maximumAuto(auto first, auto ... args)
        {
            auto result{ first };

            ((result = result > args ? result : args) , ...);

            return result;
        }

        static void testExercise()
        {
            constexpr int m1{ maximum(1, 5, 3, 9, 7) };

            constexpr int m2{ maximum(2, 4, 6, 8, 6, 4, 2) };

            static_assert(m1 == 9, "wrong maximum value");
            static_assert(m2 == 8, "wrong maximum value");
        }
    }

    namespace Exercise_03 {

        template<typename T1, typename T2>
        static constexpr bool sameType(T1, T2)
        {
            return std::is_same<T1, T2>::value;
        }

        template<typename T1, typename T2, typename... TRest>
        static constexpr bool sameType(T1 arg1, T2 arg2, TRest... args)
        {
            return std::is_same<decltype(arg1), decltype(arg2)>::value && sameType(arg2, args...);
        }

        // Oder

        //template<typename T1, typename T2, typename... TRest>
        //constexpr bool sameType(T1 arg1, T2 arg2, TRest... args)
        //{
        //    return std::is_same<T1, T2>::value && sameType(arg2, args...);
        //}

        static void testExercise()
        {
            constexpr bool result1{ sameType(43, false, "hello") };
            std::cout << std::boolalpha << result1 << std::endl;

            constexpr bool result2{ sameType(1, 2, 3, 4, 5, 6, 7, 8, 9) };
            std::cout << std::boolalpha << result2 << std::endl;
        }
    }
}

void test_exercises_constexpr()
{
    using namespace Exercises_ConstExpr;

    Exercise_01::testExercise();
    Exercise_02::testExercise();
    Exercise_03::testExercise();
}

// =====================================================================================
// End-of-File
// =====================================================================================
