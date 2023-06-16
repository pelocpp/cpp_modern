// =====================================================================================
// TemplatesClassBasics01.cpp // Class Templates Basics 01
// =====================================================================================

module modern_cpp:templates_class_basics;

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
            double result = calc.add(1.0, 2.0);

            // T = int
            using MyType = int;
            Calculator<MyType> calc2;
            MyType result2 = calc2.add(10, 11);
            result2 = calc2.div(4, 10);

            // T = std::complex<double>
            using namespace std::complex_literals;
            Calculator<std::complex<double>> calc3;
            std::complex<double> z1 = 1. + 2i;
            std::complex<double> z2 = 1. - 2i;
            std::complex<double> result3 = calc3.add(z1, z2);
        }
    }
}

void main_class_templates_basics_01()
{
    using namespace ClassTemplatesBasics::SimpleTemplateCalculator;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
