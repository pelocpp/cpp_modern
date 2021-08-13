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

namespace Exercises {

    namespace Exercise_01 {

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

        void testExercise_01() {
            auto min1 = minimum(-7, 3.7f, 9u, -2.6);
            std::cout << "min1: " << min1 << ", type: " << typeid(min1).name() << std::endl;

            auto min2 = minimum(-7, 3.7f, 9u, -42.6);
            std::cout << "min2: " << min2 << ", type: " << typeid(min2).name() << std::endl;

            auto min3 = minimum(123, (short)456, (long)789);
            std::cout << "min3: " << min3 << ", type: " << typeid(min3).name() << std::endl;
        }
    }

    namespace Exercise_02 {

#define SOLUTION 

        class HugeArray {
        private:
            size_t m_len;
            int* m_data;

        public:
            HugeArray();        // default c'tor
            HugeArray(size_t);  // user-defined c'tor
            ~HugeArray();       // d'tor

            // copy semantics
            HugeArray(const HugeArray&);  // copy c'tor
            HugeArray& operator=(const HugeArray&);  // copy assignment

#if defined (SOLUTION)
        // move semantics
            HugeArray(HugeArray&&) noexcept;  // move c'tor
            HugeArray& operator= (HugeArray&&) noexcept; // move assignment
#endif
        };

        HugeArray::HugeArray() : m_len(0), m_data(nullptr) {
            std::cout << "default c'tor" << std::endl;
        }

        HugeArray::HugeArray(size_t len) : m_len(len), m_data(new int[len]) {
            std::cout << "c'tor (size_t):  " << len << " allocated" << std::endl;
        }

        HugeArray::~HugeArray() {
            std::cout << "d'tor:           " << m_len << " relased" << std::endl;
            delete[] m_data;
        }

        // copy semantics
        HugeArray::HugeArray(const HugeArray& other) {
            std::cout << "COPY c'tor:      " << other.m_len << " allocated" << std::endl;
            m_len = other.m_len;
            m_data = new int[other.m_len];
            std::copy(other.m_data, other.m_data + m_len, m_data);
        }

        HugeArray& HugeArray::operator=(const HugeArray& other) {
            std::cout << "COPY assignment: " << other.m_len << " assigned" << std::endl;
            if (this != &other) {
                delete[] m_data;
                m_len = other.m_len;
                m_data = new int[m_len];
                std::copy(other.m_data, other.m_data + m_len, m_data);
            }
            return *this;
        }

#if defined (SOLUTION)
        // move semantics
        HugeArray::HugeArray(HugeArray&& other) noexcept {  // move c'tor
            std::cout << "MOVE c'tor:      " << other.m_len << " allocated" << std::endl;
            m_data = other.m_data;   // shallow copy
            m_len = other.m_len;
            other.m_data = nullptr;  // reset source object, ownership has been moved
            other.m_len = 0;
        }

        HugeArray& HugeArray::operator= (HugeArray&& other) noexcept { // move-assignment
            std::cout << "MOVE assignment: " << other.m_len << " assigned" << std::endl;
            if (this != &other) {
                delete[] m_data;         // release left side
                m_data = other.m_data;   // shallow copy
                m_len = other.m_len;
                other.m_data = nullptr;  // reset source object, ownership has been moved
                other.m_len = 0;
            }
            return *this;
        }
#endif

        void testExercise_02() {
            std::cout << "Start:" << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<HugeArray> myVec;
            HugeArray bArray(10000000);
            HugeArray bArray2(bArray);
            myVec.push_back(bArray);   // <== std::move
            bArray = HugeArray(20000000);
            myVec.push_back(HugeArray(30000000));  // <== emplace_back (30000000)
            auto end = std::chrono::high_resolution_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds> (end - start);
            std::cout << "Done [" << diff.count() << " msecs]" << std::endl;
        }
    }

    namespace Exercise_03 {

        inline void even(const int val) {
            if (!(val % 2)) {
                std::cout << val << std::endl;
            }
        }

        struct Even {
            void operator()(const int val) {
                if (!(val % 2)) {
                    std::cout << val << std::endl;
                }
            }
        };

        void testExercise_03a() {
            std::vector<int> values(20);

            std::generate(
                std::begin(values),
                std::end(values),
                [count = 1]() mutable { return count++; }
            );

            // function
            std::for_each(std::begin(values), std::end(values), even);

            // lambda
            std::for_each(
                std::begin(values), 
                std::end(values), 
                [](int val) {
                    if (!(val % 2)) {
                        std::cout << val << std::endl;
                    }
                }
            );

            // functor
            std::for_each(std::begin(values), std::end(values), Even());
        }

