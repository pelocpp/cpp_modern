// =====================================================================================
// Typmerkmale // Type Traits
// =====================================================================================

// =====================================================================================
// Aus "Peter Pohmann" // Kapitel 3.12
// =====================================================================================

#include <iostream>
#include <string>

namespace MyTypeTraits {

    template <typename T>
    class Kind {
        static_assert(std::is_class<T>::value, "class expected.");
        static_assert(std::is_array<T>::value, "array expected.");
    };

    template <typename T>
    class AnotherKind {
        static_assert(std::is_pointer<T>::value, "pointer type expected.");
    };

#if defined (DEMO)
    template <typename T>
    bool isEqual(T a, T b);

    template <typename T>
    bool isEqual<int>(int a, int b) {
        return a == b;
    }

    template <typename T>
    bool isEqual<int>(int a, int b) {
        return std::abs(a - b) < 0.0001;
    }
#endif

    template <typename T>
    bool isEqual(T a, T b) {
        if (std::integral_constant<T>::value)
            return a == b;
        else
            return std::abs(a - b) < 0.0001;
    }

    template <typename T1, typename T2>
    bool isEqual(T1 a, T2 b) {
        if (std::integral_constant<T1>::value && std::integral_constant<T2>::value)
            return a == b;
        else
            return std::abs(a - b) < 0.0001;
    }

    void test_01() {
        // Kind<int> aKind;  // doesn't compile
        // Kind<std::string> anotherKind;  // depends
        // Kind<std::string[]> anotherKind;  // depends
    }

    void test_02() {
        // AnotherKind<const int*> anotherKind;  // compiles
    }

    // =====================================================================================

    template <typename T>
    struct ReferenceType
    {
        typedef T type;
    };

    template <typename T>
    struct ReferenceType<T&>
    {
        typedef T& type;
    };

    template <typename T>
    void checkReference()
    {
        if (std::is_reference<T>::value == true) {
            std::cout << "reference " << std::endl;
        }
        else {
            std::cout << "not reference" << std::endl;
        }
    }

    void test_03() {

        std::cout << "int: ";
        checkReference<int>();

        std::cout << "int&: ";
        checkReference<int&>();

        std::cout << "ReferenceType<int>::type > ";
        checkReference< ReferenceType<int>::type >();

        std::cout << "ReferenceTypeint&>::type > : ";
        checkReference< ReferenceType<int&>::type >();
    }
}

int main_type_traits()
{
    using namespace MyTypeTraits;
    test_01();
    test_02();
    test_03();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
