// =====================================================================================
// std::variant
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <variant>

namespace VariantDemo {

    void test_01() {

        std::variant<int, float, std::string> var{ 10.5f };

        std::cout
            << var.index()
            << ", value "
            << std::get<float>(var)
            << std::endl;

        var = std::string("Hello"); // we're now a string

        std::cout 
            << var.index()
            << ", value " 
            << std::get<std::string>(var)
            << std::endl;

        var = 10; // we're now an int

        std::cout 
            << var.index()
            << ", value " 
            << std::get<int>(var)
            << std::endl;

        var.emplace<2>(std::string("Hello")); // we're now a string again

        std::cout 
            << var.index()
            << ", value " 
            << std::get<std::string>(var)
            << std::endl;

        // std::get returns a reference, so you can change the value:

        std::get<std::string>(var) += std::string(" World");

        std::cout
            << var.index()
            << ", value "
            << std::get<std::string>(var)
            << std::endl;

        var = 10.1f;
        if (auto pFloat = std::get_if<float>(&var); pFloat)
            *pFloat *= 2.0f;

        std::cout 
            << var.index()
            << ", value " 
            << std::get<float>(var)
            << std::endl;
    }

    void test_02() {

        // accessing a variant

        std::variant<int, float, std::string> var{ std::string("Hello") };

        std::cout 
            << var.index()
            << ", value "
            << std::get<std::string>(var)
            << std::endl;

        try
        {
            auto f = std::get<float>(var);
            std::cout << "float! " << f << "\n";
        }
        catch (std::bad_variant_access&)
        {
            std::cout << "Variant doesn't hold float at this moment ..." << std::endl;;
        }

        var = 123;

        std::cout 
            << var.index()
            << ", value "
            << std::get<int>(var)
            << std::endl;

        if (const auto intPtr = std::get_if<0>(&var))
            std::cout << "int! => " << *intPtr << std::endl;
    }
}

void main_variant()
{
    using namespace VariantDemo;
    test_01();
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
