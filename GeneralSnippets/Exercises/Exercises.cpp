// =====================================================================================
// Exercices
// =====================================================================================

#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <type_traits>

namespace Exercices {

    template <typename T>
    inline T minimum(const T& t) { return t; }

    template <typename T, typename ...P>
    inline typename std::common_type<T, P...>::type
    minimum(const T& t, const P& ...p)
    {
        typedef typename std::common_type<T, P...>::type res_type;
        return std::min(res_type(t), res_type(minimum(p...)));
    }

    // oder etwas knapper

    //template <typename T>
    //inline T minimum(const T& t) { return t; }

    //template <typename T, typename ...P>
    //inline auto minimum(const T& t, const P& ...p)
    //{
    //    using res_type = std::common_type_t<T, P...>;
    //    return std::min(res_type(t), res_type(minimum(p...)));
    //}

    void test_exercise_01() {
        auto min1 = minimum(-7, 3.7f, 9u, -2.6);
        std::cout << "min1: " << min1 << ", type: " << typeid(min1).name() << std::endl;

        auto min2 = minimum(-7, 3.7f, 9u, -42.6);
        std::cout << "min2: " << min2 << ", type: " << typeid(min2).name() << std::endl;

        auto min3 = minimum(123, (short)456, (long)789);
        std::cout << "min3: " << min3 << ", type: " << typeid(min3).name() << std::endl;
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