// =====================================================================================
// std::transform
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

namespace AlgorithmTransform {

    void test_01()
    {
        // very simple phone book
        std::cout << "List of Entries: " << std::endl;

        std::map<std::string, size_t> phonebook{
            { "Hans Meier" , 12345678},
            { "Hubert Mueller", 87654321},
            { "Franz Schneider", 81726354}
        };

        for (const auto& [name, number] : phonebook) {
            std::cout << name << ": " << number << std::endl;
        }

        std::vector<std::string> names{};

        // std::transform on a single range - retrieve names from phonebook
        std::transform(
            std::begin(phonebook),
            std::end(phonebook),
            std::back_inserter(names),
            [](std::pair<std::string, size_t> entry) {
                return std::get<0>(entry);
            }
        );

        std::cout << "List of Persons: " << std::endl;
        for (const auto& name : names) {
            std::cout << name << std::endl;
        }
    }

    void test_02()
    {
        std::vector<std::string> persons{
            std::string{ "Hans Meier" },
            std::string{ "Hubert Mueller" },
            std::string{ "Franz Schneider" }
        };

        std::vector<size_t> numbers{ 12345678, 7654321, 81726354 };

        std::map<std::string, size_t> contacts{};

        // std::transform on two ranges - create contacts from separate informations
        std::transform(
            std::begin(persons),
            std::end(persons),
            std::begin(numbers),
            std::inserter(contacts, std::end(contacts)),
            [](std::string person, size_t number) {
                return std::pair<std::string, size_t>(person, number);
            }
        );

        std::cout << "List of Contacts: " << std::endl;
        for (const auto& [name, number] : contacts) {
            std::cout << name << ": " << number << std::endl;
        }
    }
}

void main_transform()
{
    using namespace AlgorithmTransform;
    test_01();
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
