// =====================================================================================
// PerfectForwarding02.cpp // Perfect Forwarding 02
// =====================================================================================

module modern_cpp:perfect_forwarding;

namespace PerfectForwarding02 {

    // util class
    class AnyClass
    {
        friend std::ostream& operator<< (std::ostream&, const AnyClass&);

    private:
        double m_value;

    public:
        AnyClass(double value) : m_value{ value } {}
    };

    std::ostream& operator<< (std::ostream& os, const AnyClass& obj)
    {
        os << '(' << obj.m_value << ')';
        return os;
    }

    // put into comment, if template function with copy-by-reference is available
    //template<typename TCLASS, typename TARG>
    //TCLASS Factory(TARG a)
    //{
    //    return TCLASS{ a };
    //}

    template<typename TCLASS, typename TARG>
    TCLASS Factory(TARG& a)
    {
        return TCLASS{ a };
    }

    template<typename TCLASS, typename TARG>
    TCLASS Factory(const TARG& a)
    {
        return TCLASS{ a };
    }

    void test_01() {
        // first example
        auto n = Factory<int>(123);
        std::cout << n << std::endl;

        // second example
        auto obj = Factory<AnyClass>(1.5);
        std::cout << obj << std::endl;
    }

    void test_02() {
        // first example
        int value = 123;
        auto n = Factory<int>(value);
        std::cout << n << std::endl;

        // second example
        AnyClass arg(1.5);
        auto obj = Factory<AnyClass>(arg);
        std::cout << obj << std::endl;
    }

    template<typename TCLASS, typename TARG>
    TCLASS FactoryEx(TARG&& a)
    {
        return TCLASS(std::forward<TARG>(a));
    }

    void test_03()
    {
        // first example
        auto n = FactoryEx<int>(123);
        std::cout << n << std::endl;

        // second example
        auto obj = FactoryEx<AnyClass>(1.5);
        std::cout << obj << std::endl;

        // third example
        int someValue = 987;
        auto m = FactoryEx<int>(someValue);
        std::cout << m << std::endl;

        // fourth example
        AnyClass arg1(2.5);
        auto obj2 = FactoryEx<AnyClass>(arg1);
        std::cout << obj2 << std::endl;

        // fifth example
        AnyClass& arg2 = arg1;
        auto obj3 = FactoryEx<AnyClass>(arg2);
        std::cout << obj3 << std::endl;
    }
}

void main_perfect_forwarding_02()
{
    using namespace PerfectForwarding02;
    test_01();
    test_02();
    test_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
