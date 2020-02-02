// =====================================================================================
// Metaprogramming
// =====================================================================================

#include <iostream>
#include <type_traits>

// =====================================================================================
// Standardbeispiele
// und
// https://www.grimm-jaud.de/index.php/private-vortraege/15-template-metaprogramming
// =====================================================================================

namespace Metaprogramming {

    template <int N>
    struct Factorial {

        static int const value = N * Factorial<N - 1>::value;

    };

    template <>
    struct Factorial<1> {
        static int const value = 1;
    };

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

    void test_01() {

        std::cout << Factorial<1>::value << std::endl;
        std::cout << Factorial<2>::value << std::endl;
        std::cout << Factorial<3>::value << std::endl;
        std::cout << Factorial<4>::value << std::endl;
        std::cout << Factorial<5>::value << std::endl;
        std::cout << Factorial<6>::value << std::endl;
        std::cout << Factorial<7>::value << std::endl;
        std::cout << Factorial<8>::value << std::endl;
        std::cout << Factorial<9>::value << std::endl;
        std::cout << Factorial<10>::value << std::endl;
        std::cout << Factorial<11>::value << std::endl;
        std::cout << Factorial<12>::value << std::endl;
        std::cout << Factorial<13>::value << std::endl;
        std::cout << Factorial<14>::value << std::endl;
        std::cout << Factorial<15>::value << std::endl;
        std::cout << Factorial<16>::value << std::endl;
        std::cout << Factorial<17>::value << std::endl;
    }

    void test_02() {

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

int main_metaprogramming()
{
    using namespace Metaprogramming;

    test_01();
    // test_02();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
