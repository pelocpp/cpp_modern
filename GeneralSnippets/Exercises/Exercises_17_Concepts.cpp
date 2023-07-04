// =====================================================================================
// Exercises_17_Concepts.cpp
// =====================================================================================

// https://lemire.me/blog/2023/04/18/defining-interfaces-in-c-with-concepts-c20/?amp

// https://itnext.io/c-20-concepts-complete-guide-42c9e009c6bf

// https://itnext.io/c-20-concepts-complete-guide-42c9e009c6bf

// https://iteo.com/blog/post/c-concepts-make-the-templates-greater-again/


module modern_cpp_exercises:concepts;

namespace Exercises_Concepts {

    namespace Exercise_01 {

//01: template < typename T>
//02 : concept Numerical = std::integral<T> || std::floating_point<T>;

// https://oopscenities.net/2021/07/13/c20-useful-concepts-requiring-type-t-to-be-derived-from-a-base-class/


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
        private:
            int m_value;

        public:
            Integer() : Integer{ 0 } {};

            Integer(int value) : m_value{ value } {}

            std::string toString() const override
            {
                return "Integer: " + std::to_string(m_value);
            }
        };

        class Double // : public Object
        {
        private:
            double m_value;

        public:
            Double() : Double{ 0 } {};

            Double(double value) : m_value{ value } {}

            std::string toString() const // override
            {
                return "Double: " + std::to_string(m_value);  // TOTO : TESTEN
            }
        };



        template <typename T>
        void print(const T& obj)
        {
            std::cout << obj.toString() << std::endl;
        }

        template <ConceptObject T>
        void print1(const T& obj)
        {
            std::cout << obj.toString() << std::endl;
        }

        template <ConceptObjectEx T>
        void print2(const T& obj)
        {
            std::cout << obj.toString() << std::endl;
        }

        // WEITER: ALLE 4 Varianten !!!


        void test_01() {

            print(Integer{ 123 });
            //Double d{ 123.456 };
            //d.toString();
            //std::cout << d.toString() << std::endl;

            print1(Integer{ 456 });

            print2(Integer{ 789 });
        }



        void testExercise_01() {

            std::cout << "asdasdasd";
        }
    }
}

void test_exercises_concepts()
{
    using namespace Exercises_Concepts;
    Exercise_01::testExercise_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
