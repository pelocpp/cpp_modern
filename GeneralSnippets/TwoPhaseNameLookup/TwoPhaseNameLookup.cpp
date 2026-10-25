// =====================================================================================
// TwoPhaseNameLookup.cpp
// =====================================================================================

module modern_cpp:two_phase_name_lookup;

import std;

namespace {

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

    void two_phase_name_lookup_01() {

        Derived derived;
        derived.callBase();
    }

    void two_phase_name_lookup_02() {

        DerivedEx<int> derived;
        derived.callBase();
    }
}

void main_two_phase_name_lookup()
{
    two_phase_name_lookup_01();
    two_phase_name_lookup_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
