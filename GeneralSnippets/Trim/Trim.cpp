// =====================================================================================
// Trim.cpp
// =====================================================================================

module modern_cpp:trim;

namespace TrimExample {

    // =======================================================
    // trim string from start (in place)
    static void leftTrimInPlace(std::string& s) {

        std::string::iterator pos = std::find_if(
            s.begin(),
            s.end(),
            [](unsigned char ch) {
                return !std::isspace(ch);
            }
        );

        s.erase(s.begin(), pos);
    }

    // trim string from end (in place)
    static void rightTrimInPlace(std::string& s) {

        std::string::reverse_iterator pos = std::find_if(
            s.rbegin(),
            s.rend(),
            [](unsigned char ch) {
                return !std::isspace(ch);
            }
        );

        s.erase(pos.base(), s.end());
    }

    // trim string from both ends (in place)
    static void trimInPlace(std::string& s) {
        leftTrimInPlace(s);
        rightTrimInPlace(s);
    }

    // =======================================================
    // trim from start (creating a copy)
    static std::string leftTrim(std::string s) {
        leftTrimInPlace(s);
        return s;
    }

    // trim from end (copying)
    static std::string rightTrim(std::string s) {
        rightTrimInPlace(s);
        return s;
    }

    // trim from both ends (copying)
    static std::string trim(std::string s) {
        trimInPlace(s);
        return s;
    }

    static void test_01()
    {
        // small benchmark test
        std::string s{ "   ABCDEFGHIJK   " };
        std::cout << '[' << trim(s) << ']' << std::endl;
        std::cout << '[' << s << ']' << std::endl;
        trimInPlace(s);
        std::cout << '[' << s << ']' << std::endl;
    }

    static void test_02()
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

    static void test_03()
    {
        std::vector<int> vec{ 1, 2, 3, 4, 5 };

        std::vector<int>::iterator it{
            std::find(vec.begin(),vec.end(), 3)
        };

        std::cout << *it << std::endl;  // prints '3'

        std::reverse_iterator<std::vector<int>::iterator> rit{ it };
        std::cout << *rit << std::endl; // prints '2'

        std::vector<int>::iterator i2 = rit.base();
        std::cout << *i2 << std::endl;  // prints '3'
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
