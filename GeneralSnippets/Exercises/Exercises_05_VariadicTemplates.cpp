// =====================================================================================
// Exercises_05_VariadicTemplates.cpp
// =====================================================================================

module modern_cpp_exercises:variadic_templates;

namespace Exercises_VariadicTemplates {

    namespace Exercise_01 {

        // =============================================================
        // Logical And - with variadic templates

        template<typename T>
        bool andAll(T cond) {
            return cond;
        }

        template<typename T, typename ... TRest>
        bool andAll(T cond, TRest ... conds) {
            return cond && andAll(conds...);
        }

        // or

        //bool andAll() {
        //    return true;
        //}
        //
        //template<typename T, typename ... TRest>
        //bool andAll(T cond, TRest... conds) {
        //    return cond && andAll(conds...);
        //}

        static void testExercise_01a() {

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

        template<typename T, typename... TRest>
        bool orAll(T cond, TRest ... conds) {
            return cond || orAll(conds...);
        }

        // or

        //bool orAll() {
        //    return false;
        //}

        //template<typename T, typename... TRest>
        //bool orAll(T cond, TRest... conds) {
        //    return cond || orAll(conds...);
        //}

        static void testExercise_01b() {

            bool result = orAll(false, true, false);
            std::cout << std::boolalpha << result << std::endl;

            result = orAll(false, false, false, false, false, false, false, false, false, false);
            std::cout << std::boolalpha << result << std::endl;
        }

        static void testExercise_01() {
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

        template<typename T1, typename T2, typename... TRest>
        bool sameType(T1 arg1, T2 arg2, TRest... args)
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

        static void testExercise_02() {

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
        T minimum(const T& t) {
            return t;
        }

        template <typename T, typename... TArgs>
        typename std::common_type<T, TArgs...>::type
        minimum(const T& first, const TArgs& ...rest)
        {
            using result_type = typename std::common_type<T, TArgs...>::type;
            return std::min(static_cast<result_type>(first), static_cast<result_type>(minimum(rest...)));
        }

        static void testExercise_03() {
            auto min1 = minimum(-7, 3.7f, 9u, -2.6);
            std::cout << "min1: " << min1 << std::endl;

            auto min2 = minimum(-7, 3.7f, 9u, -42.6);
            std::cout << "min2: " << min2 << std::endl;

            auto min3 = minimum(123, (short)456, (long)789);
            std::cout << "min3: " << min3 << std::endl;
        }
    }

    namespace Exercise_04 {

        template<typename Tuple, std::size_t N>
        struct ShowTupleImpl {
            static void print(const Tuple& t) {
                ShowTupleImpl<Tuple, N - 1>::print(t);
                std::cout << ", " << std::get<N - 1>(t);
            }
        };

        template<typename Tuple>
        struct ShowTupleImpl<Tuple, 1> {
            static void print(const Tuple& t) {
                std::cout << std::get<0>(t);
            }
        };

        template<typename... TArgs>
        void printTuple(const std::tuple<TArgs... >& t) {
            std::cout << "[";
            ShowTupleImpl<const std::tuple<TArgs...>&, sizeof...(TArgs)>::print(t);
            std::cout << "]" << std::endl;
        }

        template<typename... TArgs>
        void printTupleEx(const std::tuple<TArgs... >& t) {
            using tuple_type = const std::tuple<TArgs... >&;
            static const int tupleSize = sizeof...(TArgs);
            std::cout << "[";
            ShowTupleImpl<tuple_type, tupleSize>::print(t);
            std::cout << "]" << std::endl;
        }

        static void testExercise_04() {
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
            static constexpr int result = 0;
        };

        // ODER

        template <int N>
        class sum1<N>
        {
        public:
            static constexpr int result = N;
        };

        template <int N, int ... TRest>
        class sum1<N, TRest ...>
        {
        public:
            static constexpr int result = N + sum1<TRest ...>::result;
        };

        // =============================================================
        // b) 
        // Als Funktionsschablone:
        // Die Funktion hat einen oder mehrere Parameter.
        // Die Parameter werden über die Parameter Pack Expansion an
        // eine(mehrere) Funktion(en) übergeben, die vom Compiler generiert wird(werden).

        template <typename T>
        constexpr T sum2(T n)
        {
            return n;
        }

        template <typename T, typename  ... TRest>
        constexpr T sum2(T n, TRest ... r)
        {
            return n + sum2(r ...);
        }

        // =============================================================
        // c) 
        // Als Funktionsschablone:
        // Die Funktion hat *keinen* Parameter.
        // Dafür hat die Funktionsschablone einen oder mehrere Template Parameter.

        template<int X>
        constexpr int sum3()
        {
            return X;
        }

        template<int X, int Y, int...Z>
        constexpr int sum3()
        {
            return X + sum3<Y, Z...>();
        }

        // =============================================================
        // d)
        // Zwei weitere Realisierungen als Klassenschablone:
        // 
        // Unter Verwendung von Non-Type Parametern und ohne partielle Spezialisierung,
        // die Realisierung erzeugt ein 'std::initializer_list<>'-Objekt mit einem
        // anschließenden Aufruf von 'std::accumulate':

        template <int... TArgs>
        class sum4
        {
        public:
            // 'std::accumulate' cannot be called in an 'constexpr' context,
            // therefore applying type conversion operator
            // 
            // Note: Since C++20 std::accumulate is defined as follows:
            //   template< class InputIt, class T >
            //   constexpr T accumulate(InputIt first, InputIt last, T init);

            constexpr operator int() const
            {
                std::initializer_list<int> args = { TArgs ... };
                return std::accumulate(std::begin(args), std::end(args), 0);
            }
        };

        // =============================================================
        // Mit einem Folding-Konstrukt:

        template <int... TArgs>
        class sum5
        {
        public:
            static constexpr int result = ( ... + TArgs);
        };

        static void testExercise_05() {
            constexpr int result1 = sum1<1, 2, 3, 4, 5>::result;
            constexpr int result2 = sum2(1, 2, 3, 4, 5);
            constexpr int result3 = sum3<1, 2, 3, 4, 5>();
            constexpr int result4 = sum4<1, 2, 3, 4, 5>{};
            constexpr int result5 = sum5<1, 2, 3, 4, 5>::result;

            std::cout << result1 << std::endl;
            std::cout << result2 << std::endl;
            std::cout << result3 << std::endl;
            std::cout << result4 << std::endl;
            std::cout << result5 << std::endl;
        }
    }

    namespace Exercise_06 {

        template <typename... TBases>
        class X : public TBases ...
        {
        public:
            X(const TBases&... b) : TBases(b)...  {}
        };

        static void testExercise_06() {
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
}

void test_exercises_variadic_templates()
{
    using namespace Exercises_VariadicTemplates;
    Exercise_01::testExercise_01();
    Exercise_02::testExercise_02();
    Exercise_03::testExercise_03();
    Exercise_04::testExercise_04();
    Exercise_05::testExercise_05();
    Exercise_06::testExercise_06();
}

// =====================================================================================
// End-of-File
// =====================================================================================
