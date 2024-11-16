// =====================================================================================
// Exercises_16_Generic_Lambdas.cpp
// =====================================================================================

module modern_cpp_exercises:generic_lambdas;

namespace Exercises_Generic_Lambdas {

    namespace Exercise_01 {

        static void testExercise_01_01() {

            // define a generic lambda
            auto isGreaterThanFifty = [](const auto& n) { return n > 50; };

            std::vector<int> intValues{ 44, 65, 22, 77, 2 };

            // use generic lambda with a vector of integers
            auto pos = std::find_if(
                std::begin(intValues),
                std::end(intValues),
                isGreaterThanFifty
            );
            if (pos != std::end(intValues)) {
                std::cout << "Found a value: " << *pos << std::endl;
            }
        }

        class Person
        {
        private:
            std::string m_name;
            size_t m_age;

        public:
            Person(std::string name, size_t age)
                : m_name{ name }, m_age{ age } {}

            std::string getName() const { return m_name; }

            bool operator > (size_t age) const {
                return m_age > age;
            }
        };

        static void testExercise_01_02()
        {
            // generic lambda - same as above
            auto isGreaterThanFifty = [](const auto& object) {
                return object > 50;
            };

            std::vector<Person> personValues{
                Person{ "Hans", 40 },
                Person{ "Sepp", 60 }
            };

            // use generic lambda with a vector of Persons
            auto pos = std::find_if(
                std::begin(personValues),
                std::end(personValues),
                isGreaterThanFifty
            );
            if (pos != std::end(personValues)) {
                std::cout << "Found Person:  " << (*pos).getName() << std::endl;
            }
        }

        static void testExercise_01() {
            testExercise_01_01();
            testExercise_01_02();
        }
    }
}

void test_exercises_generic_lambdas()
{
    using namespace Exercises_Generic_Lambdas;
    Exercise_01::testExercise_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
