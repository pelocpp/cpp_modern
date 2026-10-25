// =====================================================================================
// ModularizedStandardLibrary.cpp
// =====================================================================================

module modern_cpp:modularized_standard_library;

import std;

namespace {

    void modularized_standard_library_01()
    {
        std::println("Hello World");
    }

    void modularized_standard_library_02()
    {
        std::println("List of Entries:");

        std::unordered_map<std::string, std::size_t> phonebook
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
            [](const std::pair<const std::string, std::size_t>& entry) {
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
    modularized_standard_library_01();
    modularized_standard_library_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
