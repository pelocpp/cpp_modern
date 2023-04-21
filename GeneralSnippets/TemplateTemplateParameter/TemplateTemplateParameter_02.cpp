// =====================================================================================
// TemplateTemplateParameter_02.cpp // Template Template Parameter 02
// =====================================================================================

module modern_cpp:template_template_parameter;

namespace TemplateTemplateParameter_02 {

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
        MaxCheck() : m_min{ T{} }, m_max{} {}

        MaxCheck(T value1, T value2) : m_min{ value1 }, m_max{ value2 } {}

        void check1() const noexcept {
            std::cout << "check1" << std::endl;
        }

        template<typename U>
        void check2(U) const noexcept {
            std::cout << "check1" << std::endl;

        }

        template<typename U>
        void check3(U, U) const noexcept {
            std::cout << "check"    << std::endl;
        }

    private:
        T m_max;
        T m_min;
    };

    template <typename T, int Low, int High, template <typename> class CheckPolicy>
    class Range {
    private:
        T m_low;
        T m_high;
        CheckPolicy<NoMaxCheck<T>> m_policy;

    public:
        Range() : m_low{ Low }, m_high{ High }
        {
            m_policy.check2(m_low);
            m_policy.check3(m_low, m_high);
        }

        // getter / setter
        T getLow() { return m_low; }
        T getHigh() { return m_high; }
    };

    void test_01() {

        Range<long, 1, 5, MaxCheck> range1;
        Range<long, 1, 5, NoMaxCheck> range2;
    }
}

void main_templates_template_parameter_02()
{
    using namespace TemplateTemplateParameter_02;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
