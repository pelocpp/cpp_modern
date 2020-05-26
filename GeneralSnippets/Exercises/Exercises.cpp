// =====================================================================================
// Exercices
// =====================================================================================

#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <type_traits>

namespace Exercices {

#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <type_traits>

    template <typename T>
    inline T minimum2(const T& t) { return t; }

    //template <typename T, typename ...P>
    //typename std::common_type<T, P...>::type
    //    minimum(const T& t, const P& ...p)
    //{
    //    typedef typename std::common_type<T, P...>::type res_type;
    //    return std::min(res_type(t), res_type(minimum(p...)));
    //}

    // oder etwas knapper

    template <typename T, typename ...P>
      inline  auto minimum2(const T& t, const P& ...p)
    {
        using res_type = std::common_type_t<T, P...>;
        return std::min(res_type(t), res_type(minimum2(p...)));
    }

    void test_exercise_01() {
        auto m = minimum2(-7, 3.7f, 9u, -2.6);
        std::cout << "m is " << m << ", its type is " << typeid(m).name() << std::endl;

        auto m2 = minimum2(-7, 3.7f, 9u, -42.6);
        std::cout << "m2 is " << m2 << ",its type is " << typeid(m2).name() << std::endl;

        auto m3 = minimum2(123, (short)456, (long)789);
        std::cout << "m3 is " << m3 << ", its type is " << typeid(m3).name() << std::endl;
    }
}

int main()
// int main_exercices()
{
    using namespace Exercices;

    test_exercise_01();

    return 1;
}

// =====================================================================================
// End-of-File
// =====================================================================================