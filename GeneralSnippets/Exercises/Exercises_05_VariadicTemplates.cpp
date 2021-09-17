// =====================================================================================
// Exercices
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

namespace Exercises_VariadicTemplates {

    namespace Exercise_01 {

        // =============================================================
        // Logical And - with variadic templates

        template<typename T>
        bool andAll(T cond) {
            return cond;
        }

        template<typename T, typename... Ts>
        bool andAll(T cond, Ts... conds) {
            return cond && andAll(conds...);
        }

        // or

        //bool andAll() {
        //    return true;
        //}
        //
        //template<typename T, typename... Ts>
        //bool andAll(T cond, Ts... conds) {
        //    return cond && andAll(conds...);
        //}

        void testExercise_01a() {

            bool result = andAll(true, false, true);
            std::cout << std::boolalpha << result << std::endl;

            result = andAll(true, (1 > 2), true);
            std::cout << std::boolalpha << result << std::endl;

            result = andAll(true, true, true, true, true, true, true, true, true, true);
            std::cout << std::boolalpha << result << std::endl;
        }

        // =============================================================
        // Logical Or - with variadic templates

        template<typename T>
        bool orAll(T cond) {
            return cond;
        }

        template<typename T, typename... Ts>
        bool orAll(T cond, Ts... conds) {
            return cond || orAll(conds...);
        }

        // or

        //bool orAll() {
        //    return false;
        //}

        //template<typename T, typename... Ts>
        //bool orAll(T cond, Ts... conds) {
        //    return cond || orAll(conds...);
        //}

        void testExercise_01b() {

            bool result = orAll(false, true, false);
            std::cout << std::boolalpha << result << std::endl;

            result = orAll(false, false, false, false, false, false, false, false, false, false);
            std::cout << std::boolalpha << result << std::endl;
        }

        void testExercise_01() {
            testExercise_01a();
            testExercise_01b();
        }
    }

    namespace Exercise_02 {

        template<typename T1, typename T2>
        bool sameType(T1 arg1, T2 arg2)
        {
            std::cout << " # " << arg1 << ": " << typeid(arg1).name();
            std::cout << " - " << arg2 << ": " << typeid(arg2).name() << std::endl;

            return std::is_same<decltype(arg1), decltype(arg2)>::value;
            // or
            // return std::is_same_v<decltype(arg1), decltype(arg2)>;
            // or
            // return std::is_same<T1, T2>::value;
        }

        template<typename T1, typename T2, typename... TREST>
        bool sameType(T1 arg1, T2 arg2, TREST... args)
        {
            std::cout << " > " << arg1 << ": " << typeid(arg1).name();
            std::cout << " - " << arg2 << ": " << typeid(arg2).name() << std::endl;

            // Note: short-circuit-evaluation is considered !
            // Study output of program execution
            return std::is_same<decltype(arg1), decltype(arg2)>::value && sameType(arg2, args...);

            // Note: Due to order of expression evaluation short-circuit-evaluation cannot be considered !
            // Study output of program execution
            // return sameType(arg2, args...) && std::is_same<decltype(arg1), decltype(arg2)>::value;
        }

        void testExercise_02() {

            bool result;
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

        template <typename T>
        inline T minimum(const T& t) {
            return t;
        }

        template <typename T, typename ... TARGS>
        inline typename std::common_type<T, TARGS...>::type
            minimum(const T& t, const TARGS& ...p)
        {
            using result_type = typename std::common_type<T, TARGS...>::type;
            return std::min(static_cast<result_type>(t), static_cast<result_type>(minimum(p...)));
        }

        // oder etwas knapper

        //template <typename T>
        //inline T minimum(const T& t) { 
        //    return t; 
        //}

        //template <typename T, typename ... TARGS>
        //inline auto minimum(const T& t, const TARGS& ... p)
        //{
        //    using result_type = std::common_type_t<T, TARGS ...>;
        //    return std::min(static_cast<result_type>(t), static_cast<result_type>(minimum(p...)));
        //}

        void testExercise_03() {
            auto min1 = minimum(-7, 3.7f, 9u, -2.6);
            std::cout << "min1: " << min1 << ", type: " << typeid(min1).name() << std::endl;

            auto min2 = minimum(-7, 3.7f, 9u, -42.6);
            std::cout << "min2: " << min2 << ", type: " << typeid(min2).name() << std::endl;

            auto min3 = minimum(123, (short)456, (long)789);
            std::cout << "min3: " << min3 << ", type: " << typeid(min3).name() << std::endl;
        }
    }

    namespace Exercise_04 {

        template<typename TUPLE, std::size_t N>
        struct ShowTupleImpl {
            static void print(const TUPLE& t) {
                ShowTupleImpl<TUPLE, N - 1>::print(t);
                std::cout << ", " << std::get<N - 1>(t);
            }
        };

        template<typename TUPLE>
        struct ShowTupleImpl<TUPLE, 1> {
            static void print(const TUPLE& t) {
                std::cout << std::get<0>(t);
            }
        };

