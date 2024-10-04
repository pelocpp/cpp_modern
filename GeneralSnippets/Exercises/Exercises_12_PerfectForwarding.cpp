// =====================================================================================
// Exercises_12_PerfectForwarding.cpp
// =====================================================================================

module modern_cpp_exercises:perfect_forwarding;

namespace Exercises_PerfectForwarding {

    namespace Exercise_01
    {
        struct Point
        {
            int m_x;
            int m_y;
        };
    }
}

namespace std
{
    using namespace Exercises_PerfectForwarding::Exercise_01;

    // formatter for struct Point
    template<>
    struct std::formatter<Point> {
        constexpr auto parse(std::format_parse_context& ctx) {
            return ctx.begin();
        }

        auto format(const Point& pt, std::format_context& ctx) const {

            return
                std::format_to(ctx.out(), "[{},{}]", pt.m_x, pt.m_y);
        }
    };

    // formatter for std::complex
    template<typename U>
    struct std::formatter<std::complex<U>> {
        constexpr auto parse(std::format_parse_context& ctx) {
            return ctx.begin();
        }

        auto format(const std::complex<U>& c, std::format_context& ctx) const {

            return
                std::format_to(ctx.out(), "[{},{}]", c.real(), c.imag());
        }
    };
}

namespace Exercises_PerfectForwarding {

    namespace Exercise_01 {

        template <typename T>
        void list(T&& value)
        {
           std::println("{}", std::forward<T>(value));
        }

        template <typename T, typename ... TREST>
        void list(T&& first, TREST&& ... rest)
        {
            std::println("{}", std::forward<T>(first));
            list(std::forward<TREST>(rest)...);
        }

        static void test_01()
        {
            int n{ 123 };
            const double Pi{ 3.14 };

            list(10, "abc", n, Pi, 2.4, std::string{ "ABC" }, 99.99f);
        }

        static void test_02()
        {
            Point p{ 11, 12 };
            Point* pp = new Point{ 3, 4 };
            std::complex<double> c{ 2.5, 3.5 };

            list(c, 10, "abc", p, *pp, 2.4, Point{ 1, 2 });

            delete pp;
        }

        // Lösung zur Ergänzungsaufgabe:
        template <typename T>
        void print(int index, T&& value)
        {
            std::println("{}: {}", index, std::forward<T>(value));
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

        static void test_03() {
            int n = 123;
            const double pi = 3.14;
            listEx(10, "abc", n, pi, 2.4, std::string("ABC"), 99.99f);
        }

        static void test_04() {
            Point p{ 11, 12 };
            Point* pp = new Point{ 3, 4 };
            std::complex<double> c(2.5, 2.5);

            listEx(c, 10, "abc", p, *pp, 2.4, Point{ 1, 2 });

            delete pp;
        }

        static void test_05() {
            listEx(10, 11, 12, 13, 14);
        }

        // Lösung zur Ergänzungsaufgabe:
        // Zweite alternative Realisierung mit std::initializer_list<T>

        template <typename ... T>
        void listExEx(T&& ... args)
        {
            std::initializer_list<int>
            { 
                (std::println("{}", std::forward<T>(args)), int{}) ...
            };
        }

        template <typename ... T>
        void listExExEx(T&& ... args)
        {
            size_t count{};
            std::initializer_list<int>
            {
                (std::println("{}: {}", ++count, std::forward<T>(args)), int{}) ...
            };
        }

        static void test_06() {
            listExEx(100, 101, 102, 103, 104, 105);
            listExExEx(100, 101, 102, 103, 104, 105);
        }

        static void test_07() {
            Point p{ 11, 12 };
            Point* pp = new Point{ 3, 4 };
            std::complex<double> c(2.5, 2.5);

            listExEx(c, 10, "abc", p, *pp, 2.4, Point{ 1, 2 });
            listExExEx(c, 10, "abc", p, *pp, 2.4, Point{ 1, 2 });

            delete pp;
        }

        static void testExercise_01() {
            test_01();
            test_02();
            test_03();
            test_04();
            test_05();
            test_06();
            test_07();
        }
    }

    namespace Exercise_02 {

        static void f()
        {
            // simulate some work (function without parameters)
            std::println("calling f");
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        static void g(int a, double b)
        {
            // simulate some work (function with parameters)
            std::println("calling g with parameters {} and {}", a, b);
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }

        class ExecutionTimer
        {
        public:
            template <typename F, typename... Args>
            static std::chrono::milliseconds duration(F&& f, Args&&... args)
            {
                // Zeitmessung in Millisekunden
                std::chrono::system_clock::time_point start{ std::chrono::system_clock::now() };
                auto tpStart{ std::chrono::time_point_cast<std::chrono::milliseconds>(start) };
                std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
                std::chrono::system_clock::time_point end{ std::chrono::system_clock::now() };
                auto tpEnd{ std::chrono::time_point_cast<std::chrono::milliseconds>(end) };
                std::chrono::milliseconds diff = tpEnd - tpStart;
                return diff;
            }
        };

        static void test_01() {
            std::chrono::milliseconds time{ ExecutionTimer::duration(f) };
            std::println("{} msecs.", time.count());
        }

        static void test_02() {
            std::chrono::milliseconds time{ ExecutionTimer::duration(g, 10, 20.0) };
            std::println("{} msecs.", time.count());
        }

        static void testExercise_02() {
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
