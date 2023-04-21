// =====================================================================================
// Trim.cpp
// =====================================================================================

module modern_cpp:trim;

namespace TrimExample {

    // =======================================================
    // trim string from start (in place)
    void leftTrimInPlace(std::string& s) {

        std::string::iterator pos = std::find_if(
            std::begin(s),
            std::end(s),
            [](unsigned char ch) {
                return !std::isspace(ch);
            }
        );

        s.erase(std::begin(s), pos);
    }

    // trim string from end (in place)
    void rightTrimInPlace(std::string& s) {

        std::string::reverse_iterator pos = std::find_if(
            std::rbegin(s),
            std::rend(s),
            [](unsigned char ch) {
                return !std::isspace(ch);
            }
        );

        s.erase(pos.base(), std::end(s));
    }

    // trim string from both ends (in place)
    void trimInPlace(std::string& s) {
        leftTrimInPlace(s);
        rightTrimInPlace(s);
    }

    // =======================================================
    // trim from start (creating a copy)
    std::string leftTrim(std::string s) {
        leftTrimInPlace(s);
        return s;
    }

    // trim from end (copying)
    std::string rightTrim(std::string s) {
        rightTrimInPlace(s);
        return s;
    }

    // trim from both ends (copying)
    std::string trim(std::string s) {
        trimInPlace(s);
        return s;
    }

    void test_01()
    {
        // small benchmark test
        std::string s{ "   ABCDEFGHIJK   " };
        std::cout << '[' << trim(s) << ']' << std::endl;
        std::cout << '[' << s << ']' << std::endl;
        trimInPlace(s);
        std::cout << '[' << s << ']' << std::endl;
    }

    void test_02()
    {
        // small benchmark test
        std::string s{ "   ABCDEFGHIJK   " };
        std::cout << '[' << leftTrim(s) << ']' << std::endl;
        std::cout << '[' << s << ']' << std::endl;
        std::cout << '[' << rightTrim(s) << ']' << std::endl;
        std::cout << '[' << s << ']' << std::endl;
        trimInPlace(s);
        std::cout << '[' << s << ']' << std::endl;
    }

    void test_03()
    {
        std::vector<int> vec{ 1, 2, 3, 4, 5 };

        std::vector<int>::iterator it = std::find(
            std::begin(vec),
            std::end(vec),
            3
        );

        std::cout << *it << std::endl;  // prints '2'

        std::reverse_iterator<std::vector<int>::iterator> rit{ it };
        std::cout << *rit << std::endl; // prints '1'

        std::vector<int>::iterator i2 = rit.base();
        std::cout << *i2 << std::endl;  // prints '2'
    }
}

void main_trim()
{
    using namespace TrimExample;
    test_01();
    test_02();
    test_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
