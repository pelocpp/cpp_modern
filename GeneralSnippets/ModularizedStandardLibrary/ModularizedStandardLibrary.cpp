// =====================================================================================
// ModularizedStandardLibrary.cpp
// =====================================================================================

module modern_cpp:modularized_standard_library;

import std;

namespace ModularizedStandardLibrary {

    static void test_01()
    {
        std::println("Hello World");
    }

    static void test_02()
    {
        std::println("List of Entries:");

        std::unordered_map<std::string, size_t> phonebook
        {
            { "Hans Meier" ,     12345678 },
            { "Franz Schneider", 81726354 },
            { "Hubert Mueller",  87654321 }
        };

        for (const auto& [name, number] : phonebook) {
            std::println("{}: {}", name, number);
        }

        std::vector<std::string> names;

        // retrieve names from phonebook
        std::transform(
            phonebook.begin(),
            phonebook.end(),
            std::back_inserter(names),
            [](const std::pair<const std::string, size_t>& entry) {
                return std::get<0>(entry);
            }
        );

        std::println("List of Persons:");
        for (const auto& name : names) {
            std::println("{}", name);
        }
    }
}

void main_modularized_standard_library()
{
    using namespace ModularizedStandardLibrary;

    test_01(); 
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
