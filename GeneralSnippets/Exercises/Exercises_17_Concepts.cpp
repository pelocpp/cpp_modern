// =====================================================================================
// Exercises_17_Concepts.cpp
// =====================================================================================

module modern_cpp_exercises:concepts;

namespace Exercises_Concepts {

    namespace Exercise_01 {

        class Object;

        template <typename T>
        concept ConceptObject = std::is_base_of<Object, T>::value;

        template <typename T>
        concept ConceptObjectEx = std::derived_from<T, Object>;

        class Object
        {
        public:
            virtual ~Object() = default;
            virtual std::string toString() const = 0;
        };

        class Integer : public Object
        {
        protected:
            int m_value;

        public:
            Integer() : Integer{ 0 } {};
            Integer(int value) : m_value{ value } {}

            std::string toString() const override
            {
                return "Integer: " + std::to_string(m_value);
            }
        };

        class NaturalNumber : public Integer
        {
        public:
            NaturalNumber() : Integer{ 0 } {};
            NaturalNumber(int value) : Integer{ value >= 0 ? value : 0 } {}
        };

        class Double
        {
        private:
            double m_value;

        public:
            Double() : Double{ 0 } {};
            Double(double value) : m_value{ value } {}

            std::string toString() const // override
            {
                return "Double:  " + std::to_string(m_value);
            }
        };

        template <typename T>
        void print00(const T& obj)
        {
            std::println("{}", obj.toString());
        }

        template <typename T>
            requires std::is_base_of<Object, T>::value
        void print01(const T& obj)
        {
            std::println("{}", obj.toString());
        }

        template <typename T>
        void print02(const T& obj) requires std::is_base_of<Object, T>::value
        {
            std::println("{}", obj.toString());
        }

        template <ConceptObject T>
        void print03(const T& obj)
        {
            std::println("{}", obj.toString());
        }

        static auto print04(const ConceptObject auto& obj)
        {
            std::println("{}", obj.toString());
        }

        static void test_01() {

            print00(Integer{ 1 });
            print01(Integer{ 2 });
            print02(Integer{ 3 });
            print03(Integer{ 4 });
            print04(Integer{ 5 });

            print00(NaturalNumber{ 10 });
            print01(NaturalNumber{ 20 });
            print02(NaturalNumber{ 30 });
            print03(NaturalNumber{ 40 });
            print04(NaturalNumber{ 50 });

            print01(NaturalNumber{ -1 });
            print02(NaturalNumber{ -2 });
            print03(NaturalNumber{ -3 });
            print04(NaturalNumber{ -4 });
        }

        static void test_02() {

            Double d{ 123.456 };
            std::println("{}", d.toString());

            // print01(d);   // the constraint was not satisfied
            // print02(d);   // the constraint was not satisfied
            // print03(d);   // the constraint was not satisfied
            // print04(d);   // the constraint was not satisfied
        }

        template <ConceptObjectEx T>
        void print10(const T& obj)
        {
            std::println("{}", obj.toString());
        }

        static void print11(const ConceptObjectEx auto& obj)
        {
            std::println("{}", obj.toString());
        }

        static void test_03() {

            print00(NaturalNumber{ 1 });
            print10(NaturalNumber{ 2 });
            print11(NaturalNumber{ 3 });
            print10(NaturalNumber{ -1 });
            print11(NaturalNumber{ -2 });
        }

        static void testExercise() {

            test_01();
            test_02();
            test_03();
        }
    }

    namespace Exercise_02 {

        namespace RequiresAllSame_01 {

            // Using Function Overloading

            template<typename T>
                requires std::same_as<T, bool>
            bool andAll(T cond) {
                return cond;
            }

            template<typename T, typename ... TRest>
                requires std::same_as<T, bool> && (std::same_as<TRest, bool> && ...)
            bool andAll(T cond, TRest ... conds) {
                return cond && andAll(conds...);
            }

            static void test() {

                auto result = andAll(true, true, true);

                bool b{ false };
                result = andAll(!b, b, !b);

                //result = andAll(1, 2, 3);
                //result = andAll(123.456);
            }
        }

        namespace RequiresAllSame_02 {

            // Using Folding

            template<typename ... TArgs>
                requires (std::same_as<TArgs, bool> && ...)
            bool andAll(TArgs ... args) {
                return (... && args);
            }

