// =====================================================================================
// TemplatesClassBasics04.cpp // Class Templates Basics 04
// =====================================================================================

#include <iostream>
#include <string>
#include <limits>
#include <vector>

namespace ClassTemplatesBasics04 {

    namespace SimpleTemplateDemo {

        template <typename T>
        class Optional
        {
            T m_value;
            bool m_hasValue;

        public:
            // c'tor(s)
            Optional() : m_hasValue(false), m_value(T{}) {  }
            Optional(T const& value) : m_value(value), m_hasValue(true) { }

            // public interface
            void setValue(T const& value) {
                m_value = value;
                m_hasValue = true;
            }

            void clear() {
                m_hasValue = false;
            }

            T const& getValue() const {
                if (!m_hasValue) {
                    std::cerr << "Error! No value present!\n";
                }
                return m_value;
            }

            bool hasValue() const {
                return m_hasValue;
            }
        };

        void test_01() {
            Optional<int> obj1;
            std::cout << "Object has value: " << obj1.hasValue() << "\n";
            obj1.setValue(123);
            std::cout << "Object has value: " << obj1.hasValue() << "\n";
            std::cout << "obj = " << obj1.getValue() << "\n";
            obj1.clear();
            std::cout << "Object has value: " << obj1.hasValue() << "\n";
            int dontKnow1 = obj1.getValue();

            Optional<std::string> obj2;
            std::cout << "Object has value: " << obj2.hasValue() << "\n";
            obj2.setValue("ABC");
            std::cout << "Object has value: " << obj2.hasValue() << "\n";
            std::cout << "obj = " << obj2.getValue() << "\n";
            obj2.clear();
            std::cout << "Object has value: " << obj2.hasValue() << "\n";
            std::string dontKnow2 = obj2.getValue();
        }
    }

    namespace SimpleTemplateDemo_Alternate {

        template <typename T>
        class Optional
        {
            T m_value;
            bool m_hasValue;

        public:
            // c'tor(s)
            Optional();
            Optional(T const& value);

            // public interface
            void setValue(T const& value);
            void clear();
            T const& getValue() const;
            bool hasValue() const;
        };

        template <typename T>
        Optional<T>::Optional() : m_hasValue(false), m_value(T{}) {}

        template <typename T>
        Optional<T>::Optional(T const& value) : m_value(value), m_hasValue(true) { }

        template <typename T>
        void Optional<T>::setValue(T const& value) {
            m_value = value;
            m_hasValue = true;
        }

        template <typename T>
        void Optional<T>::clear() {
            m_hasValue = false;
        }

        template <typename T>
        T const& Optional<T>::getValue() const {
            if (!m_hasValue) {
                std::cerr << "Error! No value present!\n";
            }
            return m_value;
        }

        template <typename T>
        bool Optional<T>::hasValue() const {
            return m_hasValue;
        }

        void test_02() {
            Optional<int> obj1;
            std::cout << "Object has value: " << obj1.hasValue() << "\n";
            obj1.setValue(123);
            std::cout << "Object has value: " << obj1.hasValue() << "\n";
            std::cout << "obj = " << obj1.getValue() << "\n";
            obj1.clear();
            std::cout << "Object has value: " << obj1.hasValue() << "\n";
            int dontKnow1 = obj1.getValue();

            Optional<std::string> obj2;
            std::cout << "Object has value: " << obj2.hasValue() << "\n";
            obj2.setValue("ABC");
            std::cout << "Object has value: " << obj2.hasValue() << "\n";
            std::cout << "obj = " << obj2.getValue() << "\n";
            obj2.clear();
            std::cout << "Object has value: " << obj2.hasValue() << "\n";
            std::string dontKnow2 = obj2.getValue();
        }
    }

    namespace MethodsTemplates {

        class Printer {
        private:
            std::ostream& m_target;

        public:
            explicit Printer(std::ostream& target) : m_target(target) {}

            template<typename T>
            Printer& print(const T& arg) {
                m_target << arg;
                return *this;
            }
        };

        void test_03() {

            Printer normalPrinter(std::cout);
            normalPrinter.print(100).print(" --> ").print(123.456).print("\n");

            Printer errorPrinter(std::cerr);
            errorPrinter.print(654.321).print(" <== ").print(100).print("\n");
        }
    }

    namespace DependentKeywordTypename {

        template<typename T>
        void infos(const char* name) {

            using TShort = typename std::numeric_limits<T>;  // <== NOTE: usage of keyword typename
                                                             //     dependent name

            std::cout
                << name << ':' << std::endl
                << "  Num Bits:" << TShort::digits             // number bits without sign-bit
                << "  Signed:" << TShort::is_signed            // signed datatype?   
                << "  Minimum:" << (long long)TShort::min()   // minimum value
                << "  Maximum:" << (long long)TShort::max()   // maximum value
                << "\n";
        }

        void test_04() {

            infos<signed char>("char");
            infos<unsigned char>("unsigned char");
            infos<short>("short");
            infos<int>("int");
            infos<unsigned int>("unsigned int");
            infos<long>("long");
            infos<long long>("long long");
        }
    }

    namespace TemplateMethodSpecialization {

