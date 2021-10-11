// =====================================================================================
// Exercises_14_ConstExpr.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <numeric>

namespace Exercises_ConstExpr {

    namespace Exercise_01 {

        template<typename T1, typename T2>
        constexpr bool sameType(T1 arg1, T2 arg2)
        {
            return std::is_same<T1, T2>::value;
        }

        template<typename T1, typename T2, typename... TREST>
        constexpr bool sameType(T1 arg1, T2 arg2, TREST... args)
        {
            return std::is_same<decltype(arg1), decltype(arg2)>::value && sameType(arg2, args...);
        }

        void testExercise_01() {

            constexpr bool result1 = sameType(43, false, "hello");
            std::cout << std::boolalpha << result1 << std::endl;

            constexpr bool result2 = sameType(1, 2, 3, 4, 5, 6, 7, 8, 9);
            std::cout << std::boolalpha << result2 << std::endl;
        }
    }
}

void test_exercises_constexpr()
{
    using namespace Exercises_ConstExpr;
    Exercise_01::testExercise_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
