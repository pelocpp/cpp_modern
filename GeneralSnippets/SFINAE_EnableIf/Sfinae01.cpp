// =====================================================================================
// SFINAE and enable_if
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

namespace SFINAE {

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
        typename T::value_type n = -t();
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

    template <class T, typename enable_if<std::is_integral<T>::value, T>::type* = nullptr>
    void doSomething(const T& t) {
        // an implementation for integral types (int, char, unsigned, etc.)
        std::cout << "doSomething integral type: " << t << std::endl;
    }

    template <class T, typename enable_if<std::is_class<T>::value, T>::type* = nullptr>
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

    template <class T, typename enable_if_t<std::is_integral<T>::value, T>* = nullptr>
    void doSomething2(const T& t) {
        // an implementation for integral types (int, char, unsigned, etc.)
        std::cout << "doSomething integral type: " << t << std::endl;
    }

    template <class T, typename enable_if_t<std::is_class<T>::value, T>* = nullptr>
    void doSomething2(const T& t) {
        // an implementation for class types
        std::cout << "doSomething class type: " << t() << std::endl;
    }

    void test_05() {
        doSomething2(456);
        doSomething2(SomeClass{});
    }
}

int main_sfinae()
{
    using namespace SFINAE;
    test_01();
    test_02();
    test_04();
    test_05();
    return 1;
}

// =====================================================================================
// End-of-File
// =====================================================================================
