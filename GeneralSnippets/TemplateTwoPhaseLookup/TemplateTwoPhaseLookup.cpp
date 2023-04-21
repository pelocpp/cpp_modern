// =====================================================================================
// TemplateTwoPhaseLookup.cpp
// =====================================================================================

module modern_cpp:template_two_phase_lookup;

namespace Templates_TwoPhaseNameLookup
{
    // Non-Template Code Example:
    class Base {
    public:
        void doSomething() {
            std::cout << "doSomething" << std::endl;
        }
    };

    class Derived : public Base {
    public:
        void callBase() {
            doSomething();
        }
    };

    // Template Code Example:
    template <typename T>
    class BaseEx {
    public:
        void doSomething() {
            std::cout << "doSomething" << std::endl;
        }
    };

    template <typename T>
    class DerivedEx : public BaseEx<T> {
    public:
        // using BaseEx<T>::doSomething;
        void callBase() {
            // doSomething();      // <=== remove comment: 
            this->doSomething();
            BaseEx<T>::doSomething();
        }
    };

    /*
    *   Note Error Message:
    *   'doSomething': function declaration must be available as none of the arguments depend on a template parameter
    */

    void test_01() {

        Derived derived;
        derived.callBase();
    }

    void test_02() {

        DerivedEx<int> derived;
        derived.callBase();
    }
}

void main_templates_two_phase_name_lookup()
{
    using namespace Templates_TwoPhaseNameLookup;
    test_01();
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
