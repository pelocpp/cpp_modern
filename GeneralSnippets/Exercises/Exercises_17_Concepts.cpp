// =====================================================================================
// Exercises_17_Concepts.cpp
// =====================================================================================

// https://oopscenities.net/2021/07/13/c20-useful-concepts-requiring-type-t-to-be-derived-from-a-base-class/

// https://lemire.me/blog/2023/04/18/defining-interfaces-in-c-with-concepts-c20/?amp

// https://itnext.io/c-20-concepts-complete-guide-42c9e009c6bf

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
            std::cout << obj.toString() << std::endl;
        }

        template <typename  T>
            requires std::is_base_of<Object, T>::value
        void print01(const T& obj)
        {
            std::cout << obj.toString() << std::endl;
        }

        template <typename  T>
        void print02(const T& obj) requires std::is_base_of<Object, T>::value
        {
            std::cout << obj.toString() << std::endl;
        }

        template <ConceptObject  T>
        void print03(const T& obj)
        {
            std::cout << obj.toString() << std::endl;
        }

        auto print04(const ConceptObject auto& obj)
        {
            std::cout << obj.toString() << std::endl;
        }

        void test_01() {

            print00(Integer{ 12 });
            print01(Integer{ 34 });
            print02(Integer{ 56 });
            print03(Integer{ 78 });
            print04(Integer{ 90 });

            print00(NaturalNumber{ 1 });
            print01(NaturalNumber{ 2 });
            print02(NaturalNumber{ 3 });
            print03(NaturalNumber{ 4 });
            print04(NaturalNumber{ 5 });

            print01(NaturalNumber{ -2 });
            print02(NaturalNumber{ -3 });
            print03(NaturalNumber{ -4 });
            print04(NaturalNumber{ -5 });
        }

        void test_02() {

            Double d{ 123.456 };
            std::cout << d.toString() << std::endl;

            // print01(d);   // the constraint was not satisfied
            // print02(d);   // the constraint was not satisfied
            // print03(d);   // the constraint was not satisfied
            // print04(d);   // the constraint was not satisfied
        }

        template <ConceptObjectEx T>
        void print10(const T& obj)
        {
            std::cout << obj.toString() << std::endl;
        }

        void print11(const ConceptObjectEx auto& obj)
        {
            std::cout << obj.toString() << std::endl;
        }

        void test_03() {

            print00(NaturalNumber{ 1 });
            print10(NaturalNumber{ 2 });
            print11(NaturalNumber{ 3 });
            print10(NaturalNumber{ -1 });
            print11(NaturalNumber{ -2 });
        }

        void testExercise_01() {

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

            void test() {

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

            void test() {

                auto result = andAll(true, true, true);

                bool b{ false };
                result = andAll(!b, b, !b);

                //result = andAll(1, 2, 3);
                //result = andAll(123.456);
            }
        }

        namespace RequiresAllSame_03 {

            // Using "Abbreviated Function Templates Syntax"

            bool andAll(std::same_as<bool> auto ... args) {
                return (... && args);
            }

            void test() {

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

            bool andAll(std::same_as<bool> auto cond) {
                return cond;
            }

            bool andAll(std::same_as<bool> auto cond, std::same_as<bool> auto ... conds) {
                return cond && andAll(conds...);
            }

            void test() {

                auto result = andAll(true, true, true);

                bool b{ false };
                result = andAll(!b, b, !b);

                //result = andAll(1, 2, 3);
                //result = andAll(123.456);
            }
        }

        void testExercise_01() {

            RequiresAllSame_01::test();
            RequiresAllSame_02::test();
            RequiresAllSame_03::test();
            RequiresAllSame_04::test();
        }
    }
}

void test_exercises_concepts()
{
    using namespace Exercises_Concepts;
    Exercise_01::testExercise_01();
    Exercise_02::testExercise_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
