// =====================================================================================
// Regular Expressions
// =====================================================================================

module modern_cpp:regexpr;

namespace RegularExpressions {

    static void test_01_simple_regex()
    {
        // simple example

        std::regex expression{ "[a-z]+\\.txt" };

        std::string names[] = {
            "foo.txt",
            "bar.txt",
            "baz.dat",
            "anyfile"
        };

        for (const auto& name : names) {
            bool result{ std::regex_match(name, expression) };
            std::cout << std::boolalpha << name << ": " << result << std::endl;
        }
    }

    static void test_02_simple_regex()
    {
        // simple example - counting the number of all matches

        std::regex expression{ "[^\\s]+" };

        std::string text = { "std::regex_iterator is a read-only iterator" };

        auto iterator = std::sregex_iterator(
            text.begin(),
            text.end(),
            expression
        );

        while (iterator != std::sregex_iterator{}) {

            const auto& token = *iterator;
            std::println("{}", token.str());
            ++iterator;
        }
    }

    static void test_02_capturing_groups()
    {
        // example from 'geeksforgeeks'

        std::string sp{ "geeksforgeeks" };
        std::regex re{ "(geeks)(.*)" };

        // flag type for determining the matching behavior
        // && here it is for matches on strings.
        std::smatch match;

        // we can use member function on match
        // to extract the matched pattern.
        if (std::regex_search(sp, match, re) == true) {

            // The size() member function indicates the
            // number of capturing groups plus one for the overall match
            // match size = Number of capturing group + 1
            // (.*) which "forgeeks" ).
            std::cout << "Match size = " << match.size() << std::endl;

            // Capturing group is index from 0 to match_size -1 
            // .....here 0 to 2
            // pattern at index 0 is the overall match "geeksforgeeks"
            // pattern at index 1 is the first capturing group "geeks"
            // pattern at index 2 is the 2nd capturing group "forgeeks"

            std::cout << "Whole match : " << match.str(0) << std::endl;

            std::cout << "First capturing group is '" << match.str(1)
                << "' which is captured at index " << match.position(1)
                << std::endl;

            std::cout << "Second capturing group is '" << match.str(2)
                << "' which is captured at index " << match.position(2)
                << std::endl;
        }
        else {
            std::cout << "No match is found" << std::endl;
        }
    }

    static void test_03_capturing_group_vs_non_capturing_group_01()
    {
        // example: capturing groups

        std::regex re{ "(https?|s?ftp)://([^/\r\n]+)(/[^\r\n]*)?" };

        std::string paths[] = {
            "http://stackoverflow.com/",
            "https://stackoverflow.com/questions/tagged/regex",
            "sftp://home/remote_username/filename.zip",
            "ftp://home/ftpuser/remote_test_dir",
        };

        for (const auto& path : paths) {

            std::smatch sm;
            bool success{ std::regex_match(path, sm, re) };
            if (success) {
                std::string protocol{ sm[1] };
                std::string domain{ sm[2] };
                std::string dir{ sm[3] };
                std::cout
                    << "Valid URL: " << path << " ==> "
                    << protocol << "-" << domain << "-" << dir << std::endl;
            }
            else {
                std::cout << "Invalid URL: " << path << std::endl;
            }
        }
    }

    static void test_04_capturing_group_vs_non_capturing_group_02()
    {
        // example: non-capturing group

        std::regex re("(?:https?|s?ftp)://([^/\r\n]+)(/[^\r\n]*)?");

        std::string paths[] = {
            "http://stackoverflow.com/",
            "https://stackoverflow.com/questions/tagged/regex",
            "sftp://home/remote_username/filename.zip",
            "ftp://home/ftpuser/remote_test_dir",
        };

        for (const auto& path : paths) {
            std::smatch sm;
            bool success{ std::regex_match(path, sm, re) };
            if (success) {
                std::string domain = sm[1];
                std::string dir = sm[2];
                std::cout <<
                    "Valid URL: " << path << " ==> "
                    << domain << " - " << dir << std::endl;
            }
            else {
                std::cout << "Invalid URL: " << path << std::endl;
            }
        }
    }

    static void test_05_datum_01()
    {
        // example: date, non-capturing groups

        std::regex re{ "\\d{4}/(?:0?[1-9]|1[0-2])/(?:0?[1-9]|[1-2][0-9]|3[0-1])" };

        std::string dates[] = {
            "2000/06/15",
            "200/6/15",
            "2020/0/32",
            "0001/1/1"
        };

        for (const auto& date : dates) {

            bool success{ std::regex_match(date, re) };
            if (success) {
                std::cout << "Valid date:   " << date << std::endl;
            }
            else {
                std::cout << "Invalid date: " << date << std::endl;
            }
        }
    }

    static void test_06_datum_02()
    {
        // example: date, capturing groups

        std::regex re{ "(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])" };

        std::string dates[] = {
            "2000/06/15",
            "200/6/15",
            "2020/0/32",
            "0001/1/1"
        };

        for (const auto& date : dates) {

            std::smatch sm;

            bool success{ std::regex_match(date, sm, re) };
            if (success) {
                int year{ stoi(sm[1]) };
                int month{ stoi(sm[2]) };
                int day{ stoi(sm[3]) };
                std::cout
                    << "Valid date:   " << date << " ==> " << year
                    << "-" << month << "-" << day << std::endl;
            }
            else {
                std::cout << "Invalid date: " << date << std::endl;
            }
        }
    }
}

void main_regular_expressions()
{
    using namespace RegularExpressions;
    test_01_simple_regex();
    test_02_simple_regex();
    test_02_capturing_groups();
    test_03_capturing_group_vs_non_capturing_group_01();
    test_04_capturing_group_vs_non_capturing_group_02();
    test_05_datum_01();
    test_06_datum_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
