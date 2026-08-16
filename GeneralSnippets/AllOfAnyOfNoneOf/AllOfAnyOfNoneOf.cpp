// =====================================================================================
// AllOfAnyOfNoneOf.cpp // STL Algorithmen
// =====================================================================================

module modern_cpp:all_of_any_of_none_of;

namespace AllOfAnyOfNoneOf {

    /* std::allof, std::any_of, std::none_of: introduction
    */

    static void std_all_of()
    {
        std::vector<int> numbers{ 2, 4, 6, 8 };

        bool result = std::all_of(
            numbers.begin(),
            numbers.end(),
            [](int n) { return n % 2 == 0; }
        );

        std::println("Result: {}", result); // result == true
    }

    static void std_any_of()
    {
        std::vector<int> numbers{ 1, 3, 4, 7 };

        bool result = std::any_of(
            numbers.begin(),
            numbers.end(),
            [](int n) { return n % 2 == 0; }
        );

        std::println("Result: {}", result); // result == true
    }

    static void std_none_of()
    {
        std::vector<int> numbers{ 1, 3, 5, 7 };

        bool result = std::none_of(
            numbers.begin(),
            numbers.end(),
            [](int n) { return n % 2 == 0; }
        );

        std::println("Result: {}", result); // result == true
    }

    // =====================================================================================

    /* Short Circuit Evaluation
    */

    static void std_all_of_short_circuit()
    {
        std::vector<int> numbers{ 2, 4, 5, 8, 10 };

        bool result = std::all_of(
            numbers.begin(),
            numbers.end(),
            [](int n) {
                return n % 2 == 0;
            }
        );
    }

    static void std_any_of_short_circuit()
    {
        std::vector<int> numbers{ 1, 3, 4, 7, 9 };

        bool result = std::any_of(
            numbers.begin(),
            numbers.end(),
            [](int n) {
                return n % 2 == 0;
            }
        );
    }

    static void std_none_of_short_circuit()
    {
        std::vector<int> numbers{ 1, 3, 4, 7, 9 };

        bool result = std::none_of(
            numbers.begin(),
            numbers.end(),
            [](int n) {
                return n % 2 == 0;
            }
        );
    }

    // =====================================================================================
        
    /* std::allof, std::any_of, std::none_of: tiny real world examples
    */

    static void std_all_of_example()
    {
        struct User {
            std::string name;
            int age;
            bool emailVerified;
        };

        std::vector<User> users {
            { "Alice", 32, true },
            { "Bob", 25, true },
            { "Charlie", 17, true },
            { "Diana", 41, true }
        };

        bool allValid = std::all_of(
            users.begin(),
            users.end(),
            [](const User& user) {
                return user.age >= 18 && user.emailVerified;
            }
        );

        std::println("Are all users adults with verified email addresses? {}", allValid);
    }

    static void std_any_of_example()
    {
        struct Job {
            int id;
            int priority;
            bool failed;
        };

        std::vector<Job> jobs{
            { 101, 1, false },
            { 102, 2, false },
            { 103, 5, true },
            { 104, 3, false }
        };

        bool needsAttention = std::any_of(
            jobs.begin(),
            jobs.end(),
            [](const Job& job) {
                return job.failed || job.priority >= 5;
            }
        );

        std::println("Is there at least one job that needs attention? {}", needsAttention);
    }

    static void std_none_of_example()
    {
        std::vector<std::string> filenames{
            "report.pdf",
            "photo.jpg",
            "data.csv",
            "virus.exe"
        };

        bool safe = std::none_of(
            filenames.begin(),
            filenames.end(),
            [](const std::string& filename) {
                return filename.ends_with(".exe");
            }
        );

        std::println("Are there no .exe files? {}", safe);
    }
}

void main_all_of_any_of_none_of()
{
    using namespace AllOfAnyOfNoneOf;

    std_all_of();
    std_any_of();
    std_none_of();

    std_all_of_short_circuit();
    std_any_of_short_circuit();
    std_none_of_short_circuit();

    std_all_of_example();
    std_any_of_example();
    std_none_of_example();
}

// =====================================================================================
// End-of-File
// =====================================================================================
