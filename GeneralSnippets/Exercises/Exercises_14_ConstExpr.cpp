// =====================================================================================
// Exercises_14_ConstExpr.cpp
// =====================================================================================

module modern_cpp_exercises:const_expr;

namespace Exercises_ConstExpr {

    namespace Exercise_01 {

        // works for int arguments
        auto maximum = [](int a, int b, int c) constexpr {

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
        auto maximumAuto = [](auto a, auto b, auto c) constexpr {
            return (a > b && a > c) ? a : ((b > a && b > c) ? b : c  );
        };

        // works for arguments of different type (?!?)
        // type of the ternary ?: expression is
        // the common type of its second and third argument
        auto maximumMoreAuto = [](auto a, auto b, auto c) constexpr {

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
        auto maximumGeneric = [](T a, T b, T c) constexpr {
            return (a > b && a > c) ? a : ((b > a && b > c) ? b : c);
        };

        // works for arbitrary arguments of the same type (!)
        // different syntax
        auto maximumMoreGeneric = []<typename T>(T a, T b, T c) constexpr {
            return (a > b && a > c) ? a : ((b > a && b > c) ? b : c);
        };

        static void testExercise() {

            constexpr auto result1 = maximum(1, 2, 3);

            constexpr auto result2 = maximumAuto(3, 1, 2);
            constexpr auto result3 = maximumAuto(3, 2, 1);                    // Why does this compile, different argument types (?)

            constexpr auto result4 = maximumMoreAuto(1.5, 3.5, 2.5);
            // constexpr auto result5 = maximumMoreAuto(1.5, 3.5f, 2.5);      // does NOT compile (!)

            constexpr auto result6 = maximumAuto(1.5, 3.5f, 2.5);             // Why does this compile (?)

            constexpr auto result7 = maximumGeneric<int>(5, 7, 6);
            constexpr auto result8 = maximumGeneric<double>(7.5, 8.5, 6.5f);  // Compiles, but different argument types (!)

            constexpr auto result9 = maximumMoreGeneric(5, 4, 3);
            // constexpr auto result10 = maximumMoreGeneric(5.5f, 4.5, 3.5);  // does NOT compile (!), compare with 'maximumGeneric' (?!?!)
        }
    }

    namespace Exercise_02 {

        template<typename T1, typename T2>
        constexpr bool sameType(T1, T2)
        {
            return std::is_same<T1, T2>::value;
        }

        template<typename T1, typename T2, typename... TRest>
        constexpr bool sameType(T1 arg1, T2 arg2, TRest... args)
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
}

// =====================================================================================
// End-of-File
// =====================================================================================
