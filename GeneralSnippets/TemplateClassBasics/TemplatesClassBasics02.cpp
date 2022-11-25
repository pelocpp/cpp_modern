// =====================================================================================
// TemplatesClassBasics02.cpp // Class Templates Basics 02
// =====================================================================================

#include <iostream>
#include <string>

namespace ClassTemplatesBasics_02 {

    // Simple Class Template Definition
    namespace ClassTemplatesBasics_Intro_01 {

        template <typename T>
        class MyContainer
        {
        private:
            T m_data;

        public:
            MyContainer() : m_data{} {}
            T getData() const { return m_data; }
            void setData(const T& data) { m_data = data; }
        };

        // explicit class template instantiation
        template class MyContainer<float>;

        void test_01() {
            MyContainer<double> container;
            container.setData(123.456);
            double value = container.getData();
            std::cout << value << std::endl;
        }

        // implicit instantiation of MyContainer<double>
        void test_02() {
            MyContainer<double> container;
        }
    }

    // Class Templates with several formal Parameters
    namespace ClassTemplatesBasics_Intro_02 {

        template <typename T, typename U>
        class MyPair
        {
        public:
            T m_data_01;
            U m_data_02;

        public:
            MyPair(const T& data_01, const U& data_02) 
                : m_data_01{ data_01 }, m_data_02{ data_02 } { }

            void print(std::ostream& os) {
                os << m_data_01 << " : " << m_data_02 << std::endl;
            }
        };

        void test_02() {
            MyPair<std::string, double> averageTemperature{ "March", 5.5 };
            averageTemperature.print(std::cout);
        }
    }

    // Definition of methods of class template (inside / outside class)
    namespace ClassTemplatesBasics_Intro_03 {

        template <typename T>
        class MyContainer
        {
        private:
            T m_data;

        public:
            MyContainer();
            T getData() const;
            void setData(const T& data);
        };

        template <typename T>
        MyContainer<T>::MyContainer() : m_data{} {}

        template <typename T>
        T MyContainer<T>::getData() const {
            return m_data;
        }

        template <typename T>
        void MyContainer<T>::setData(const T& data) {
            m_data = data;
        }

        void test_03() {
            MyContainer<double> container;
            container.setData(654.321);
            double value = container.getData();
            std::cout << value << std::endl;
        }
    }

    // Template specialization of a single method from a templated class

    // Overriding (specialization) of a single method from a class template
    namespace ClassTemplatesBasics_Intro_04 {

        template <typename T>
        class MyContainer
        {
        private:
            T m_data;

        public:
            MyContainer() : m_data{} {}
            T getData() const { return m_data; }
            void setData(const T& data) { m_data = data; }
        };

        template <>
        void MyContainer<std::string>::setData(const std::string& data) {
            m_data = "[" + data + "]";
        }

        void test_04() {
            MyContainer<std::string> container;
            container.setData("I love C++ Templates :)");
            std::string data = container.getData();
            std::cout << data << std::endl;

            MyContainer<int> anotherContainer;
            anotherContainer.setData(123);
            int value = anotherContainer.getData();
            std::cout << value << std::endl;
        }
    }

    // Overriding (specialization) of a single method from a class template
    namespace ClassTemplatesBasics_Intro_05 {

        template <typename T>
        class MyContainer
        {
        private:
            T m_data;

        public:
            MyContainer() : m_data{} {}
            T getData() const { return m_data; }
            void setData(const T& data) { m_data = data; }
        };

        template <>
        void MyContainer<std::string>::setData(const std::string& data) {
            m_data = "[" + data + "]";
        }

        void test_05() {
            MyContainer<std::string> container;
            container.setData("I love C++ Templates :)");
            std::string data = container.getData();
            std::cout << data << std::endl;

            MyContainer<int> anotherContainer;
            anotherContainer.setData(123);
            int value = anotherContainer.getData();
            std::cout << value << std::endl;
        }
    }

    namespace ClassTemplatesBasics_Intro_06 {

        template <typename T, int DIM>
        class FixedVector
        {
        private:
            T m_data[DIM];

        public:
            FixedVector () : m_data{} {}

            size_t size() { return DIM; }

            void set(size_t idx, const T& elem) { m_data[idx] = elem; }

            T get(size_t idx) const { return m_data[idx]; }

            void print(std::ostream& os) {
                for (const auto& elem : m_data) {
                    os << elem << ' ';
                }
                os << '\n';
            }
        };


        void test_06_01() {

            FixedVector<int, 5> vec;

            for (size_t n{}; n < vec.size(); ++n) {
                vec.set(n, 2 * static_cast<int>(n));
            }

            vec.print(std::cout);
        }

        void test_06_02() {

            //Vector<int> v1(10)
            //    Vector<int> v2(20); // v1 und v2 haben den selben Typ
            //Vector2<int, 10> v2_1; // v2_1 und v2_2 haben
            //Vector2<int, 20> v2_2; // unterschiedliche Typen!

        }

        void test_06() {

            test_06_01();
            test_06_02();

        }

    }
}

void main_class_templates_basics_02()
{
    using namespace ClassTemplatesBasics_02;

    //ClassTemplatesBasics_Intro_01::test_01();
    // ClassTemplatesBasics_Intro_02::test_02();
    //ClassTemplatesBasics_Intro_03::test_03();
    //ClassTemplatesBasics_Intro_04::test_04();
       // ClassTemplatesBasics_Intro_05::test_05();
        ClassTemplatesBasics_Intro_06::test_06();
}

// =====================================================================================
// End-of-File
// =====================================================================================
