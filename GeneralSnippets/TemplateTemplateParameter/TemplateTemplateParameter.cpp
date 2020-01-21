// =====================================================================================
// LValue / RValue
// =====================================================================================

#include <iostream>
#include <cctype>
#include <stdexcept>

namespace TemplateTemplateParameter {

    template<typename T>
    struct NoMaxCheck
    {
    public:
        NoMaxCheck() {}
        NoMaxCheck(T, T) {}

        void check(T t1, T t2) const noexcept {
            std::cout << "No check !!!" << std::endl;
        }

        template<typename U>
        void check2(U u) const noexcept {
            std::cout << "check1" << std::endl;

        }

        template<typename U>
        void check3(U u1, U u2) const noexcept {
            std::cout << "check" << std::endl;
        }
    };

    template<typename T>
    struct MaxCheck
    {
    public:
        MaxCheck() : mMin(T{}), mMax() {}
        MaxCheck(T value1, T value2) : mMin(value1) , mMax(value2) {}

        void check1() const noexcept {
            std::cout << "check1" << std::endl;
        }

        template<typename U>
        void check2( U u) const noexcept {
            std::cout << "check1" << std::endl;

        }

        template<typename U>
        void check3(U u1,U u2) const noexcept {
            std::cout << "check"    << std::endl;
        }

    private:
        T mMax;
        T mMin;
    };

    template <typename T, int Low, int High, template <typename> class CheckPolicy>
    class Range {
    private:
        T m_low;
        T m_high;
        CheckPolicy<NoMaxCheck<T>> m_policy;

    public:
        Range() : m_low(Low), m_high(High) {

            m_policy.check2( m_low);
            m_policy.check3(m_low, m_high);
        }

        // getter / setter
        T getLow() { return m_low; }
        T getHigh() { return m_high; }
    };


    void _test_01_template_template_parameter() {

        Range<long, 1, 5, MaxCheck> range1;
        Range<long, 1, 5, NoMaxCheck> range2;
    }
}

int main() {

    using namespace TemplateTemplateParameter;

    _test_01_template_template_parameter();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
