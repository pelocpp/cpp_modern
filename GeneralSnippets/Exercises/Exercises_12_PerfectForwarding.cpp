// =====================================================================================
// Exercises_12_PerfectForwarding.cpp
// =====================================================================================

module modern_cpp_exercises:perfect_forwarding;

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

        // Lösung zur Ergänzungsaufgabe:
        // Zweite alternative Realisierung mit std::initializer_list<T>

        template <typename ... T>
        void listExEx(T&& ... args)
        {
            std::initializer_list<int> { 
                (std::cout << std::forward<T>(args) << std::endl, int{}) ...
            };
        }

        template <typename ... T>
        void listExExEx(T&& ... args)
        {
            size_t count{};
            std::initializer_list<int> {
                (std::cout << ++count << ": " << std::forward<T>(args) << std::endl, int{}) ... 
            };
        }

        void test_06() {
            listExEx(100, 101, 102, 103, 104, 105);
            listExExEx(100, 101, 102, 103, 104, 105);
        }

        void test_07() {
            Point p{ 11, 12 };
            Point* pp = new Point{ 3, 4 };
            std::complex<double> c(2.5, 2.5);
            listExEx(c, 10, "abc", p, *pp, 2.4, Point{ 1, 2 });
            listExExEx(c, 10, "abc", p, *pp, 2.4, Point{ 1, 2 });
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
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }

        class ExecutionTimer
        {
        public:
            template <typename F, typename... Args>
            static std::chrono::milliseconds duration(F&& f, Args&&... args)
            {
                // Zeitmessung in Millisekunden
                std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
                auto tpStart = std::chrono::time_point_cast<std::chrono::milliseconds>(start);
                std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
                std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
                auto tpEnd = std::chrono::time_point_cast<std::chrono::milliseconds>(end);
                std::chrono::milliseconds diff = tpEnd - tpStart;
                return diff;
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

        void testExercise_02() {
            test_01();
            test_02();
        }
    }
}

void test_exercices_perfect_forwarding()
{
    using namespace Exercises_PerfectForwarding;
    Exercise_01::testExercise_01();
    Exercise_02::testExercise_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
