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

namespace Exercises_PerfectForwarding {

    namespace Exercise_01 {

        template <typename T>
        void list(T&& value)
        {
            std::cout << std::forward<T>(value) << std::endl;
        }

        template <typename T, typename ... TREST>
        void list(T&& first, TREST&& ... rest)
        {
            std::cout << std::forward<T>(first) << std::endl;
            list(std::forward<TREST>(rest)...);
        }

        void test_01() 
        {
            int n{ 123 };
            const double Pi{ 3.14 };

            list(10, "abc", n, Pi, 2.4, std::string{ "ABC" }, 99.99f);
        }

        struct Point
        {
            int m_x;
            int m_y;
        };

        std::ostream& operator<< (std::ostream& os, const Point& p)
        {
            os << '[' << p.m_x << ',' << p.m_y << ']';
            return os;
        }

        void test_02() 
        {
            Point p{ 11, 12 };
            Point* pp = new Point{ 3, 4 };
            std::complex<double> c{ 2.5, 3.5 };
            list(c, 10, "abc", p, *pp, 2.4, Point{ 1, 2 });
        }

        // Lösung zur Ergänzungsaufgabe:
        template <typename T>
        void print(int index, T&& value)
        {
            std::cout << index << ": " << std::forward<T>(value) << std::endl;
        }

        template <typename T, typename ... TREST>
        void list_internal(int index, T&& first, TREST&& ... rest)
        {
            index++;
            print(index, std::forward<T>(first));
            if constexpr (sizeof...(rest) > 0) {
                list_internal(index, std::forward<TREST>(rest)...);
            }
        }

        template <typename T, typename ... TREST>
        void listEx(T&& first, TREST&& ... rest)
        {
            int index = 1;
            print(index, std::forward<T>(first));
            list_internal(index, std::forward<TREST>(rest)...);
        }

        void test_03() {
            int n = 123;
            const double pi = 3.14;

            listEx(10, "abc", n, pi, 2.4, std::string("ABC"), 99.99f);
        }

        void test_04() {
            Point p{ 11, 12 };
            Point* pp = new Point{ 3, 4 };
            std::complex<double> c(2.5, 2.5);
            listEx(c, 10, "abc", p, *pp, 2.4, Point{ 1, 2 });
        }

        void test_05() {
            listEx(10, 11, 12, 13, 14);
        }

        // NEU

        template <typename ... T>
        void listExEx0(T&& ... args)
        {
            std::initializer_list<int> { (std::cout << std::forward<T>(args) << std::endl, int{})... };
        }

        template <typename ... T>
        void listExEx1(T&& ... args)
        {
            size_t count{};

            std::initializer_list<int> { (std::cout << ++count << ": " << std::forward<T>(args) << std::endl, int{})... };
        }

        void test_06() {
            listExEx0(100, 101, 102, 103, 104, 105);
            listExEx1(100, 101, 102, 103, 104, 105);
        }

        void test_07() {
            Point p{ 11, 12 };
            Point* pp = new Point{ 3, 4 };
            std::complex<double> c(2.5, 2.5);
            listExEx0(c, 10, "abc", p, *pp, 2.4, Point{ 1, 2 });
            listExEx1(c, 10, "abc", p, *pp, 2.4, Point{ 1, 2 });
        }


        void testExercise_01() {
            //test_01();
            //test_02();
            //test_03();
            //test_04();
            //test_05();

            //test_06();
            test_07();
        }
    }

    namespace Exercise_02 {

        void f()
        {
            // simulate some work (function without parameters)
            std::cout << "calling f" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        void g(int a, double b)
        {
            // simulate some work (function with parameters)
            std::cout << "calling g with parameters " << a << " and " << b << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        // ===============================================================
        // Erste Variante: Zeitmessung in Millisekunden

        class ExecutionTimer
        {
        public:
            template <typename F, typename... Args>
            static std::chrono::milliseconds duration(F&& f, Args&&... args)
            {
                std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
                std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
                std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();
                std::chrono::nanoseconds diff = end - start;
                return std::chrono::duration_cast<std::chrono::milliseconds>(diff);
            }
        };

        void test_01() {
            std::chrono::milliseconds time = ExecutionTimer::duration(f);
            std::cout << time.count() << " msecs." << std::endl;
        }

        void test_02() {
            std::chrono::milliseconds time = ExecutionTimer::duration(g, 10, 20.0);
            std::cout << time.count() << " msecs." << std::endl;
        }

        // ===============================================================
        // Zweite Variante: Zeitmessung via Template Parameter einstellbar

        template <
            typename Time = std::chrono::microseconds,
            typename TClock = std::chrono::high_resolution_clock
        >
        class ExecutionTimerEx
        {
        public:
            template <typename F, typename... Args>
            static Time duration(F&& f, Args&&... args)
            {
                std::chrono::time_point start = TClock::now();
                std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
                std::chrono::time_point end = TClock::now();
                auto diff = end - start;
                return std::chrono::duration_cast<Time>(diff);
            }
        };

        void test_03() {
            auto time = ExecutionTimerEx<>::duration(g, 10, 20.0);
            std::cout << time.count() << " microseconds." << std::endl;
        }

        void test_04() {
            auto time = ExecutionTimerEx<std::chrono::milliseconds>::duration(g, 20, 30.0);
            std::cout << time.count() << " milliseconds." << std::endl;
        }

        void test_05() {
            auto time = ExecutionTimerEx<std::chrono::microseconds>::duration(g, 30, 40.0);
            std::cout << time.count() << " microseconds." << std::endl;
        }

        void test_06() {
            auto time = ExecutionTimerEx<std::chrono::nanoseconds>::duration(g, 40, 50.0);
            std::cout << time.count() << " nanoseconds." << std::endl;
        }

        void testExercise_02() {
            test_01();
            test_02();
            test_03();
            test_04();
            test_05();
            test_06();
        }
    }
}

void main_exercices_perfect_forwarding()
{
    using namespace Exercises_PerfectForwarding;
    Exercise_01::testExercise_01();
    Exercise_02::testExercise_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