        void testExercise_03b() {
            std::vector<int> values(20);

            std::generate(
                std::begin(values),
                std::end(values),
                [count = 1]() mutable { return count++; }
            );

            // 'divisor' defined within capture clause 
            std::for_each(
                std::begin(values), 
                std::end(values),
                [divisor = 3](int val) {
                    if (!(val % divisor)) {
                        std::cout << val << std::endl;
                    }
                }
            );
            std::cout << std::endl;

            // or 'divisor' defined in outer context (scope) 
            int divisor = 5;

            // capture context by value (reference & would work also)
            std::for_each(
                std::begin(values),
                std::end(values),
                [=](int val) {
                    if (!(val % divisor)) {
                        std::cout << val << std::endl;
                    }
                }
            );
        }

        void testExercise_03() {
            testExercise_03a();
            testExercise_03b();
        }
    }

    namespace Exercise_04 {

        std::map<char, std::function<double(double, double)>> createCalculator() {

            std::map<char, std::function<double(double, double)>> map;
            map.insert(std::make_pair('+', [](double a, double b) { return a + b; }));
            map.insert(std::make_pair('-', [](double a, double b) { return a - b; }));
            map.insert(std::make_pair('*', [](double a, double b) { return a * b; }));
            map.insert(std::make_pair('/', [](double a, double b) { return a / b; }));
            return map;
        }

        // or more compact

        std::map<char, std::function<double(double, double)>> createCalculatorEx() {

            std::map<char, std::function<double(double, double)>> map;
            map['+'] = [](double a, double b) { return a + b; };
            map['-'] = [](double a, double b) { return a - b; };
            map['*'] = [](double a, double b) { return a * b; };
            map['/'] = [](double a, double b) { return a / b; };
            return map;
        }

        // or still more compact

        std::map<char, std::function<double(double, double)>> createCalculatorExEx()
        {
            return {
                { '+', [](double a, double b) {return a + b; } },
                { '-', [](double a, double b) {return a - b; } },
                { '*', [](double a, double b) {return a * b; } },
                { '/', [](double a, double b) {return a / b; } }
            };
        }

        void testExercise_04a() {

            std::map<char, std::function<double(double, double)>> calculator = createCalculator();
            double op1, op2;
            char op;

            std::cout << "Enter first Operand: ";
            std::cin >> op1;
            std::cout << "Enter second Operand: ";
            std::cin >> op2;
            std::cout << "Enter operation (+, -, *, /): ";
            std::cin >> op;

            // do the math
            double result = calculator[op](op1, op2);
            std::cout << "Result: " << op1 << ' ' << op << ' ' << op2 << " = " << result << '.' << std::endl;
        };

        void testExercise_04b() {

            std::map<char, std::function<double(double, double)>> calculator = createCalculator();

            // do some math operations
            std::cout << "1.5 + 2.7 = " << calculator['+'](1.5, 2.7) << std::endl;
            std::cout << "1.5 - 2.7 = " << calculator['-'](1.5, 2.7) << std::endl;
            std::cout << "1.5 * 2.7 = " << calculator['*'](1.5, 2.7) << std::endl;
            std::cout << "1.5 / 2.7 = " << calculator['/'](1.5, 2.7) << std::endl;

            // add a new operation
            calculator.insert(std::make_pair('^', [](double a, double b) { return std::pow(a, b); }));
            std::cout << "1.5 ^ 2.5 = " << calculator['^'](1.5, 2.5) << std::endl;
        };

        void testExercise_04() {
            // testExercise_04a();  // needs console input
            testExercise_04b();
        }
    }

    namespace Exercise_05 {

        void testExercise_05a()
        {
            // Output:
            // Variable: 1
            // Variable: 2
            // Variable: 3
            // Variable: 1

            // When the lambda is called, the lambda captures a copy of @variable.
            // When the lambda decrements @variable from 1 to 2 and 3, it decrements its own copy, not the original value.
            // But: The original value of @variable is preserved across calls to the lambda!

            int variable{ 1 };

            auto lambda{ [variable]() mutable {
                std::cout << "Variable: " << variable << std::endl;
                variable++;
                }
            };

            // invoke lambda three times
            lambda();
            lambda();
            lambda();

            std::cout << "Variable: " << variable << std::endl << std::endl;
        }

        void testExercise_05b()
        {
            // Output:
            // 10
            // 11
            // 12
            // 13
            // 14
            // 15
            // 16
            // 17
            // 15

            auto L = [val = 10]() mutable { std::cout << val++ << std::endl; };
            L();
            L();
            L();
            L();
            L();
            auto LC = L;
            LC();
            LC();
            LC();
            L();
        }

