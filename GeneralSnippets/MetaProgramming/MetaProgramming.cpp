// =====================================================================================
// Metaprogramming
// =====================================================================================

#include <iostream>

namespace Metaprogramming {

    template <int N>
    struct Factorial {

        static int const value = N * Factorial<N - 1>::value;

    };

    template <>
    struct Factorial<1> {
        static int const value = 1;
    };

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
        //std::cout << Factorial<11>::value << std::endl;
        //std::cout << Factorial<12>::value << std::endl;
        //std::cout << Factorial<13>::value << std::endl;
        //std::cout << Factorial<14>::value << std::endl;
        //std::cout << Factorial<15>::value << std::endl;
        //std::cout << Factorial<16>::value << std::endl;
        //std::cout << Factorial<17>::value << std::endl;
    }
}

int main_metaprogramming()
{
    using namespace Metaprogramming;
    test_01();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
