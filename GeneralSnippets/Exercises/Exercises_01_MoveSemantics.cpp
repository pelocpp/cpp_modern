// =====================================================================================
// Exercises_01_MoveSemantics.cpp
// =====================================================================================

module;

#include "../ScopedTimer/ScopedTimer.h"

module modern_cpp_exercises:move_semantics;

namespace Exercises_MoveSemantics {

    namespace Exercise_01 {

        class Person 
        {
        private:
            std::string m_name;         // name of person
            std::vector<int> m_values;  // some arbitrary person values

        public:
            Person() {}
            Person(const std::string& name) : m_name{ name } {}
            ~Person() {}

            void addValue(int value) {
                m_values.push_back(value);
            }

            friend std::ostream& operator<< (std::ostream& os, const Person& cust) {
                os << "{ " << cust.m_name << ": ";
                for (auto val : cust.m_values) {
                    os << val << ' ';
                }
                os << "}";
                return os;
            }
        };

        /*
        * When passing an object to a function, or returning an object from a function, 
        * it's possible to do a move (rather than a copy) if:
        * 
        * = the object is an rvalue
        * = the object's class defines the special member move functions
        */

        static void testExercise() {

            // create a person with some initial values
            Person dagobert{ "Dagobert Duck" };
            for (int value : { 1, 2, 3, 4, 5, 6, 7, 8, 9 }) {
                dagobert.addValue(value);
            }

            // print person
            std::cout << "Person: " << dagobert << std::endl;

            // insert person into a collection
            std::vector<Person> persons;
            persons.push_back(dagobert);
            // persons.push_back(std::move(dagobert));

            // print person again
            std::cout << "Person: " << dagobert << std::endl;
        }
    }

    namespace Exercise_02 {

// #define SOLUTION 

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

        static void testExercise()
        {
            std::cout << "Start:" << std::endl;
         
            ScopedTimer watch{};

            std::vector<HugeArray> myVec;

            HugeArray bArray(10000000);
            HugeArray bArray2(bArray);
            myVec.push_back(bArray);   // <== std::move
            bArray = HugeArray(20000000);

            myVec.push_back(HugeArray(30000000));  // <== emplace_back (30000000)

            std::cout << "Done." << std::endl;
        }
    }
}

void test_exercises_move_semantics()
{
    using namespace Exercises_MoveSemantics;

    Exercise_01::testExercise();
    Exercise_02::testExercise();
}

// =====================================================================================
// End-of-File
// =====================================================================================