        void testExercise_05c()
        {
            // Output:
            // 1
            // 2
            // 2

            // Rather than printing 1, 2, 3, the code prints 2 twice. When we created @otherCount as a copy of @count,
            // we created a copy of @count in its current state. @count‘s i was 1, so @otherCount‘s i is 1 as well.
            // Since @otherCount is a copy of @count, they each have their own @i.

            int i{ };

            // create a lambda named 'count'
            auto count{ [i]() mutable { std::cout << ++i << std::endl; } };

            // invoke lambda
            count();

            // create a copy of lambda 'count'
            auto otherCount{ count };

            // invoke both lambda 'count' and the copy
            count();
            otherCount();
            std::cout << std::endl;
        }

        void invoke(const std::function<void(void)>& fn)
        {
            fn();
        }

        void testExercise_05d()
        {
            // Output:
            // 1
            // 1
            // 1

            // This exhibits the same problem as the prior example in a more obscure form:
            // When std::function is created with a lambda, 
            // the std::function internally makes a copy of the lambda object.
            // Thus, the call to fn() is actually being executed on the copy of our lambda, not the actual lambda.

            // See also:
            // https://stackoverflow.com/questions/23515058/creating-stdfunction-with-lambda-causes-superfluous-copying-of-the-lambda-obje

            int i{ };

            // increments and prints its local copy of @i
            auto count{ [i]() mutable { std::cout << ++i << std::endl; } };

            invoke(count);
            invoke(count);
            invoke(count);
            std::cout << std::endl;
        }

        void testExercise_05()
        {
            testExercise_05a();
            testExercise_05b();
            testExercise_05c();
            testExercise_05d();
        }
    }

    namespace Exercise_06 {

        std::optional<int> toInt(std::string s) {
            std::optional<int> result;
            try
            {
                int i = std::stoi(s);

                // want input string to be consumed entirely (there are several ways
                // to accomplish this each with advantages and disadvantages)
                std::string tmp = std::to_string(i);
                if (tmp.length() != s.length())
                    throw std::invalid_argument("input string illegal");

                result.emplace(i);
            }
            catch (std::invalid_argument const&)
            {
                std::cerr << "Bad input: std::invalid_argument" << std::endl;
            }
            catch (std::out_of_range const&)
            {
                std::cerr << "Integer overflow: std::out_of_range" << std::endl;
            }

            return result;
        }

        template <typename T>
        std::optional<T> toNumber(std::string s) {
            std::optional<T> result;
            try
            {
                if constexpr (std::is_same_v<T, int> || std::is_same_v<T, short>) {
                    int i = std::stoi(s);
                    std::string tmp = std::to_string(i);
                    if (tmp.length() != s.length())
                        throw std::invalid_argument("input string illegal");

                    result.emplace(i);
                }
                if constexpr (std::is_same_v<T, long>) {
                    long l = std::stol(s);
                    std::string tmp = std::to_string(l);
                    if (tmp.length() != s.length())
                        throw std::invalid_argument("input string illegal");

                    result.emplace(l);
                }
                if constexpr (std::is_same_v<T, long long>) {
                    long long ll = std::stoll(s);
                    std::string tmp = std::to_string(ll);
                    if (tmp.length() != s.length())
                        throw std::invalid_argument("input string illegal");

                    result.emplace(ll);
                }
            }
            catch (std::invalid_argument const&)
            {
                std::cerr << "Bad input: std::invalid_argument" << std::endl;
            }
            catch (std::out_of_range const&)
            {
                std::cerr << "Integer overflow: std::out_of_range" << std::endl;
            }

            return result;
        }

        void testExercise_06a() {
            std::optional<int> i1 = toInt("123");
            if (i1.has_value()) {
                std::cout << i1.value() << std::endl;
            }

            std::optional<int> i2 = toInt("-987654321");
            if (i2.has_value()) {
                std::cout << i2.value() << std::endl;
            }

            std::optional<int> i3 = toInt("123ABC");
            if (i3.has_value()) {
                std::cout << i3.value() << std::endl;
            }

            std::optional<int> i4 = toInt("ABC123");
            if (i4.has_value()) {
                std::cout << i4.value() << std::endl;
            }
        }

        void testExercise_06b() {

            std::optional<short> i1 = toNumber<short>("32767");
            if (i1.has_value()) {
                std::cout << i1.value() << std::endl;
            }

            std::optional<int> i2 = toNumber<int>("2147483647");
            if (i2.has_value()) {
                std::cout << i2.value() << std::endl;
            }

            std::optional<long int> i3 = toNumber<long int>("2147483647");
            if (i3.has_value()) {
                std::cout << i3.value() << std::endl;
            }

            std::optional<long long> i4 = toNumber<long long>("9223372036854775807");
            if (i4.has_value()) {
                std::cout << i4.value() << std::endl;
            }
        }

