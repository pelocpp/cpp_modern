// =====================================================================================
// FunctionalProgramming01.cpp
// =====================================================================================

module modern_cpp:functional_programming;

namespace FunctionalProgramming {

    class User
    {
    public:
        std::string m_name;
        int m_age;
        std::string m_phone_number;
        std::string m_email;
    };

    static void updateAge(User& user)
    {
        user.m_age = user.m_age + 1;
    }

    static User pureUpdateAge(const User& user) // cannot modify the input argument
    {
        User tmp{ user };
        tmp.m_age = tmp.m_age + 1;
        return tmp;
    }

    static User pureUpdateAge2(User user)       // user is the copy of the passed object
    {
        user.m_age = user.m_age + 1;
        return user;
    }

    static void test_functional_programming_01()
    {
        User john
        {
            .m_name{ "John" },
            .m_age{ 25 }
        };

        pureUpdateAge(john);
    }

    static void test_functional_programming_02()
    {
        User john
        {
            .m_name{ "John" },
            .m_age{ 25 }
        };

        auto updated{ pureUpdateAge2(john) };
        std::println("Age: {}", updated.m_age);

        updated = pureUpdateAge2(john);
        std::println("Age: {}", updated.m_age);
    }

    class Function
    {
    private:
        int m_state;

    public:
        Function () : Function{ 0 } {}
        Function(int state) : m_state{ state } {}

        void modify_state(int state) {
            m_state = state;
        }

        int get_state() {
            return m_state;
        }

        void operator()() {
            // do something that a function would do
            std::println("Do something using state {}", m_state);
        }
    };

    void doSomething(Function f)
    {
        f();
    }

    static void test_functional_programming_03()
    {
        Function func{ 123 };
        doSomething(func);
    }

    // =================================================================================

    // testing 'Filter-Map-Reduce' Pattern
    class Book 
    {
    public:
        std::string m_title;
        std::string m_author;
        int m_year;
        double m_price;
    };

    static void test_functional_programming_04() {

        std::list<Book> booksList
        {
            { "C", "Dennis Ritchie", 1972, 11.99 },
            { "Java", "James Gosling", 1995, 19.99 },
            { "C++", "Bjarne Stroustrup", 1985, 20.00 },
            { "C#", "Anders Hejlsberg", 2000, 29.99 }
        };

        // filter books which appeared past 1990
        std::vector<Book> booksAfter1990{};

        std::copy_if (
            std::begin(booksList),
            std::end(booksList),
            std::back_inserter(booksAfter1990),
            [] (const Book& book) { return book.m_year >= 1990; }
        );

        // extract book title
        std::vector<std::string> bookTitles{};

        std::transform(
            std::begin(booksAfter1990),
            std::end(booksAfter1990),
            std::back_inserter(bookTitles),
            [] (const Book& book) { return book.m_title; }  // convert Book to std::string
        );

        // reduce to result string, e.g. comma seperated list
        std::string titles = std::accumulate(
            std::begin(bookTitles),
            std::end(bookTitles),
            std::string{},
            [](std::string a, std::string b) {
                std::stringstream ss;
                if (a.empty()) {
                    ss << b;
                }
                else {
                    ss << a << ", " << b;
                }
                return ss.str();
            }
        );

        std::println("Titles: {}", titles);
    }

    static void test_functional_programming_05() {

        std::list<Book> booksList
        {
            { "C", "Dennis Ritchie", 1972, 11.99 } ,
            { "Java", "James Gosling", 1995, 19.99 },
            { "C++", "Bjarne Stroustrup", 1985, 20.00 },
            { "C#", "Anders Hejlsberg", 2000, 29.99 }
        };

        auto results = booksList
            | std::ranges::views::filter ([](const Book& book) { return book.m_year < 1990; })
            | std::ranges::views::transform([](const Book& book) { return book.m_title; }) 
            | std::ranges::views::common;

        // reduce to result string, e.g. comma seperated list
        std::string titles = std::accumulate(
            std::begin(results),
            std::end(results),
            std::string{},
            [](std::string a, std::string b) {
                std::stringstream ss;
                if (a.empty()) {
                    ss << b;
                }
                else {
                    ss << a << ", " << b;
                }
                return ss.str();
            }
        );

        std::println("Titles: {}", titles);
    }
}

void main_functional_programming_ranges()
{
    using namespace FunctionalProgramming;

    test_functional_programming_01();
    test_functional_programming_02();
    test_functional_programming_03();
    test_functional_programming_04();
    test_functional_programming_05();
}

// =====================================================================================
// End-of-File
// =====================================================================================