            static void test() {

                auto result = andAll(true, true, true);

                bool b{ false };
                result = andAll(!b, b, !b);

                //result = andAll(1, 2, 3);
                //result = andAll(123.456);
            }
        }

        namespace RequiresAllSame_03 {

            // Using "Abbreviated Function Templates Syntax"

            static bool andAll(std::same_as<bool> auto ... args) {
                return (... && args);
            }

            static void test() {

                auto result = andAll(true, true, true);

                bool b{ false };
                result = andAll(!b, b, !b);

                //result = andAll(1, 2, 3);
                //result = andAll(123.456);
            }
        }

        namespace RequiresAllSame_04 {

            // Using "Abbreviated Function Templates Syntax"
            // in combination with overloaded functions

            static bool andAll(std::same_as<bool> auto cond) {
                return cond;
            }

            static bool andAll(std::same_as<bool> auto cond, std::same_as<bool> auto ... conds) {
                return cond && andAll(conds...);
            }

            static void test() {

                auto result = andAll(true, true, true);

                bool b{ false };
                result = andAll(!b, b, !b);

                //result = andAll(1, 2, 3);
                //result = andAll(123.456);
            }
        }

        namespace RequiresAllSame_05 {

            /*
             * NOT using concepts:
             * Based on C++ 17 with std::enable_if and Folding
             * C++ 11 is always possible, then you need to reimplement std::conjunction.
             */

             // wrapper for 'std::conjunction'
            template <typename ... TArgs>
            constexpr bool AreSame = std::conjunction<std::is_same<bool, TArgs> ...>::value;

            template <typename ... TArgs>
            std::enable_if <AreSame<TArgs ...>, bool>::type
                andAll(TArgs ... args) noexcept
            {
                return (... && args);
            }

            static void test() {

                auto result = andAll(true, true, true);

                bool b{ false };
                result = andAll(!b, b, !b);

                //result = andAll(1, 2, 3);
                //result = andAll(123.456);
            }
        }

        static void testExercise() {

            RequiresAllSame_01::test();
            RequiresAllSame_02::test();
            RequiresAllSame_03::test();
            RequiresAllSame_04::test();
            RequiresAllSame_05::test();
        }
    }

    namespace Exercise_03 {

        namespace Exercise_03_Using_Interface {

            // ---------------------------------------------------------------
            // without interfaces

            class IntegerIterable
            {
            public:
                virtual bool hasNext() const = 0;
                virtual int  next() = 0;
                virtual void reset() = 0;
            };

            static int count(IntegerIterable& t)
            {
                int count{};

                t.reset();
                while (t.hasNext()) {
                    t.next();
                    ++count;
                }

                return count;
            }

            class IterableArray : public IntegerIterable
            {
            private:
                std::vector<int> m_array;
                size_t           m_index;

            public:
                IterableArray(std::initializer_list<int> numbers)
                    : m_array{ numbers }, m_index{} 
                {}

                virtual void reset() override { 
                    m_index = 0;
                }

                virtual bool hasNext() const override {
                    return m_index < m_array.size();
                }

                virtual int next() override {
                    ++m_index;
                    return m_array[m_index - 1];
                }
            };

            static int getCount(IntegerIterable& a) {
                return count(a);
            }

            static void test() {

                IterableArray a{ 1, 2, 3, 4, 5 };

                int count{ getCount(a) };
                std::println("{}", count);

                // Note: '->'-Operator
                IntegerIterable* ap{ &a };
                ap->reset();
                while (ap->hasNext()) {
                    int n{ ap->next() };
                    std::print("{} ", n);
                }
                std::println();
            }
        }

        namespace Exercise_03_Using_Concepts {

            // ---------------------------------------------------------------
            // without concepts

            template <typename T>
            int count(T& t)
            {
                int count{};

                t.reset();
                while (t.hasNext()) {
                    t.next();
                    ++count;
                }

                return count;
            }

            // ---------------------------------------------------------------
            // with concepts

            template <typename T>
            concept IsIterable = requires(T v)
            {
                { std::as_const(v).hasNext() } -> std::convertible_to<bool>;
                { v.next() } -> std::same_as<int>;
                { v.reset() }-> std::convertible_to<void>;
            };