        void testExercise_06() {
            testExercise_06a();
            testExercise_06b();
        }
    }

    namespace Exercise_07 {

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

        void testExercise_07() {
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

    namespace Exercise_08 {

        template<long long n>
        struct FibImpl {
            static constexpr long long value =
                FibImpl<n - 1>::value + FibImpl<n - 2>::value;
        };

        template<>
        struct FibImpl<1> {
            static constexpr long long value = 1;
        };

        template<>
        struct FibImpl<0> {
            static constexpr long long value = 0;
        };

        template<long long n>
        struct Fibonacci {
            static_assert(n >= 0, "Error: Fibonacci can't be called with a negative integer");
            static constexpr long long value = FibImpl<n>::value;
        };

        void testExercise_08() {
            std::cout << 1 << ":  " << Fibonacci<1>::value << std::endl;
            std::cout << 2 << ":  " << Fibonacci<2>::value << std::endl;
            std::cout << 10 << ": " << Fibonacci<10>::value << std::endl;
            std::cout << 20 << ": " << Fibonacci<20>::value << std::endl;
            std::cout << 30 << ": " << Fibonacci<30>::value << std::endl;
            std::cout << 40 << ": " << Fibonacci<40>::value << std::endl;
            std::cout << 50 << ": " << Fibonacci<50>::value << std::endl;
            std::cout << 60 << ": " << Fibonacci<60>::value << std::endl;
            std::cout << 70 << ": " << Fibonacci<70>::value << std::endl;
            std::cout << 80 << ": " << Fibonacci<80>::value << std::endl;
            std::cout << 90 << ": " << Fibonacci<90>::value << std::endl;
            std::cout << 92 << ": " << Fibonacci<92>::value << std::endl;
        }
    }

    namespace Exercise_09 {

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

        void testExercise_09() {
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

    namespace Exercise_10 {

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

        void testExercise_10_a() {

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

        void testExercise_10_b() {

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

        void testExercise_10() {
            testExercise_10_a();
            testExercise_10_b();
        }
    }

    namespace Exercise_11 {

        template <typename T>
        class MyContainer {
        private:
            std::vector<T> m_data;

        public:
            MyContainer() = default;

            MyContainer(const T& d1, const T& d2) {
                std::cout << "c'tor (const T&, const T&)" << std::endl;
                m_data.push_back(d1);
                m_data.push_back(d2);
            }

            MyContainer(std::initializer_list<T> data) : m_data(data) {
                std::cout << "c'tor (std::initializer_list<T>)" << std::endl;
            }

            void operator()() {
                std::cout << "  [";
                for (auto data : m_data) {
                    std::cout << data << ' ';
                }
                std::cout << ']' << std::endl;
            }
        };

        void testExercise_11() {
            // using MyContainer with int
            MyContainer<int> container1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            container1();

            // using MyContainer with std::string
            MyContainer<std::string> container2{ "range", "-", "based", "for", "loop" };
            container2();

            MyContainer<int> container3;
            container3();
            MyContainer<int> container4{};
            container4();
            MyContainer<int> container5(1, 2);
            container5();
            MyContainer<int> container6{ 1, 2 };
            container6();
        }
    }

    namespace Exercise_12 {

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

        void testExercise_12a() {

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

        void testExercise_12b() {

            bool result = orAll(false, true, false);
            std::cout << std::boolalpha << result << std::endl;

            result = orAll(false, false, false, false, false, false, false, false, false, false);
            std::cout << std::boolalpha << result << std::endl;
        }

        void testExercise_12() {
            testExercise_12a();
            testExercise_12b();
        }
    }

    namespace Exercise_13 {

        // =============================================================
        // Logical And - with folding expression

        template<typename ...Args>
        bool andAll(Args ...args) {
            return (args && ... && true);  // binary right fold (init == true)
        }

        void testExercise_13a() {

            bool result = andAll(true, (1 > 2), true);
            std::cout << std::boolalpha << result << std::endl;

            result = andAll(true, true, true);
            std::cout << std::boolalpha << result << std::endl;
        }

        // =============================================================
        // Logical Or - with folding expression

        template<typename ...Args>
        bool orAll(Args ...args) {
            return (args || ...);  // unary right fold
        }

        void testExercise_13b() {

            bool result = orAll(false, false, true);
            std::cout << std::boolalpha << result << std::endl;

            result = orAll(false, false, false, false, false);
            std::cout << std::boolalpha << result << std::endl;
        }

        void testExercise_13() {
            testExercise_13a();
            testExercise_13b();
        }
    }

    namespace Exercise_14 {

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

        void testExercise_14() {

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

    namespace Exercise_15 {

        // Beachte:
        // Bei Anwendung eines Folding Expression wird nach dem "Ausrollen" des Folding Ausdrucks
        // das 1. mit dem 2., das 1. mit dem 3., das 1. mit dem 4. Element usw. verglichen. 
        // Beim Lösungsansatz mit variadischen Templates wird
        // das 1. mit dem 2., das 2. mit dem 3., das 3. mit dem 4. Element usw. verglichen!

        template<typename T, typename... TREST>
        constexpr bool sameType(T arg, TREST... args)
        {
            // since C++17: folding expression !
            return (std::is_same_v<decltype(arg), decltype(args)> && ...);
        }

        void testExercise_15() {

            bool result;
            result = sameType(1, 2, 3, 4, '?', 6, 7, 8, 9);
            std::cout << std::boolalpha << result << std::endl;

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

    namespace Exercise_16 {

        // -------------------------------------------------------------------------------------
        // Teilaufgabe 1:
        // -------------------------------------------------------------------------------------
        // a) Es werden entweder Iteratoren oder Container an die Funktionen übergeben
        // b) Beim sogenannten "Pipe-Lining", also verschachteltetem Aufrufen der jeweiligen Funktionen
        //    ist man bei der zweiten Variante etwas flexibler

        // -------------------------------------------------------------------------------------
        // Teilaufgabe 2:
        // -------------------------------------------------------------------------------------
        // Zu Beispiel wie folgt:
        // Der übersetzungsfähige Quellcode stammt aus der Datei 'FunctionalProgramming01.cpp':
        // Hier sind alle 'include'-Dateien und Definitionen der 'map'-Funktion vorhanden.

        //void test_functional_map_02e() {

        //    std::vector<std::string> words = {
        //        std::string("one"),
        //        std::string("two"),
        //        std::string("three")
        //    };

        //    std::for_each(std::begin(words), std::end(words), [](const std::string& word) {
        //        std::cout << word << ' ';
        //        });
        //    std::cout << std::endl;

        //    auto result = map(
        //        std::begin(words),
        //        std::end(words),
        //        [](std::string word) {
        //            // convert std::string to upper case
        //            std::transform(std::begin(word), std::end(word), std::begin(word), std::toupper);
        //            return word;
        //        }
        //    );

        //    std::for_each(std::begin(result), std::end(result), [](std::string s) {
        //        std::cout << s << ' ';
        //        }
        //    );
        //    std::cout << std::endl;
        //}
    }

    namespace Exercise_17 {

        template <typename TReturn, typename InputIterator, typename TFunctor>
        auto fold(InputIterator begin, InputIterator end, TFunctor&& lambda)
            // not needed, just for demonstration purposes
            -> TReturn
        {
            TReturn init{};

            return std::accumulate(begin, end, init, std::forward<TFunctor>(lambda));
        }

        template <typename InputIterator, typename TFunctor>
        auto foldEx(InputIterator begin, InputIterator end, TFunctor&& lambda)
            // REQUIRED
            -> decltype(lambda(
                std::declval<typename std::iterator_traits<InputIterator>::value_type >(),
                std::declval<typename std::iterator_traits<InputIterator>::value_type >()))
        {
            using TReturn = 
                decltype(lambda(
                    std::declval<typename std::iterator_traits<InputIterator>::value_type >(),
                    std::declval<typename std::iterator_traits<InputIterator>::value_type >())
                    );

            TReturn init{};

            return std::accumulate(begin, end, init, std::forward<TFunctor>(lambda));
        }

        void test_fold_01()
        {
            std::vector<int> numbers { 1, 2, 3, 4, 5, 6, 7, 8 };

            std::string concatenated = fold<std::string>(
                std::begin(numbers),
                std::end(numbers),
                [](std::string s, int n) -> std::string {
                    return s + std::to_string(n); 
                }

                // oder 
                // [](auto n, auto m) -> std::string {
                //    return n + std::to_string(m);
                // }
            );

            std::cout << concatenated << std::endl;
        }

        void test_fold_02()
        {
            std::vector<int> numbers{ 8, 7, 6, 5, 4, 3, 2, 1 };

            std::string concatenated = foldEx(
                std::begin(numbers),
                std::end(numbers),
                [](auto n, int m) -> std::string {
                    return n + std::to_string(m);
                }
            );

            std::cout << concatenated << std::endl;
        }

        void testExercise_17() {
            test_fold_01();
            test_fold_02();
        }
    }

    namespace Exercise_18 {

        // https://gieseanw.wordpress.com/2017/05/03/a-true-heterogeneous-container-in-c/

        void testExercise_18a()
        {
            std::variant<int, std::string> myVariant;
            myVariant = 123;
            std::cout << std::get<int>(myVariant) << std::endl;
            myVariant = std::string("456");
            std::cout << std::get<std::string>(myVariant) << std::endl;
        }

        struct MyPrintVisitor
        {
            void operator()(const int& value) { std::cout << "int: " << value << std::endl; }
            void operator()(const std::string& value) { std::cout << "std::string: " << value << std::endl; }
        };

        // oder

        struct AllInOneVisitor
        {
            template <class T>
            void operator()(const T& value) { std::cout << value << std::endl; }
        };

        // oder

        struct MyModifyingVisitor
        {
            template <class T>
            void operator()(T& value) { value += value; }
        };

        auto lambdaAllInOneVisitor = [](const auto& value) {
            std::cout << value << std::endl;
        };

        void testExercise_18b()
        {
            std::variant<int, std::string> myVariant;
            myVariant = 123;
            std::visit(MyPrintVisitor{}, myVariant);
            myVariant = std::string("456");
            std::visit(MyPrintVisitor{}, myVariant);

            myVariant = 123;
            std::visit(AllInOneVisitor{}, myVariant);
            myVariant = std::string("456");
            std::visit(AllInOneVisitor{}, myVariant);

            myVariant = 123;
            std::visit(lambdaAllInOneVisitor, myVariant);
            myVariant = std::string("456");
            std::visit(lambdaAllInOneVisitor, myVariant);

            myVariant = 123;
            std::visit(MyModifyingVisitor{}, myVariant);
            std::visit(MyPrintVisitor{}, myVariant);
            myVariant = std::string("456");
            std::visit(MyModifyingVisitor{}, myVariant);
            std::visit(MyPrintVisitor{}, myVariant);
        }

        void testExercise_18c()
        {
            std::vector<std::variant<int, std::string>> hetVec;

            hetVec.emplace_back(12);
            hetVec.emplace_back(std::string("34"));
            hetVec.emplace_back(56);
            hetVec.emplace_back(std::string("78"));

            // print them
            for (const auto& var : hetVec) {
                std::visit(MyPrintVisitor{}, var);
            }

            // modify them
            for (auto& var : hetVec) {
                std::visit(MyModifyingVisitor{}, var);
            }

            // print them again
            for (const auto& var : hetVec) {
                std::visit(MyPrintVisitor{}, var);
            }
        }

        template <typename... T>
        class HeterogeneousContainer
        {
        private:
            std::vector<std::variant<T...>> m_values;

        public:
            // visitor
            template <class V>
            void visit(V&& visitor) {
                for (auto& value : m_values) {
                    std::visit(visitor, value);
                }
            }

            // accessor
            std::vector<std::variant<T...>>& Values() {
                return m_values;
            };
        };

        void testExercise_18d()
        {
            HeterogeneousContainer<int, std::string> hetCont;

            hetCont.Values().emplace_back(12);
            hetCont.Values().emplace_back(std::string("34"));
            hetCont.Values().emplace_back(56);
            hetCont.Values().emplace_back(std::string("78"));

            // print them
            hetCont.visit(lambdaAllInOneVisitor);
            std::cout << std::endl;

            // modify them
            hetCont.visit(MyModifyingVisitor{});

            // print again
            hetCont.visit(lambdaAllInOneVisitor);
            std::cout << std::endl;
        }

        void testExercise_18() {
            testExercise_18a();
            testExercise_18b();
            testExercise_18c();
            testExercise_18d();
        }
    }

    namespace Exercise_19 {

        using Clock = std::chrono::high_resolution_clock;
        constexpr long MaxIterations = 10000;
        constexpr bool Verbose = false;
        constexpr int Width = 400;
        constexpr int Height = 400;

        // classical approach: base class for image types
        class Image {
        protected:
            long m_width;
            long m_height;

        public:
            // c'tor
            Image(int width, int height) : m_width{ width }, m_height{ height } {}

        public:
            // public interface
            virtual void draw() = 0;
            virtual void drawPixel(int position) = 0;
            virtual long getNumPixels() = 0;
        };

        class PngImage : public Image {
        private:
            long m_numPixels;
            long m_currPixel;

        public:
            PngImage() : Image{ 0, 0 }, m_currPixel(0) { setNumPixels(); }
            PngImage(int width, int height) : Image{ width, height } { setNumPixels(); }

            virtual void draw() override {
                // just to prevent optimizer to optimize "too much" some sloppy stuff
                m_currPixel = 0;
                int numPixels = getNumPixels();
                int currPosition = getCurrPixel();
                while (currPosition != numPixels) {
                    drawPixel(currPosition);
                    incCurrPixel();
                    currPosition = getCurrPixel();
                }
            }

            virtual void drawPixel(int position) override {
                if (Verbose) {
                    std::cout << "draw pixel at position " << position << std::endl;
                }
            }

            virtual long getNumPixels() override {
                return m_numPixels;
            }

        private:
            // private helper methods
            void setNumPixels() {
                m_numPixels = m_width * m_height;
            }

            long getCurrPixel() {
                return m_currPixel;
            }

            void incCurrPixel() {
                m_currPixel++;
            }
        };

        // driver code for classical polymorphism benchmark
        void testExercise_19a_classic_benchmark()
        {
            std::cout << "Classical Polymorphism Benchmark: " << std::endl;

            Image* pImage = new PngImage(Width, Height);

            auto start = Clock::now();

            // call draw several times to make sure performance is visible 
            for (int i = 0; i < MaxIterations; ++i) {
                pImage->draw();
            }

            long pixels = pImage->getNumPixels();
            std::cout << "Pixels: " << pixels << std::endl;

            auto end = Clock::now();
            std::cout << "Time taken: "
                << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                << " microseconds" << std::endl;
        }

        // CRTP approach: base class for all image types.
        // The template parameter T is used to specify the type
        // of a derived class pointed to by a pointer 
        template <class T>
        class ImageCRTP {
        protected:
            long m_width;
            long m_height;

        public:
            // c'tor
            ImageCRTP(int width, int height) : m_width{ width }, m_height{ height } {}

            void draw() {
                static_cast<T*>(this)->draw();  // dispatch call to exact type 
            }

            void drawPixel(int position) {
                return static_cast<T*>(this)->drawPixel(position);
            }

            long getNumPixels() {
                return static_cast<T*>(this)->getNumPixels();
            }
        };

        class PngImageCRTP : public ImageCRTP<PngImageCRTP> {
        private:
            long m_numPixels;
            long m_currPixel;

        public:
            PngImageCRTP() : ImageCRTP{ 1, 1 }, m_currPixel(0) { setNumPixels(); }
            PngImageCRTP(int width, int height) : ImageCRTP{ width, height } { setNumPixels(); }

            void draw() {
                // just to prevent optimizer to optimize "too much" some sloppy stuff
                m_currPixel = 0;
                int numPixels = getNumPixels();
                int currPosition = getCurrPixel();
                while (currPosition != numPixels) {
                    drawPixel(currPosition);
                    incCurrPixel();
                    currPosition = getCurrPixel();
                }
            }

            void drawPixel(int position) {
                if (Verbose) {
                    std::cout << "draw pixel at position " << position << std::endl;
                }
            }

            long getNumPixels() {
                return m_numPixels;
            }

        private:
            // private helper methods
            void setNumPixels() {
                m_numPixels = m_width * m_height;
            }

            long getCurrPixel() {
                return m_currPixel;
            }

            void incCurrPixel() {
                m_currPixel++;
            }
        };

        // driver code for CRTP benchmark
        void testExercise_19a_crtp_benchmark()
        {
            std::cout << "CRTP Benchmark: " << std::endl;

            ImageCRTP<PngImageCRTP>* pImage = new PngImageCRTP(Width, Height);

            auto start = Clock::now();

            // call draw several times to make sure performance is visible 
            for (int i = 0; i < MaxIterations; ++i) {
                pImage->draw();
            }

            long pixels = pImage->getNumPixels();
            std::cout << "Pixels: " << pixels << std::endl;

            auto end = Clock::now();
            std::cout << "Time taken: "
                << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                << " microseconds" << std::endl;
        }

        void testExercise_19() {
            testExercise_19a_classic_benchmark();
            testExercise_19a_crtp_benchmark();
        }
    }

    namespace Exercise_20 {

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

        void testExercise_20() {
            int result1 = sum1<1, 2, 3, 4, 5>::result;
            int result2 = sum2(1, 2, 3, 4, 5);
            int result3 = sum3<1, 2, 3, 4, 5>();

            std::cout << result1 << std::endl;
            std::cout << result2 << std::endl;
            std::cout << result3 << std::endl;
        }
    }

    namespace Exercise_21 {

        template <typename ... Bases>
        class X : public Bases ...
        {
        public:
            X(const Bases& ... b) : Bases(b)...  {}
        };

        void testExercise_21() {
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

    namespace Exercise_22 {

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


        void testExercise_22() {
            //test_01();
            //test_02();
            //test_03();
            //test_04();
            //test_05();

            //test_06();
            test_07();
        }
    }

    namespace Exercise_23 {

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

        void testExercise_23() {
            test_01();
            test_02();
            test_03();
            test_04();
            test_05();
            test_06();
        }
    }

    namespace Exercise_24 {

        bool andAll(std::initializer_list<bool> vec) {

            return std::accumulate(
                std::begin(vec),
                std::end(vec),
                true, // starting value
                [](bool first, bool next) {
                    return first and next;
                }
            );
        }

        bool orAll(std::initializer_list<bool> vec) {

            return std::accumulate(
                std::begin(vec),
                std::end(vec),
                false, // starting value
                [](bool first, bool next) {
                    return first or next;
                }
            );
        }

        void testExercise_24a() {
            bool result = andAll({ true, false, true });
            std::cout << std::boolalpha << result << std::endl;

            result = andAll({ true, true, true, true, true, true, true, true, true, true });
            std::cout << std::boolalpha << result << std::endl;
        }

        void testExercise_24b() {
            bool result = orAll({ false, true, false });
            std::cout << std::boolalpha << result << std::endl;

            result = orAll({ false, false, false, false, false, false, false, false, false, false });
            std::cout << std::boolalpha << result << std::endl;
        }

        void testExercise_24() {
            testExercise_24a();
            testExercise_24b();
        }
    }

    namespace Exercise_25 {

        template <typename T, typename ... TARGS>
        auto minimum(const T& x, const T& y, const TARGS& ... args)
        {
            auto m = (x < y) ? x : y;

            if (sizeof ... (args) > 0) {

                auto helper = [&](const auto& value) {
                    if (value < m) {
                        m = value;
                    }
                };

                (..., helper(args));
            }

            return m;
        }

        template <typename T, typename ... TARGS>
        auto maximum(const T& x, const T& y, const TARGS& ... args)
        {
            auto m = (x > y) ? x : y;

            if (sizeof ... (args) > 0) {

                auto helper = [&](const auto& value) {
                    if (value > m) {
                        m = value;
                    }
                };

                (..., helper(args));
            }

            return m;
        }

        void testExercise_25a() {
            std::cout << minimum(1, 2) << std::endl;
            std::cout << minimum(2, 3, 4) << std::endl;
            std::cout << minimum(4, 3, 2, 1) << std::endl;
            std::cout << minimum(6, 2, 5, 7, 4, 3) << std::endl;
            std::cout << std::endl;
        }

        void testExercise_25b() {
            std::cout << maximum(1, 2) << std::endl;
            std::cout << maximum(2, 3, 4) << std::endl;
            std::cout << maximum(4, 3, 2, 1) << std::endl;
            std::cout << maximum(6, 1, 5, 2, 4, 3) << std::endl;
        }

        void testExercise_25() {
            testExercise_25a();
            testExercise_25b();
        }
    }
}

void main_exercises_legacy()
{
    using namespace Exercises::Exercise_01;
    using namespace Exercises::Exercise_02;
    using namespace Exercises::Exercise_03;
    using namespace Exercises::Exercise_04;
    using namespace Exercises::Exercise_05;
    using namespace Exercises::Exercise_06;
    using namespace Exercises::Exercise_07;
    using namespace Exercises::Exercise_08;
    using namespace Exercises::Exercise_09;
    using namespace Exercises::Exercise_10;
    using namespace Exercises::Exercise_11;
    using namespace Exercises::Exercise_12;
    using namespace Exercises::Exercise_13;
    using namespace Exercises::Exercise_14;
    using namespace Exercises::Exercise_15;
    using namespace Exercises::Exercise_16;
    using namespace Exercises::Exercise_17;
    using namespace Exercises::Exercise_18;
    using namespace Exercises::Exercise_19;
    using namespace Exercises::Exercise_20;
    using namespace Exercises::Exercise_21;
    using namespace Exercises::Exercise_22;
    using namespace Exercises::Exercise_23;
    using namespace Exercises::Exercise_24;
    using namespace Exercises::Exercise_25;

    //testExercise_01();
    //testExercise_02();
    //testExercise_03();
    //testExercise_04();  
    //testExercise_05();
    //testExercise_06();
    //testExercise_07();
    //testExercise_08();
    //testExercise_09();
    //testExercise_10();
    //testExercise_11();
    //testExercise_12();
    //testExercise_13();
    //testExercise_14();
    //testExercise_15();
    //testExercise_17();
    //testExercise_18();
    //testExercise_19();
    //testExercise_20();
    //testExercise_21();
    //testExercise_22();
    //testExercise_23();
    //testExercise_24();
    //testExercise_25();
}

// =====================================================================================
// End-of-File
// =====================================================================================
