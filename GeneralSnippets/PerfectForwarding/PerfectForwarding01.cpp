// =====================================================================================
// PerfectForwarding01.cpp // Perfect Forwarding 01
// =====================================================================================

module modern_cpp:perfect_forwarding;

namespace PerfectForwarding01 {

    // utility class
    class AnyClass
    {
    public:
        AnyClass() = default;
        ~AnyClass() = default;

        AnyClass(const AnyClass&) {
            std::cout << "copy c'tor" << std::endl;
        }

        AnyClass(AnyClass&&) noexcept {
            std::cout << "move c'tor" << std::endl;
        }
    };

    // ----

    template <typename T>
    T* Clone(const T& src) {
        return new T{ src };
    }

    // NICHT ÜBERSETZUNGSFÄHIG - Siehe https://cppinsights.io/ !!!
    //template <typename T>
    //T* Clone2(T&& src) {
    //    return new T{ src };
    //}

    template <typename T>
    auto Clone2a(T&& src) {
        using TT = typename std::remove_reference<T>::type;
        return new TT{ src };
    }

    template <typename T>
    auto Clone2b(T&& src) -> typename std::remove_reference<T>::type* {
        using TT = typename std::remove_reference<T>::type;
        return new TT{ src };
    }

    template <typename T>
    auto Clone2c(T&& src) -> typename std::remove_reference<T>::type* {
        return new typename std::remove_reference<T>::type{ src };
    }

    template <typename T>
    auto Clone2d(T&& src) {
        return new typename std::remove_reference<T>::type{ src };
    }

    template <typename T>
    typename std::remove_reference<T>::type* Clone2e(T&& src) {
        return new typename std::remove_reference<T>::type{ src };
    }

    // ----

    //template <typename T>
    //auto Clone3(T&& src) {
    //    using TT = typename std::remove_reference<T>::type;
    //    return new TT{ std::move(src) };
    //}

    // ----

    template <typename F>
    F&& my_forward(typename std::remove_reference<F>::type& t) noexcept {
        return static_cast<F&&>(t);
    }

    template <typename F>
    F&& my_forward(typename std::remove_reference<F>::type&& t) noexcept {
        return static_cast<F&&>(t);
    }

    // ----

    template <typename T>
    auto Clone98(T&& src) {
        return new typename std::remove_reference<T>::type(my_forward<T>(src));
    }

    // ----

    template <typename T>
    auto Clone99(T&& src) {
        return new typename std::remove_reference<T>::type(std::forward<T>(src));
    }

    void test_01() {
        // a)
        AnyClass obj1;
        AnyClass* obj2{ new AnyClass(obj1) };               // copy c'tor invoked
        AnyClass* obj3{ new AnyClass(std::move(*obj2)) };   // move c'tor invoked

        // b)
        //AnyClass obj10;
        //AnyClass* obj11{ Clone(obj10) };                    // copy c'tor invoked
        //AnyClass* obj12{ Clone(std::move(*obj11)) };        // copy c'tor invoked (???)

        // c)
        // NICHT ÜBERSETZUNGSFÄHIG
        //AnyClass obj10;
        //AnyClass* obj11{ Clone2(obj10) };                    // copy c'tor invoked
        //AnyClass* obj12{ Clone2(std::move(*obj11)) };        // copy c'tor invoked (???)
    }

    void test_02() {
        // d1)
        AnyClass obj20;
        AnyClass* obj21{ Clone2a(obj20) };
        AnyClass* obj22{ Clone2a(std::move(*obj21)) };

        // d2)
        AnyClass obj30;
        AnyClass* obj31{ Clone2b(obj30) };
        AnyClass* obj32{ Clone2b(std::move(*obj31)) };

        // d3)
        AnyClass obj40;
        AnyClass* obj41{ Clone2c(obj40) };
        AnyClass* obj42{ Clone2c(std::move(*obj41)) };

        // d4)
        AnyClass obj50;
        AnyClass* obj51{ Clone2d(obj50) };
        AnyClass* obj52{ Clone2d(std::move(*obj51)) };

        // d5)
        AnyClass obj60;
        AnyClass* obj61{ Clone2e(obj60) };
        AnyClass* obj62{ Clone2e(std::move(*obj61)) };
    }

    void test_03() {
        // i)
        //AnyClass obj70;
        //AnyClass* obj71{ Clone3(obj70) };
        //AnyClass* obj72{ Clone3(std::move(*obj71)) };

        // ======

        // y)
        AnyClass obj80;
        AnyClass* obj81{ Clone98(obj80) };              // copy c'tor invoked
        AnyClass* obj82{ Clone98(std::move(*obj81)) };  // move c'tor invoked (!!!)

        // z)
        AnyClass obj90;
        AnyClass* obj91{ Clone99(obj90) };              // copy c'tor invoked
        AnyClass* obj92{ Clone99(std::move(*obj91)) };  // move c'tor invoked (!!!)
    }
}

void main_perfect_forwarding_01()
{
    using namespace PerfectForwarding01;
    test_01();
    test_02();
    test_03();
}


// =====================================================================================
// End-of-File
// =====================================================================================
