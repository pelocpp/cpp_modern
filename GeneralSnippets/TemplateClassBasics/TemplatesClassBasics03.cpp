// =====================================================================================
// TemplatesClassBasics03.cpp // Class Templates Basics 03
// =====================================================================================

#include <iostream>
#include <string>
#include <complex>

namespace ClassTemplatesBasics_03 {

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

void main_class_templates_basics_03()
{
    using namespace ClassTemplatesBasics_03::SimpleTemplateDefinition;
    using namespace ClassTemplatesBasics_03::TemplateExplicitSpecialization;
    using namespace ClassTemplatesBasics_03::TemplatePartialSpecialization;
    using namespace ClassTemplatesBasics_03::MethodsTemplates;

    test_02();
    test_03();
    test_04();
    test_05();
}

// =====================================================================================
// End-of-File
// =====================================================================================
