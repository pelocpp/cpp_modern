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
#include <chrono>
#include <functional>
#include <map>
#include <optional>
#include <tuple>
#include <array>
#include <variant>
#include <numeric>
#include <iterator>

namespace Exercises {

    namespace Exercise_01 {

        template <typename T>
        inline T minimum(const T& t) { return t; }

        template <typename T, typename ...P>
        inline typename std::common_type<T, P...>::type
            minimum(const T& t, const P& ...p)
        {
            typedef typename std::common_type<T, P...>::type res_type;
            return std::min(res_type(t), res_type(minimum(p...)));
        }

        // oder etwas knapper

        //template <typename T>
        //inline T minimum(const T& t) { return t; }

        //template <typename T, typename ...P>
        //inline auto minimum(const T& t, const P& ...p)
        //{
        //    using res_type = std::common_type_t<T, P...>;
        //    return std::min(res_type(t), res_type(minimum(p...)));
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
            myVec.push_back(HugeArray(30000000));
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
            std::for_each(std::begin(values), std::end(values), [](int val) {
                if (!(val % 2)) {
                    std::cout << val << std::endl;
                }
                });

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
            std::for_each(std::begin(values), std::end(values), [divisor = 3](int val) {
                if (!(val % divisor)) {
                    std::cout << val << std::endl;
                }
            });
            std::cout << std::endl;

            // or 'divisor' defined in outer context (scope) 
            int divisor = 5;

