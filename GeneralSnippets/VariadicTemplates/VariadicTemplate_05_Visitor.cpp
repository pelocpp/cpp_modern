// =====================================================================================
// Variadic Templates - std::variant und Visitor
// =====================================================================================

#include <iostream>
#include <variant>
#include <string>

namespace VariadicTemplatesVisitor {

    // https://pabloariasal.github.io/2018/06/26/std-variant/
    // or
    // https://www.bfilipek.com/2018/09/visit-variants.html

    template <class... Ts>
    struct Visitor;

    template <class T, class... Ts>
    struct Visitor<T, Ts...> : T, Visitor<Ts...>
    {
        Visitor(T t, Ts... rest) : T(t), Visitor<Ts...>(rest...) {}

        using T::operator();
        using Visitor<Ts...>::operator();
    };

    template <class T>
    struct Visitor<T> : T
    {
        Visitor(T t) : T(t) {}

        using T::operator();
    };

    template<typename ...Ts>
    auto make_visitor(Ts... lamdbas)
    {
        return Visitor<Ts...>(lamdbas...);
    }

    auto myVisitor = make_visitor(
        [](int n)
        {
            // called if variant holds an int
            std::cout << "Variant holds an int right now: " << n << std::endl;
        },
        [](float f)
        {
            // called if variant holds a float
            std::cout << "Variant holds a float right now: " << f << std::endl;
        },
        [](char ch)
        {
            // called if variant holds a char
            std::cout << "Variant holds a char right now: " << ch << std::endl;
        }
    );

    void test_01() {

        std::variant<int, float, char> var = 42;
        std::visit(myVisitor, var);
        var = 3.141f;
        std::visit(myVisitor, var);
        var = 'c';
        std::visit(myVisitor, var);
    }
}

void main_variadic_templates_visitor()
{
    using namespace VariadicTemplatesVisitor;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
