// =====================================================================================
// StringView.cpp // Klasse std::string_view
// =====================================================================================

module modern_cpp:string_view;

namespace StringViewDemonstration {

    static void test_01()
    {
        std::string_view sv{ "AAAAAAAAAAAAAAAAAAAAAAAAAAAA" };  // Konstante Zeichenkette

        std::string s{ "AAAAAAAAAAAAAAAAAAAAAAAAAAAA" };        //  Heap

        // sv[0] = '?';   // error
        char ch{ sv[0] };
    }

    static void test_02()
    {
        std::string s{ "AAAAAAAAAAAAAAAAAAAAAAAAAAAA" };

        std::string_view sv{ s };

        std::println("{}", sv);

        s += "BBBBBBBBBBBBBBBBBBBBBBBBBBBB";        // Caution: the content of s is reallocated !

        std::println("{}", sv);
    }

    static void test_03()
    {
        std::string s{ "This is a std::string object" };
        std::println("{}", s);
        std::println("{}", s.size());

        std::string sub{ s.substr(5, 23) };
        std::println("{}", sub);
        std::println("{}", sub.size());

        std::string_view sv{ "This is a std::string_view object" };
        std::println("{}", sv);
        std::println("{}", sv.size());

        std::string_view sv_sub = sv.substr(5, 28);
        std::println("{}", sv_sub);
        std::println("{}", sv_sub.size());
    }

    static void test_04()
    {
        using namespace std::literals;    // easiest way to access the s and sv suffixes

        auto s1 = "ABC";                  // no suffix: C-style string literal
        auto s2 = "DEF"s;                 // s suffix:  std::string literal
        auto s3 = "GHI"sv;                // sv suffix: std::string_view literal

        std::println("{}", s1);
        std::println("{}", s2);
        std::println("{}", s3);
    }

    static size_t countUpperCaseChars(std::string_view sv) {

        size_t result{};

        for (char c : sv) {
            if (std::isupper(c)) {
                ++result;
            }
        }

        return result;
    }

    static void test_05()
    {
        std::string_view sv{ "DiesIstEinLangerSatz" };
        size_t count{ countUpperCaseChars(sv) };
        std::println("countUpperCaseChars: {}", count);

        std::string s{ "AuchDasWiederIstEinLangerSatz" };
        count = countUpperCaseChars(s);
        std::println("countUpperCaseChars: {}", count);

        count = countUpperCaseChars("NurKurzJetzt");
        std::println("countUpperCaseChars: {}", count);

        // works too 
        count = countUpperCaseChars({ &s[25] }); // "Satz"
        std::println("countUpperCaseChars: {}", count);

        // works too
        count = countUpperCaseChars({ &s[26], 2 }); // "at"
        std::println("countUpperCaseChars: {}", count);
    }
}

void main_string_view()
{
    using namespace StringViewDemonstration;
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
}

// =====================================================================================
// End-of-File
// =====================================================================================
