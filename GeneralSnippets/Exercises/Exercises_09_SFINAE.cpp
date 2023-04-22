// =====================================================================================
// Exercises_09_SFINAE.cpp
// =====================================================================================

module;

// GCC support
#ifndef __FUNCSIG__
#define __FUNCSIG__ __PRETTY_FUNCTION__
#endif

module modern_cpp_exercises:sfinae;

namespace Exercises_SFINAE {

    namespace Exercise_01 {

        template <typename T>
        T distance(T a1, T a2, T b1, T b2)
        {
            T tmp1 = a1 - b1;
            T tmp2 = a2 - b2;
            return std::sqrt(tmp1 * tmp1 + tmp2 * tmp2);
        }

        // primary template
        template <typename>
        struct TypeRestrictor {};

        // partial (explicit) template specialization
        template<>
        struct TypeRestrictor<float>
        {
            using result = float;
        };

        // partial (explicit) template specialization
        template<>
        struct TypeRestrictor<double>
        {
            using result = double;
        };

        template <typename T>
        TypeRestrictor<T>::result
            distanceEx(T a1, T a2, T b1, T b2)
        {
            T tmp1 = a1 - b1;
            T tmp2 = a2 - b2;
            return std::sqrt(tmp1 * tmp1 + tmp2 * tmp2);
        }

        void testExercise_01() {

            double result1 = distanceEx<double>(2.0, 2.0, 1.0, 1.0);
            std::cout << result1 << std::endl;

            float result2 = distanceEx<float>(3.0F, 3.0F, 2.0F, 2.0F);
            std::cout << result2 << std::endl;

            //int result3 = distanceEx<int>(2, 2, 1, 1);
            //std::cout << result1 << std::endl;
        };
    }

    namespace Exercise_02 {

        //char* printTimeStamp(const std::time_t& ttp)
        //{
        //    char* cp{ std::ctime(&ttp) };
        //    size_t len{ std::strlen(cp) };
        //    cp[len - 1] = '\0';
        //    return cp;
        //}

        // Augangsfunktion - ist ein Kommentar gesetzt, da weiter unter das SFINAE-Prinzip angewendet wird
        //template<typename T>
        //void print(const T& arg) {
        //    std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();
        //    std::time_t ttp = std::chrono::system_clock::to_time_t(time_point);
        //    std::cout << "[" << printTimeStamp(ttp) << "] " << arg << std::endl;
        //}
        
        // Error: function template has already been defined
        //template<typename T>
        //void print(const T& arg) {
        //    arg.log();
        //}

        class AnyClass
        {
            friend std::ostream& operator << (std::ostream& out, const AnyClass& m);

        public:
            AnyClass() : AnyClass{ 0 } {};
            AnyClass(int n) : m_i{ n } {};

            virtual void log() const {
                std::cout << "AnyClass: m_i=";
                std::cout << *this << std::endl;
            }

        protected:
            int m_i;
        };

        std::ostream& operator<<(std::ostream& os, const AnyClass& m) {
            return os << m.m_i;
        }

        /*
         * Beachte:
         * Die Platzierung des SFINAE Patterns findet in der Definition des Rückgabetyps der Funktion statt.
         * Der zweite, nicht vorhandene Template Parameter von 'std::enable_if' ist per default
         * auf 'void' gesetzt
         */

        template <typename T>
        typename std::enable_if<!std::is_same<T, AnyClass>::value>::type
            print(const T& arg) {
            std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();
            std::time_t ttp = std::chrono::system_clock::to_time_t(time_point);
            // std::cout << "[" << printTimeStamp(ttp) << "] " << arg << std::endl;
        }

        template <typename T>
        typename std::enable_if<std::is_same<T, AnyClass>::value>::type
            print(const T& arg) {
            arg.log();
        }

        // Zusatzaufgabe:
        template <typename, typename = void>
        struct hasLogMessage : std::false_type {};

        template <typename T>
        struct hasLogMessage<T, decltype(std::declval<T>().log())> : std::true_type {};

        template <typename T>
        typename std::enable_if<hasLogMessage<T>::value>::type
            print2(const T& arg) {
            arg.log();
        }

        template <typename T>
        typename std::enable_if<!hasLogMessage<T>::value>::type
            print2(const T& arg) {
            std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();
            std::time_t ttp = std::chrono::system_clock::to_time_t(time_point);
            // std::cout << "[" << printTimeStamp(ttp) << "] " << arg << std::endl;
        }

        class AnotherClass : public AnyClass
        {
        public:
            AnotherClass() : AnyClass{ } {};
            AnotherClass(int n) : AnyClass{ n } {};

            virtual void log() const override {
                std::cout << "AnotherClass [m_i=";
                std::cout << *this << "]" << std::endl;
            }
        };

        void test_02a()
        {
            int n{ 123 };
            print(n);

            std::string s{ "a string" };
            print(s);
        }

        void test_02b()
        {
            AnyClass obj{ 456 };
            print(obj);
        }

        void test_02c()
        {
            char ch{ '!' };
            print(ch);

            AnyClass obj{ 123456 };
            print(obj);
        }

        void test_02d()
        {
            int n{ 123 };
            print2(n);

            AnyClass obj1{ 456 };
            print2(obj1);

            AnotherClass obj2{ 789 };
            print2(obj2);
        }

        void testExercise_02() {
            test_02a();
            test_02b();
            test_02c();
            test_02d();
        };
    }

    namespace Exercise_03 {

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

        void testExercise_03a() {

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

        void testExercise_03b() {

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

        void testExercise_03() {
            testExercise_03a();
            testExercise_03b();
        }
    }

    namespace Exercise_04 {

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

        void testExercise_04() {
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
}

void test_exercices_sfinae()
{
    using namespace Exercises_SFINAE;
    Exercise_01::testExercise_01();
    Exercise_02::testExercise_02();
    Exercise_03::testExercise_03();
    Exercise_04::testExercise_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