            // capture context by value (reference & would work also)
            std::for_each(std::begin(values), std::end(values), [=](int val) {
                if (!(val % divisor)) {
                    std::cout << val << std::endl;
                }
                });
        }
    }

    namespace Exercise_04 {

        std::map<char, std::function<double(double, double)>> createCalculatorEx() {

            std::map<char, std::function<double(double, double)>> map;
            map.insert(std::make_pair('+', [](double a, double b) { return a + b; }));
            map.insert(std::make_pair('-', [](double a, double b) { return a - b; }));
            map.insert(std::make_pair('*', [](double a, double b) { return a * b; }));
            map.insert(std::make_pair('/', [](double a, double b) { return a / b; }));
            return map;
        }

        // or more compact

        std::map<char, std::function<double(double, double)>> createCalculator() {

            std::map<char, std::function<double(double, double)>> map;
            map['+'] = [](double a, double b) { return a + b; };
            map['-'] = [](double a, double b) { return a - b; };
            map['*'] = [](double a, double b) { return a * b; };
            map['/'] = [](double a, double b) { return a / b; };
            return map;
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
            std::cout << "Result: " << op1 << ' ' << op << ' ' << op1 << " = " << result << '.' << std::endl;
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
            // 1
            // 2
            // 2

            // Rather than printing 1, 2, 3, the code prints 2 twice. When we created @otherCount as a copy of @count,
            // we created a copy of @count in its current state. @count‘s i was 1, so @otherCount‘s i is 1 as well.
            // Since @otherCount is a copy of @count, they each have their own @i.

            int i{ 0 };

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

        void testExercise_05c()
        {
            // Output:
            // 1
            // 1
            // 1

            // This exhibits the same problem as the prior example in a more obscure form:
            // When std::function is created with a lambda, 
            // the std::function internally makes a copy of the lambda object.
            // Thus, the call to fn() is actually being executed on the copy of our lambda, not the actual lambda.

            int i{ 0 };

            // increments and prints its local copy of @i
            auto count{ [i]() mutable { std::cout << ++i << std::endl; } };

            invoke(count);
            invoke(count);
            invoke(count);
            std::cout << std::endl;
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
                std::cerr << i1.value() << std::endl;
            }

            std::optional<int> i2 = toInt("-987654321");
            if (i2.has_value()) {
                std::cerr << i2.value() << std::endl;
            }

            std::optional<int> i3 = toInt("123ABC");
            if (i3.has_value()) {
                std::cerr << i3.value() << std::endl;
            }

            std::optional<int> i4 = toInt("ABC123");
            if (i4.has_value()) {
                std::cerr << i4.value() << std::endl;
            }
        }

        void testExercise_06b() {

            std::optional<short> i1 = toNumber<short>("32767");
            if (i1.has_value()) {
                std::cerr << i1.value() << std::endl;
            }

            std::optional<int> i2 = toNumber<int>("2147483647");
            if (i2.has_value()) {
                std::cerr << i2.value() << std::endl;
            }

            std::optional<long int> i3 = toNumber<long int>("2147483647");
            if (i3.has_value()) {
                std::cerr << i3.value() << std::endl;
            }

            std::optional<long long> i4 = toNumber<long long>("9223372036854775807");
            if (i4.has_value()) {
                std::cerr << i4.value() << std::endl;
            }
        }
    }

    namespace Exercise_07 {

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

        template<typename ... args>
        void printTuple(const std::tuple<args...>& t) {
            using tuple_type = const std::tuple<args...>&;
            static const int tuple_size = sizeof...(args);
            std::cout << "[";
            ShowTupleImpl<const std::tuple<args...>&, tuple_size>::print(t);
            std::cout << "]" << std::endl;
        }

        template<typename ... args>
        void printTupleEx(const std::tuple<args...>& t) {
            using tuple_type = const std::tuple<args...>&;
            static const int tuple_size = sizeof...(args);
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

        // Create a single class and use expression SFINAE on the return type of methods
        // in that class to return true if the method is detected and false if the method
        // does not exist. In the example below, we're calling testGet with an int parameter.
        //
        // This causes the first testGet method, which takes an int as an argument,
        // to be preferred over the second testGet method, which takes anything (...)
        // as an argument. The first method will only be enabled, however,
        // if the expression inside the decltype can resolve without errors.
        // 
        // The return type for both functions is bool, since decltype will return
        // the type of the last expression (technically, this is due to the comma operator).

        // https://people.eecs.berkeley.edu/~brock/blog/detection_idiom.php

        template <typename T>
        struct TestMethod {

            template <typename U>
            static constexpr
                decltype(std::declval<U>().get(), bool())
                testGet(int) { return true; }

            template <typename U>
            static constexpr bool testGet(...) { return false; }

            static constexpr bool value = testGet<T>(int());
        };

        struct FirstStruct {
            int get() { return 123; };
        };

        struct SecondStruct {
            int getter() { return 456; };
        };

        void testExercise_10() {
            std::cout
                << typeid(struct FirstStruct).name() << ":  "
                << std::boolalpha << TestMethod<FirstStruct>::value << std::endl;

            std::cout
                << typeid(struct SecondStruct).name() << ": "
                << std::boolalpha << TestMethod<SecondStruct>::value << std::endl;
        };
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

            // using initializer list for a string
            std::string cppInventor = { "Bjarne Stroustrup" };
            std::cout << "Name of Cpp Inventor: " << cppInventor;

            // using initializer list for a std::map and std::pair
            std::cout << "List of Persons: " << std::endl;
            std::map<std::string, std::string> phonebook{
                { "Hans Meier" , "123456789"},
                { "Hubert Mueller", "987654321"},
                { "Franz Schneider", "1231231230"}
            };

            for (auto mapIt = phonebook.begin(); mapIt != phonebook.end(); ++mapIt) {
                std::cout << mapIt->first << ": " << mapIt->second << std::endl;
            }

            // using MyContainer with int
            MyContainer<int> i{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            i();

            // using MyContainer with std::string
            MyContainer<std::string> myStringContainer{ "Range","based","for","loop" };
            myStringContainer();

            MyContainer<int> i1;
            i1();
            MyContainer<int> i2{};
            i2();
            MyContainer<int> i3(1, 2);
            i3();
            MyContainer<int> i4{ 1, 2 };
            i4();
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

        //template<typename T>
        //bool orAll(T cond) {
        //    return cond;
        //}

        //template<typename T, typename... Ts>
        //bool orAll(T cond, Ts... conds) {
        //    return cond || orAll(conds...);
        //}

        // or

        bool orAll() {
            return false;
        }

        template<typename T, typename... Ts>
        bool orAll(T cond, Ts... conds) {
            return cond && andAll(conds...);
        }

        void testExercise_12b() {

            bool result = orAll(false, true, false);
            std::cout << std::boolalpha << result << std::endl;

            result = orAll(false, false, false, false, false, false, false, false, false, false);
            std::cout << std::boolalpha << result << std::endl;
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
    }

    namespace Exercise_14 {

        template<typename T1, typename T2>
        bool sameType(T1 arg1, T2 arg2)
        {
            std::cout << " # " << arg1 << ": " << typeid(arg1).name();
            std::cout << " - " << arg2 << ": " << typeid(arg2).name() << std::endl;

            return std::is_same<decltype(arg1), decltype(arg2)>::value;
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

        template<typename T, typename... TREST>
        constexpr bool sameType(T arg, TREST... args)
        {
            std::cout << "compare: " << arg << " with " << std::endl;
            // since C++17: folding expression !
            return (std::is_same<decltype(arg), decltype(args)>::value && ...);
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

        template <class... T>
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
    }
}

void main_exercices()
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

    //testExercise_01();

    //testExercise_02();
    //
    //testExercise_03a();
    //testExercise_03b();
    
    // testExercise_04a();  // needs console input
    //testExercise_04b();
    //
    //testExercise_05a();
    //testExercise_05b();
    //testExercise_05c();

    //testExercise_06a();
    //testExercise_06b();
    //
    //testExercise_07();
    //
    //testExercise_08();
    //
    //testExercise_09();
    //
    //testExercise_10();
    //
    //testExercise_11();
    //
    //testExercise_12a();
    //testExercise_12b();
    // 
    //testExercise_13a();
    //testExercise_13b();
    //
    //testExercise_14();
    //
    //testExercise_15();

    //testExercise_17();
    
    //testExercise_18a();
    //testExercise_18b();
    //testExercise_18c();
    //testExercise_18d();
}

// =====================================================================================
// End-of-File
// =====================================================================================
