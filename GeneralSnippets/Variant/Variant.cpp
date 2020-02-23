// =====================================================================================
// std::variant
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <variant>

namespace Variant {

    void test_01() {

        std::variant<int, float, std::string> variantIntFloatString{ 10.5f };

        std::cout 
            << variantIntFloatString.index()
            << ", value " 
            << std::get<float>(variantIntFloatString) 
            << "\n";

        variantIntFloatString = std::string("Hello"); // we're now a string

        std::cout 
            << variantIntFloatString.index()
            << ", value " 
            << std::get<std::string>(variantIntFloatString)
            << "\n";

        variantIntFloatString = 10; // we're now an int

        std::cout 
            << variantIntFloatString.index()
            << ", value " 
            << std::get<int>(variantIntFloatString)
            << "\n";

        variantIntFloatString.emplace<2>(std::string("Hello")); // we're now a string again

        std::cout 
            << variantIntFloatString.index() 
            << ", value " 
            << std::get<std::string>(variantIntFloatString) 
            << "\n";

        // std::get returns a reference, so you can change the value:

        std::get<std::string>(variantIntFloatString) += std::string(" World");

        std::cout
            << variantIntFloatString.index()
            << ", value "
            << std::get<std::string>(variantIntFloatString)
            << "\n";

        variantIntFloatString = 10.1f;
        if (auto pFloat = std::get_if<float>(&variantIntFloatString); pFloat)
            *pFloat *= 2.0f;

        std::cout 
            << variantIntFloatString.index()
            << ", value " 
            << std::get<float>(variantIntFloatString) 
            << "\n";
    }

    void test_02() {

        // accessing a variant

        std::variant<int, float, std::string> variantIntFloatString{ 10.5f };

        std::cout 
            << variantIntFloatString.index()
            << ", value "
            << std::get<float>(variantIntFloatString) 
            << "\n";

        variantIntFloatString = std::string("Hello");

        std::cout
            << variantIntFloatString.index() 
            << ", value "
            << std::get<std::string>(variantIntFloatString) 
            << "\n";

        try
        {
            auto f = std::get<float>(variantIntFloatString);
            std::cout << "float! " << f << "\n";
        }
        catch (std::bad_variant_access&)
        {
            std::cout << "our variant doesn't hold float at this moment...\n";
        }

        variantIntFloatString = 123;

        std::cout 
            << variantIntFloatString.index()
            << ", value "
            << std::get<int>(variantIntFloatString)
            << "\n";

        if (const auto intPtr = std::get_if<0>(&variantIntFloatString))
            std::cout << "int! => " << *intPtr << "\n";
    }
}

int main_variant()
{
    using namespace Variant;
    test_01();
    test_02();
    return 1;
}

// =====================================================================================
// End-of-File
// =====================================================================================
