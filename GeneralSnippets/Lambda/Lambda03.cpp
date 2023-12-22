// =====================================================================================
// Lambda03.cpp // Lambda and 'this' Closure
// =====================================================================================

module modern_cpp:lambda;

namespace LambdaAndThisClosure {

    class Class {

        friend std::ostream& operator << (std::ostream&, const Class&);

    private:
        int m_value;

    public:
        Class() : m_value{ 1 } {}

        // just for demonstration purposes / observe, when copy c'tor is called !!!
        Class(const Class& obj) {
            std::cout << "copy c'tor called ..." << std::endl;
            m_value = obj.m_value;
        }

        void incValue() {
            ++m_value;
        }

        void doSomething() {

            auto lambda = [this]() mutable {  // use [*this] to work on a copy
                incValue();
                return m_value;
            };

            lambda();
        }
    };

    std::ostream& operator << (std::ostream& os, const Class& obj) {
        os << "m_value = " << obj.m_value;
        return os;
    }

    static void test_01() {
        Class object;
        std::cout << object << std::endl;
        object.doSomething();
        std::cout << object << std::endl;
    }

}

void main_lambdas_this_closure()
{
    using namespace LambdaAndThisClosure;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
