// =====================================================================================
// Klasse std::string_view
// =====================================================================================

#include <iostream>
#include <string>
#include <cctype>

namespace StringViewDemonstration {

    void test_01()
    {
        std::string s = "12345";
        std::cout << s << std::endl;

        s[2] = '!';
        std::cout << s << std::endl;

        std::string_view sv(s);
        std::cout << sv << std::endl;
        // sv[2] = '?';  // 'sv': you cannot assign to a variable that is const
    }

    uint32_t countUpperCaseChars(std::string_view sv) {
        uint32_t result{};
        for (char c : sv) {
            if (std::isupper(c)) {
                ++result;
            }
        }
        return result;
    }

    void test_02()
    {
        std::string_view sv("DiesIstEinLangerSatz");
        uint32_t count = countUpperCaseChars(sv);
        std::cout << "countUpperCaseChars: " << count << std::endl;

        std::string s = "AuchDasWiederIstEinLangerSatz";
        count = countUpperCaseChars(s);
        std::cout << "countUpperCaseChars: " << count << std::endl;

        count = countUpperCaseChars("NurKurzJetzt");
        std::cout << "countUpperCaseChars: " << count << std::endl;

        // works too 
        count = countUpperCaseChars({ &s[25] }); // "Satz"
        std::cout << "countUpperCaseChars: " << count << std::endl;

        // works too
        count = countUpperCaseChars({ &s[26], 2 }); // "at"
        std::cout << "countUpperCaseChars: " << count << std::endl;
    }
}

void main_string_view()
{
    using namespace StringViewDemonstration;
    test_01();
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
