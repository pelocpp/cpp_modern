#include <iostream>
#include <string>

// =====================================================================================
// Klassentemplates
// =====================================================================================

namespace ClassTemplatesBasics_SimpleTemplateDefinition {

    /*
     * general definition of class template
     */

    template <typename N, typename D>
    class Ratio {
    public:
        Ratio() : m_num(N{}), m_denom(D{}) {}

        Ratio(const N& num, const D& denom)
            : m_num(num), m_denom(denom) {}

        explicit operator double() const {
            return (double)m_num / (double)m_denom;
        }

    private:
        N m_num;
        D m_denom;
    };

    // Sidestep: making argument type deduction explicitly (make_XXX function)
    template <typename N, typename D>
    Ratio<N, D>
        make_ratio(const N& num, const D& denom) {
        return { num, denom };
    }

    void test_01_class_template_basics() {
        Ratio <int, double> ratio1;
        Ratio <int, double> ratio2(1, 5.0);
        Ratio ratio3(3, 4.0);
        Ratio ratio4 = make_ratio(1.0, 2.0);  // explicit type deduction
        auto ratio5{ make_ratio(1.0, 2.0) };  // explicit type deduction
    }
}

namespace ClassTemplatesBasics_TemplateExplicitSpecialization {

    /*
     * Template explicit specialization
     */

    // Repitition (!)
    template <typename N, typename D>
    class Ratio {
    public:
        Ratio() : m_num(N{}), m_denom(D{}) {}

        Ratio(const N& num, const D& denom)
            : m_num(num), m_denom(denom) {}

        explicit operator double() const {
            return (double)m_num / (double)m_denom;
        }

    private:
        N m_num;
        D m_denom;
    };

    // Explicit specialization: Whole class (Full specialization)
    template <>
    class Ratio<double, double> {
    public:
        Ratio() : m_value(0.0) {}

        template <typename N, typename D>
        Ratio(const N& num, const D& denom)
            : m_value((double)num / (double)denom) {}

        explicit operator double() const { return m_value; }

    private:
        double m_value;
    };

    // Explicit specialization: Only member function
    template <>
    Ratio<float, float>::operator double() const { return m_num / m_denom; }

    void test_01_class_template_basics() {

        Ratio <double, double> ratio(1, 5.0);
        double value = static_cast<double>(ratio);
        std::cout << value << std::endl;

        Ratio <float, float> fratio(3, 4);
        value = static_cast<double>(fratio);
        std::cout << value << std::endl;
    }
}

namespace ClassTemplatesBasics_TemplatePartialSpecialization {

    /*
     * Template partial specializations
     */

    // Repitition (!)
    template <typename N, typename D>
    class Ratio {
    public:
        Ratio() : m_num(N{}), m_denom(D{}) {}

        Ratio(const N& num, const D& denom)
            : m_num(num), m_denom(denom) {}

        explicit operator double() const {
            return (double)m_num / (double)m_denom;
        }

    private:
        N m_num;
        D m_denom;
    };

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

    void test_01_class_template_basics() {

        Ratio <double, int> ratio1(1.0, 2);
        Ratio <int, double> ratio2(1, 2.0);
        Ratio <int, int> ratio3(1, 2);

        // ambigous: full specialization resolves
        // Ratio <double, double> ratio4(1, 2);
    }

}

namespace ClassTemplatesBasics_MethodsTemplates {

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

    void test_01_class_template_basics() {

        Printer normalPrinter(std::cout);
        normalPrinter.print(100).print(" --> ").print(123.456).print("\n");

        Printer errorPrinter (std::cerr);
        errorPrinter.print(654.321).print(" <== ").print(100).print("\n");
    }
}

int main_class_templates_basics_01()
{
    using namespace ClassTemplatesBasics_SimpleTemplateDefinition;
    // using namespace ClassTemplatesBasics_TemplateExplicitSpecialization;
    // using namespace ClassTemplatesBasics_TemplatePartialSpecialization;
    // using namespace ClassTemplatesBasics_MethodsTemplates;

    test_01_class_template_basics();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