        template <typename T>
        class MyContainer {
        private:
            T m_data;
        public:
            void setData(const T& d);  // general implementation of setData
            T getData() const;         // general implementation of getData
        };

        template <typename T>
        void MyContainer<T>::setData(const T& data) {
            m_data = data;
        }

        template <typename T>
        T MyContainer<T>::getData() const {
            return m_data;
        }

        // template method specialization of setData
        template<>
        void MyContainer<std::string>::setData(const std::string& data) {
            m_data = ">>> " + data + " <<<";
        }

        void test_05() {

            MyContainer<int> intContainer;
            intContainer.setData(123);
            std::cout << intContainer.getData() << std::endl;

            MyContainer<std::string> stringContainer;
            stringContainer.setData(std::string("Who am I?"));
            std::cout << stringContainer.getData() << std::endl;
        }
    }

    namespace PartialClassTemplateSpecialization {

        // primary template (note: demonstration of default template argument)
        template <typename T, typename U = T>
        class MyPair {
        private:
            T m_data01;
            U m_data02;
        public:
            MyPair(const T&, const U&);
            T getFirst() const;
            U getSecond() const;
        };

        template <typename T, typename U>
        MyPair<T, U>::MyPair(const T& t, const U& u) : m_data01{ t }, m_data02{ u } {}

        template <typename T, typename U>
        T MyPair<T, U>::getFirst() const { return m_data01; }

        template <typename T, typename U>
        U MyPair<T, U>::getSecond() const { return m_data02; }

        // first partial specialization: U is specialized upon std::string, T stays formal
        template <typename T>
        class MyPair<T, std::string> {
        private:
            T m_data;
            std::string m_str;

        public:
            MyPair(const T&, const std::string&);
            T getFirst() const;
            std::string getSecond() const;
        };

        template <typename T>
        MyPair<T, std::string>::MyPair(const T& t, const std::string& str) : m_data{ t }, m_str{ str } {}

        template <typename T>
        T MyPair<T, std::string>::getFirst() const { return m_data; }

        template <typename T>
        std::string MyPair<T, std::string>::getSecond() const { return m_str; }

        // second partial specialization: T is specialized upon std::string, U stays formal
        template <typename U>
        class MyPair<std::string, U> {
        private:
            std::string m_str;
            U m_data;

        public:
            MyPair(const std::string&, const U&);
            std::string getFirst() const;
            U getSecond() const;
        };

        template <typename U>
        MyPair<std::string, U>::MyPair(const std::string& str, const U& u) : m_str{ str }, m_data{ u } {}

        template <typename U>
        std::string MyPair<std::string, U>::getFirst() const { return m_str; }

        template <typename U>
        U MyPair<std::string, U>::getSecond() const { return m_data; }

        void test_06() {

            // instantiate templates
            MyPair<int, int> int_int{ 123, 456 };               // use of primary template
            MyPair<int, std::string> int_string{ 123, "ABC" };   // partial specialization
            MyPair<std::string, int> string_int{ "DEF", 456 };   // partial specialization

            // test instantiated template methods
            std::cout << int_int.getFirst() << std::endl;
            std::cout << int_int.getSecond() << std::endl;
            std::cout << int_string.getFirst() << std::endl;
            std::cout << int_string.getSecond() << std::endl;
            std::cout << string_int.getFirst() << std::endl;
            std::cout << string_int.getSecond() << std::endl;
        }

        template<>  // full specialization
        class MyPair<std::string, std::string> {
        private:
            std::vector<std::string> m_vec;
        public:
            //MyPair(const std::string& s1, const std::string& s2) : m_vec{ s1, s2 } {}
            MyPair(const std::string& s1, const std::string& s2);
            std::string getFirst() const;
            std::string getSecond() const;
        };

        // note: full template specialization doesn't need a trailing 'template<>',
        // it's just a definition of ordinary class members
        MyPair<std::string, std::string>::MyPair(const std::string& str1, const std::string& str2) : m_vec{ str1, str2 } {}
        std::string MyPair<std::string, std::string>::getFirst() const { return m_vec[0]; }
        std::string MyPair<std::string, std::string>::getSecond() const { return m_vec[1]; }

        void test_07() {

            // instantiate template
            MyPair<std::string, std::string> str_str{ "uvw","xyz" }; // ambiguous

            // Without 'full' / 'explicit' specialization not compilable
            // 'more than one partial specialization matches the template argument list'

            // See 'explicit' specialization above this method

            std::cout << str_str.getFirst() << std::endl;
            std::cout << str_str.getSecond() << std::endl;
        }
    }
}

void main_class_templates_basics_04()
{
    using namespace ClassTemplatesBasics04::SimpleTemplateDemo;
    using namespace ClassTemplatesBasics04::SimpleTemplateDemo_Alternate;
    using namespace ClassTemplatesBasics04::MethodsTemplates;
    using namespace ClassTemplatesBasics04::DependentKeywordTypename;
    using namespace ClassTemplatesBasics04::TemplateMethodSpecialization;
    using namespace ClassTemplatesBasics04::PartialClassTemplateSpecialization;

    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
    test_07();
}

// =====================================================================================
// End-of-File
// =====================================================================================