        template<typename ... TARGS>
        void printTuple(const std::tuple<TARGS ...>& t) {
            std::cout << "[";
            ShowTupleImpl<const std::tuple<TARGS...>&, sizeof...(TARGS)>::print(t);
            std::cout << "]" << std::endl;
        }

        template<typename ... TARGS>
        void printTupleEx(const std::tuple<TARGS ...>& t) {
            using tuple_type = const std::tuple<TARGS ...>&;
            static const int tuple_size = sizeof...(TARGS);
            std::cout << "[";
            ShowTupleImpl<tuple_type, tuple_size>::print(t);
            std::cout << "]" << std::endl;
        }

        void testExercise_04() {
            auto tuple1 = std::make_tuple(1, std::string("Modern C++"), false, 3.14159);
            auto tuple2 = std::make_tuple(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
            auto tuple3 = std::make_tuple(12345);

            printTuple(tuple1);
            printTuple(tuple2);
            printTuple(tuple3);

            printTupleEx(tuple1);
            printTupleEx(tuple2);
            printTupleEx(tuple3);
        }
    }

    namespace Exercise_05 {

        // =============================================================
        // a)
        // Als Klassenschablone:
        // Unter Verwendung von Non-Type Parametern und von partieller Spezialisierung

        template <int...>
        class sum1;

        template <>
        class sum1<>
        {
        public:
            static constexpr long result = 0;
        };

        // ODER

        template <int N>
        class sum1<N>
        {
        public:
            static constexpr long result = N;
        };

        template <int N, int ... REST>
        class sum1<N, REST ...>
        {
        public:
            static constexpr long result = N + sum1<REST ...>::result;
        };

        // =============================================================
        // b) 
        // Als Funktionsschablone:
        // Die Funktion hat einen oder mehrere Parameter.
        // Die Parameter werden über die Parameter Pack Expansion an
        // eine(mehrere) Funktion(en) übergeben, die vom Compiler generiert wird(werden).

        template <typename T>
        T sum2(T n)
        {
            return n;
        }

        template <typename T, typename  ... TREST>
        T sum2(T n, TREST ... r)
        {
            return n + sum2(r ...);
        }

        // =============================================================
        // c) 
        // Als Funktionsschablone:
        // Die Funktion hat *keinen* Parameter.
        // Dafür hat die Funktionsschablone einen oder mehrere Template Parameter.

        template<int X>
        int sum3()
        {
            return X;
        }

        template<int X, int Y, int...Z>
        int sum3()
        {
            return X + sum3<Y, Z...>();
        }

        void testExercise_05() {
            int result1 = sum1<1, 2, 3, 4, 5>::result;
            int result2 = sum2(1, 2, 3, 4, 5);
            int result3 = sum3<1, 2, 3, 4, 5>();

            std::cout << result1 << std::endl;
            std::cout << result2 << std::endl;
            std::cout << result3 << std::endl;
        }
    }

    namespace Exercise_06 {

        template <typename ... Bases>
        class X : public Bases ...
        {
        public:
            X(const Bases& ... b) : Bases(b)...  {}
        };

        void testExercise_06() {
            X o1{};

            X<std::string> o2{ "ABCDEF" };
            std::cout << o2.size() << std::endl;  // size is same as length

            X<std::string, std::vector<std::string>> o3{ "ABCDEF", { "123", "456" } };

            std::cout << o3.length() << std::endl;
            std::cout << o3.std::vector<std::string>::size() << std::endl;        // (1)
            std::cout << o3.std::string::size() << std::endl;                     // (2)
            // std::cout << o3.size() << std::endl;        // ambiguous access of 'size'
        }

        // Output:
        // 6
        // 6
        // 2
        // 6
    }

    namespace Exercise_07 {

        template<typename... ARGS>
        size_t totalLength(const ARGS& ... args)
        {
            size_t len{};
            for (auto s : { args ... }) {
                len += s.size();
            }
            return len;
        }

        void testExercise_07_a()
        {
            const std::string s1{ "111" };
            const std::string s2{ "AAAAA" };
            const std::string s3{ "!!!" };

            size_t len{ totalLength(s1, s2, s3) };
            std::cout << len << std::endl;
        }

        void testExercise_07_b() 
        {
            const std::string cs{ "11111" };
            const std::string& csr{ cs };
            std::string s{ "333" };

            size_t len{ totalLength(cs, std::string{ "2" }, csr, s) };
            std::cout << len << std::endl;
        }

        void testExercise_07() {
            testExercise_07_a();
            testExercise_07_b();
        }
    }
}

void test_exercises_variadic_templates()
{
    using namespace Exercises_VariadicTemplates;
    //Exercise_01::testExercise_01();
    //Exercise_02::testExercise_02();
    //Exercise_03::testExercise_03();
    //Exercise_04::testExercise_04();
    //Exercise_05::testExercise_05();
    //Exercise_06::testExercise_06();
    Exercise_07::testExercise_07();
}

// =====================================================================================
// End-of-File
// =====================================================================================
