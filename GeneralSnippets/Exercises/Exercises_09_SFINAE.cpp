// =====================================================================================
// Exercises_09_SFINAE.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <array>

namespace Exercises_SFINAE {

    namespace Exercise_01 {

        template <class T>
        auto first(T& c) -> decltype(c.begin()) {
            std::cout << "__FUNCSIG__ = " << __FUNCSIG__ << std::endl;
            return c.begin();
        }

        template <class T, size_t N>
        T* first(T(&arr)[N]) {
            std::cout << "__FUNCSIG__ = " << __FUNCSIG__ << "N = " << N << std::endl;
            return arr;
        }

        void testExercise_01() {
            int vals[5]{ 1, 2, 3, 4, 5 };
            int elem = *(first(vals));
            std::cout << elem << std::endl;

            // OK: The first function template substitution fails because
            // 'vals.begin()' is ill-formed. This is not an error! That function
            // is just removed from consideration as a viable overload candidate,
            // leaving us with the array overload.

            std::array<int, 20> anotherArray = { 10, 11, 12 };
            elem = *first(anotherArray);
            std::cout << elem << std::endl;

            // OK: The first function template substitution succeeds because
            // 'vals.begin()' is well-formed

            std::vector<int> anotherVector = { 100, 101, 102 };
            elem = *first(anotherVector);
            std::cout << elem << std::endl;

            // OK: Matches too, because a std::vector has a begin method
        }
    }

    namespace Exercise_02 {

        // https://people.eecs.berkeley.edu/~brock/blog/detection_idiom.php

        template <typename T>
        struct MethodDetector {

            // SFINAE: template parameter definition
            template <typename U, typename TEST = decltype(std::declval<U>().get())>
            static constexpr bool detect(int) {
                return true;
            }

            // oder

            // SFINAE: return type definition
            //template <typename U>
            //static constexpr auto detect(int) -> decltype(std::declval<U>().get(), bool{}) {
            //    return true;
            //}

            template <typename U>
            static constexpr bool detect(...) {
                return false;
            }

            static constexpr bool value = MethodDetector::detect<T>(int{});
        };

        struct FirstStruct {
            int get() { return 123; };
        };

        struct SecondStruct {
            int getter() { return 456; };
        };

        void testExercise_02a() {

            std::cout
                << "FirstStruct:  "
                << std::boolalpha
                << MethodDetector<FirstStruct>::value
                << std::endl;

            std::cout
                << "SecondStruct: "
                << std::boolalpha
                << MethodDetector<SecondStruct>::value
                << std::endl;
        };

        template <typename T>
        struct MethodDetectorEx {

            // SFINAE: template parameter definition
            template <typename U, typename TEST = decltype(std::declval<U>().get(std::declval<int>(), std::declval<int>()))>
            static constexpr bool detect(int) {
                return true;
            }

            // oder

            // SFINAE: return type definition
            //template <typename U>
            //static constexpr auto detect(int) -> decltype(std::declval<U>().get(std::declval<int>(), std::declval<int>()), bool{ }) {
            //    return true;
            //}

            template <typename U>
            static constexpr bool detect(...) {
                return false;
            }

            static constexpr bool value = MethodDetectorEx::detect<T>(int{});
        };

        struct ThirdStruct {
            int get(int value) { return 2 * value; };
        };

        struct FourthStruct {
            int get(int value1, int value2) { return value1 * value2; };
        };

        void testExercise_02b() {

            std::cout
                << "ThirdStruct:  "
                << std::boolalpha
                << MethodDetectorEx<ThirdStruct>::value
                << std::endl;

            std::cout
                << "FourthStruct: "
                << std::boolalpha
                << MethodDetectorEx<FourthStruct>::value
                << std::endl;
        };

        void testExercise_02() {
            testExercise_02a();
            testExercise_02b();
        }
    }
}

void test_exercices_sfinae()
{
    using namespace Exercises_SFINAE;
    Exercise_01::testExercise_01();
    Exercise_02::testExercise_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