            template <typename T>
                requires IsIterable<T>
            int count(T& t) {
                int count{};
                t.reset();
                while (t.hasNext()) {
                    t.next();
                    ++count;
                }
                return count;
            }

            class IterableArray
            {
            private:
                std::vector<int> m_array;
                size_t           m_index;

            public:
                IterableArray(std::initializer_list<int> numbers)
                    : m_array{ numbers }, m_index{} 
                {}

                void reset() {
                    m_index = 0; 
                }

                bool hasNext() const {
                    return m_index < m_array.size();
                }

                int next() {
                    ++m_index;
                    return m_array[m_index - 1];
                }
            };

            template <typename T>
                requires IsIterable <T>
            int getCount(T& a) {
                return count(a);
            }

            static void test()
            {
                IterableArray a{ 1, 2, 3, 4, 5 };

                int count1{ getCount(a) };
                int count2{ getCount<IterableArray>(a) };

                std::println("{}", count1);
                std::println("{}", count2);

                // Note: '.'-Operator
                a.reset();
                while (a.hasNext()) {
                    int n{ a.next() };
                    std::print("{} ", n);
                }
                std::println();
            }
        }

        namespace Exercise_03_Using_Concepts_Improved {

            // ---------------------------------------------------------------
            // with concepts

            template <typename T, typename U>
            concept GenericIsIterable = requires(T v)
            {
                { std::as_const(v).hasNext() } -> std::convertible_to<bool>;
                { v.next() } -> std::same_as<U>;
                { v.reset() }-> std::convertible_to<void>;
            };

            template <typename T, typename U>
                requires GenericIsIterable<T, U>
            int count(T& t) {
                int count{};
                t.reset();
                while (t.hasNext()) {
                    t.next();
                    count++;
                }
                return count;
            }

            class IterableDoubleArray
            {
            private:
                std::vector<double> m_array{};
                size_t              m_index{};

            public:
                IterableDoubleArray(std::initializer_list<double> numbers)
                    : m_array{ numbers }, m_index{} 
                {}

                void reset() {
                    m_index = 0;
                }

                bool hasNext() const {
                    return m_index < m_array.size();
                }

                double next() {
                    m_index++;
                    return m_array[m_index - 1];
                }
            };

            template <typename T, typename U>
                requires GenericIsIterable <T, U>
            int getCount(T& a) {
                return count<T, U>(a);
            }

            static void test() {
                IterableDoubleArray d{ 1.5, 2.5, 3.5, 4.5, 5.5 };
                int count{ getCount<IterableDoubleArray, double>(d) };
                std::println("{}", count);
            }
        }

        static void testExercise() {

            Exercise_03_Using_Interface::test();
            Exercise_03_Using_Concepts::test();
            Exercise_03_Using_Concepts_Improved::test();
        }
    }

    namespace Exercise_04 {

        template<typename ... TArgs>
            requires (std::same_as<TArgs, std::string> && ...)
        size_t totalLength(const TArgs& ... args)
        {
            size_t len{};
            for (const auto& s : { args ... }) {
                len += s.size();
            }
            return len;
        }

        template<typename... TArgs>
            requires (std::same_as<TArgs, std::string> && ...)
        size_t totalLengthEx(const TArgs& ... args)
        {
            size_t len{};
            for (const auto& s : { args.size() ... }) {
                len += s;
            }
            return len;
        }

        static void testExercise_01()
        {
            const std::string s1{ "111" };
            const std::string s2{ "AAAAA" };
            const std::string s3{ "!!!" };

            size_t len{ totalLength(s1, s2, s3) };
            std::println("{}", len);

            len = totalLengthEx(s1, s2, s3);
            std::println("{}", len);
        }

        static void testExercise_02()
        {
            const std::string cs{ "11111" };
            const std::string& csr{ cs };
            std::string s{ "333" };

            size_t len{ totalLength(cs, std::string{ "2" }, csr, s) };
            std::println("{}", len);
        }

        static void testExercise() {
            testExercise_01();
            testExercise_02();
        }
    }
}

void test_exercises_concepts()
{
    using namespace Exercises_Concepts;

    Exercise_01::testExercise();
    Exercise_02::testExercise();
    Exercise_03::testExercise();
    Exercise_04::testExercise();
}

// =====================================================================================
// End-of-File
// =====================================================================================
