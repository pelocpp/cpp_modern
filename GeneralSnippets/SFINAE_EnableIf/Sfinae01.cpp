// =====================================================================================
// Sfinae01.cpp // SFINAE and enable_if
// =====================================================================================

module modern_cpp:sfinae;

namespace SFINAE_Examples {

    void foo(unsigned i) {
        std::cout << "unsigned " << i << "\n";
    }

    template <typename T>
    void foo(const T& t) {
        std::cout << "template " << t << "\n";
    }

    int negate(int i) {
        return -i;
    }

    template <typename T>
    typename T::value_type negate(const T& t) {
        return -T(t);
    }

    void test_01() {
        // which version of foo is called?
        foo(123);
    }

    void test_02() {
        // which version of negate is called?
        negate(123);
    }

    template <typename T>
    void negate2(const T& t) {
        typename T::value_type n = -t;
    }

    //void test_03() {
    //    negate2(123);  // doesn't compile
    //}

    template <bool, typename T = void>
    struct enable_if
    {};

    template <typename T>
    struct enable_if<true, T> {
        using type = T;
    };

    template <typename T, typename enable_if<std::is_integral<T>::value, T>::type* U = nullptr>
    void doSomething(const T& t) {
        // an implementation for integral types (int, char, unsigned, etc.)
        std::cout << "doSomething integral type: " << t << std::endl;
    }

    template <typename T, typename enable_if<std::is_class<T>::value, T>::type* U = nullptr>
    void doSomething(const T& t) {
        // an implementation for class types
        std::cout << "doSomething class type: " << t() << std::endl;
    }

    class SomeClass {
    public:
        std::string operator()() const {
            return "SomeClass object";
        }
    };

    void test_04() {
        doSomething(123);
        doSomething(SomeClass{});
    }

    template <bool B, typename T = void>
    using enable_if_t = typename enable_if<B, T>::type;

    template <typename T, enable_if_t<std::is_integral<T>::value, T>* U = nullptr>
    void doSomething2(const T& t) {
        // an implementation for integral types (int, char, unsigned, etc.)
        std::cout << "doSomething integral type: " << t << std::endl;
    }

    template <typename T, enable_if_t<std::is_class<T>::value, T>* U = nullptr>
    void doSomething2(const T& t) {
        // an implementation for class types
        std::cout << "doSomething class type: " << t() << std::endl;
    }

    void test_05() {
        doSomething2(456);
        doSomething2(SomeClass{});
    }
}

namespace SFINAE_EnableIf_Examples {

    template<typename T, typename U = std::enable_if_t<std::is_integral_v<T>>>
    void negate1(T& value)
    {
        value = -value;
    }

    template<typename T>
    void negate2(T& value, std::enable_if_t<std::is_integral_v<T>>* dummy = nullptr)
    {
        value = -value;
    }

    template<typename T>
    std::enable_if_t<std::is_integral_v<T>>
        negate3(T& value)
    {
        value = -value;
    }

    template<typename T>
    auto negate4(T& value) -> std::enable_if_t<std::is_integral_v<T>>
    {
        value = -value;
    }

    // ===================================================================================

    template<typename T, typename U = typename std::enable_if<std::is_integral<T>::value>::type>
    void negate10(T& value)
    {
        value = -value;
    }

    template<typename T>
    void negate11(T& value, typename std::enable_if<std::is_integral<T>::value>::type* dummy = nullptr)
    {
        value = -value;
    }

    template<typename T>
    typename std::enable_if<std::is_integral<T>::value>::type
        negate12(T& value)
    {
        value = -value;
    }

    template<typename T>
    auto negate13(T& value) -> typename std::enable_if<std::is_integral<T>::value>::type
    {
        value = -value;
    }

    // ===================================================================================

    void test_06() {
        int x = 10;

        std::cout << "x = " << x << std::endl;
        negate1(x);
        std::cout << "x = " << x << std::endl;

        negate2(x);
        std::cout << "x = " << x << std::endl;

        negate3(x);
        std::cout << "x = " << x << std::endl;

        negate4(x);
        std::cout << "x = " << x << std::endl;

        // doesn't compile
        //float f = 3.14;
        //negate1(f);
        //negate2(f);
        //negate3(f);
        //negate4(f);
    }
}

void main_sfinae()
{
    using namespace SFINAE_Examples;
    test_01();
    test_02();
    test_04();
    test_05();

    using namespace SFINAE_EnableIf_Examples;
    test_06();
}

// =====================================================================================
// End-of-File
// =====================================================================================
