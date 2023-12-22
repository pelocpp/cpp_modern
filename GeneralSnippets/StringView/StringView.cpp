// =====================================================================================
// StringView.cpp // Klasse std::string_view
// =====================================================================================

module;

#include <cstdint>   // for uint8_t

module modern_cpp:string_view;

namespace StringViewDemonstration {

    static void test_01()
    {
        std::string_view sv{ "The quick brown fox jumps over the lazy dog" };  // Konstante Zeichenkette

        std::string s{ "The quick brown fox jumps over the lazy dog" };        //  Heap

        // sv[0] = '?';   // error
        char ch{ sv[0] };
    }

    static void test_02()
    {
        std::string s{ "How vexingly quick daft zebras jump!" };

        std::string_view sv{ s };

        std::cout << sv << std::endl;

        s += "Sixty zippers were quickly picked from the woven jute bag";  // the content of s is reallocated !

        std::cout << sv << std::endl;
    }

    static void test_03()
    {
        using namespace std::literals;      // easiest way to access the s and sv suffixes

        std::cout << "foo" << std::endl;    // no suffix: C-style string literal
        std::cout << "goo"s << std::endl;   // s suffix:  std::string literal
        std::cout << "moo"sv << std::endl;  // sv suffix: std::string_view literal
    }

    static uint32_t countUpperCaseChars(std::string_view sv) {

        uint32_t result{};

        for (char c : sv) {
            if (std::isupper(c)) {
                ++result;
            }
        }

        return result;
    }

    static void test_04()
    {
        std::string_view sv{ "DiesIstEinLangerSatz" };
        uint32_t count{ countUpperCaseChars(sv) };
        std::cout << "countUpperCaseChars: " << count << std::endl;

        std::string s{ "AuchDasWiederIstEinLangerSatz" };
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
    test_03();
    test_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
