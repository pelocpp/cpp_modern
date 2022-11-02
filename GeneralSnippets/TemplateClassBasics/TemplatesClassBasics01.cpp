// =====================================================================================
// Template Class Basics
// =====================================================================================

#include <iostream>
#include <string>
#include <complex>

namespace ClassTemplatesBasics {

    namespace SimpleTemplateCalculator {

        // primary templyte
        template <typename T>
        class Calculator
        {
        public:
            static T add(T x, T y) { return x + y; }
            static T sub(T x, T y) { return x - y; }
            static T mul(T x, T y) { return x * y; }
            static T div(T x, T y) { return x / y; }
        };

        // explicit specialization of whole template class Calculator<T> for T = int
        template <>
        class Calculator<int>
        {
        public:
            static int add(int x, int y) { return x + y; }
            static int sub(int x, int y) { return x - y; }
            static int mul(int x, int y) { return x * y; }
            static int div(int x, int y) { 
                return static_cast<int> (
                    (static_cast<double>(x) / x) + 0.5
                );
            }
        };

        // or explicit specialization of single template class method 'div' for T = int

        //template <>
        //int Calculator<int>::div(int n, int m) {
        //    std::cout << "do rounding:" << std::endl;
        //    return (int)(((double)n / m) + 0.5);
        //}

        // see
        // https://stackoverflow.com/questions/25724360/template-class-with-a-single-method-specialized-in-c
        // or
        // https://stackoverflow.com/questions/1723537/template-specialization-of-a-single-method-from-a-templated-class

        void test_01() {

            // just verifying template concept: is this assignment allowed?
            Calculator<int> calc10;
            Calculator<int> calc11;
            calc10 = calc11;

            // T = double
            Calculator<double> calc;
            [[maybe_unused]] double result = calc.add(1.0, 2.0);

            // T = int
            using MyType = int;
            Calculator<MyType> calc2;
            [[maybe_unused]] MyType result2 = calc2.add(10, 11);
            result2 = calc2.div(4, 10);

            // T = std::complex<double>
            using namespace std::complex_literals;
            Calculator<std::complex<double>> calc3;
            std::complex<double> z1 = 1. + 2i;
            std::complex<double> z2 = 1. - 2i;
            [[maybe_unused]] std::complex<double> result3 = calc3.add(z1, z2);
        }
    }

    namespace SimpleTemplateDefinition {

        // general definition of class template
        template <typename N, typename D>
        class Ratio {
        public:
            Ratio() : m_num{ N{} }, m_denom{ D{ 1 } } {}

            Ratio(const N& num, const D& denom) : m_num{ num }, m_denom{ denom } {}

            explicit operator double() const {
                return static_cast<double>(m_num) / static_cast<double>(m_denom);
            }

        private:
            N m_num;
            D m_denom;
        };

        void test_02() {
            Ratio <int, double> ratio1;
            Ratio <int, double> ratio2(1, 5.0);
            Ratio ratio3(3, 4.0);  // explicit type deduction
        }
    }

    namespace TemplateExplicitSpecialization {

        // Explicit Template Specialization
        // hier: Wiederholung der Basis-Schablone
        template <typename N, typename D>
        class Ratio {
        public:
            Ratio() : m_num{ N{} }, m_denom{ D{ 1 } } {}

            Ratio(const N& num, const D& denom) : m_num{ num }, m_denom{ denom } {}

            explicit operator double() const {
                return static_cast<double>(m_num) / static_cast<double>(m_denom);
            }

        private:
            N m_num;
            D m_denom;
        };

        // Explicit specialization: a) Whole class (Full specialization)
        template <>
        class Ratio<short, short> {
        public:
            Ratio() : m_value(0.0) {}

            template <typename N, typename D>
            Ratio(const N& num, const D& denom)
                : m_value((double)num / (double)denom) {}

            explicit operator double() const { return m_value; }

        private:
            double m_value;
        };

        // Explicit specialization: b) Only member function
        template <>
        Ratio<float, float>::operator double() const { return m_num / m_denom; }

        void test_03() {

            Ratio <double, double> ratio(1, 5.0);
            double value = static_cast<double>(ratio);
            std::cout << value << std::endl;

            Ratio <short, short> fratio(3, 4.45);
            value = static_cast<double>(fratio);
            std::cout << value << std::endl;
        }
    }

    namespace TemplatePartialSpecialization {

        // Partial Template Specialization
        // hier: Wiederholung der Basis-Schablone
        template <typename N, typename D>
        class Ratio {
        public:
            Ratio() : m_num(N{}), m_denom(D{ 1 }) {}

            Ratio(const N& num, const D& denom)
                : m_num(num), m_denom(denom) {}

            explicit operator double() const {
                return (double)m_num / (double)m_denom;
            }

        private:
            N m_num;
            D m_denom;
        };

        // Partial Template Specialization: a) Reduktion auf einen Parameter
        template <typename D>
        class Ratio<double, D> {
        public:
            Ratio() : m_value(0.0) {}

            Ratio(const double& num, const D& denom)
                : m_value(num / (double)denom) {}

            explicit operator double() const { return m_value; }

        private:
            double m_value;
        };

        // Partial Template Specialization: b) Reduktion auf einen Parameter
        template <typename N>
        class Ratio<N, double> {
        public:
            Ratio() : m_value(0.0) {}

            Ratio(const N& num, const double& denom)
                : m_value((double)num / denom) {}

            explicit operator double() const { return m_value; }

        private:
            double m_value;
        };

        void test_04() {

            Ratio <double, int> ratio1(1.0, 2);
            Ratio <int, double> ratio2(1, 2.0);
            Ratio <int, int> ratio3(1, 2);

            // ambigous: full specialization resolves
            // Ratio <double, double> ratio4(1, 2);
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

        void test_05() {

            Printer normalPrinter(std::cout);
            normalPrinter.print(100).print(" --> ").print(123.456).print("\n");

            Printer errorPrinter(std::cerr);
            errorPrinter.print(654.321).print(" <== ").print(100).print("\n");
        }
    }
}

void main_class_templates_basics_01()
{
    using namespace ClassTemplatesBasics::SimpleTemplateCalculator;
    using namespace ClassTemplatesBasics::SimpleTemplateDefinition;
    using namespace ClassTemplatesBasics::TemplateExplicitSpecialization;
    using namespace ClassTemplatesBasics::TemplatePartialSpecialization;
    using namespace ClassTemplatesBasics::MethodsTemplates;

    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
}

// =====================================================================================
// End-of-File
// =====================================================================================
