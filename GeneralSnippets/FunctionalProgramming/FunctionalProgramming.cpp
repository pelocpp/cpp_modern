// =====================================================================================
// FunctionalProgramming.cpp
// =====================================================================================

module modern_cpp:functional_programming;

namespace FunctionalProgramming {

    // =================================================================================
    // Pure Functions

    class User
    {
    public:
        std::string m_name;
        std::string m_phone;
        std::size_t m_age;
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

    static void test_functional_pure_01()
    {
        User john
        {
            .m_name{ "John" },
            .m_phone{ "12345678" },
            .m_age{ 25 }
        };

        pureUpdateAge(john);
    }

    static void test_functional_pure_02()
    {
        User john
        {
            .m_name{ "John" },
            .m_phone{ "12345678" },
            .m_age{ 25 }
        };

        auto updated{ pureUpdateAge(john) };
        std::println("Age: {}", updated.m_age);

        updated = pureUpdateAge(john);
        std::println("Age: {}", updated.m_age);
    }

    class Function
    {
    private:
        std::size_t m_state;

    public:
        Function () : Function{ 0 } {}
        Function(std::size_t state) : m_state{ state } {}

        void modify_state(std::size_t state) { m_state = state; }
        std::size_t get_state() const { return m_state; }

        void operator()() const {
            // do something that a function would do
            std::println("Do something using state {}", m_state);
        }
    };

    static void doSomething(const Function& f) {
        f();
    }

    static void test_functional_pure_03() {
        Function func{ 123 };
        doSomething(func);
    }

    // =================================================================================
    // =================================================================================
    // Currying and Partial Application

    // =====================================================================================
    // Partial application

    static int add(int a, int b) {
        return a + b;
    }

    static void functional_partial_application_01()
    {
        auto addFive = [](int b) {
            return add(5, b);  // partially applied: a = 5
            };

        auto result{ addFive(3) };

        std::print("{} ", result);
    }

    // =====================================================================================
    // Partial application: Using lambda instead of free function

    static auto partialAdd(int a) {
        return [a](int b) {
            return a + b;
            };
    }

    static void functional_partial_application_02()
    {
        auto addTen = partialAdd(10);

        auto result{ addTen(5) };

        std::print("{} ", result);
    }

    // =====================================================================================
    // Partial application: Only using lambdas, no more free functions

    static void functional_partial_application_03()
    {
        auto partialAdd = [](int a) {
            return [a](int b) {
                return a + b;
                };
            };

        auto addTwenty = partialAdd(20);

        auto result{ addTwenty(10) };

        std::print("{} ", result);
    }

    // =====================================================================================
    // Partial application: Generalization of partial applications

    static void functional_partial_application_04()
    {
        auto partialAdd = [](int a) {
            return [a](int b) {
                return a + b;
                };
            };

        auto addTen = partialAdd(10);
        auto addTwenty = partialAdd(20);
        auto addThirty = partialAdd(30);

        auto result{ 0 };

        result = addTen(10);
        std::println("{} ", result);

        result = addTwenty(10);
        std::println("{} ", result);

        result = addThirty(10);
        std::println("{} ", result);
    }

    // =====================================================================================
    // Partial application: More Parameters

    static auto multiply(auto a, auto b, auto c) {
        return a * b * c;
    }

    static void functional_partial_application_05()
    {
        auto multiply_By_5_and_10 = [](int c) {
            return multiply(5, 10, c);  // partially applied: a=5, b=10
            };

        auto result{ multiply_By_5_and_10(15) };

        std::println("5*10*15={} ", result);    // output: 750
    }

    // =====================================================================================
    // =====================================================================================
    // No Currying

    static auto addRegular(auto a, auto b) {
        return a + b;
    }

    static auto addCurried = [](auto a) {
        return [a](auto b) {
            return a + b;
            };
        };

    static void functional_currying_regular()
    {
        auto result{ addRegular(5, 10) };

        std::println("{} ", result);  // output: 10
    }

    static void functional_currying_01()
    {
        auto result{ addCurried(5)(5) };

        std::println("{} ", result);  // output: 10
    }

    static void functional_currying_02()
    {
        auto addFive{ addCurried(5) };

        auto result{ addFive(10) };

        std::println("{} ", result);  // output: 15
    }

    // =====================================================================================
    // More Currying

    static auto addRegular(int a, int b, int c)
    {
        return a + b + c;
    }

    static void functional_currying_03()
    {
        auto result{ addRegular(1, 2, 3) };
        std::println("{} ", result);        // output: 6
    }

    static auto addMoreCurried(int a) {
        return [a](int b) {
            return [a, b](int c) {
                return a + b + c;
                };
            };
    }

    static void functional_currying_04()
    {
        auto result{ addMoreCurried(1)(2)(3) };
        std::println("{} ", result);                 // output: 6
    }

    static void functional_currying_05()
    {
        auto addToOne{ addMoreCurried(1) };

        auto addToThree{ addToOne(2) };

        auto result{ 0 };
        result = addToThree(3);
        std::println("{} ", result);                 // output: 6

        result = addToThree(4);
        std::println("{} ", result);                 // output: 7
    }

    static void functional_currying_06()
    {
        // look behind the scenes: using lambda syntax
        auto addMoreCurried = [](int a) {
            return [a](int b) {
                return [a, b](int c) {
                    return a + b + c;
                    };
                };
            };

        auto result{ addMoreCurried(10)(11)(12) };

        std::println("{} ", result);
    }

    // ===========================================================================
    // Currying without lambdas - an explanatory version

    static void functional_currying_07()
    {
        // look behind the scenes: using syntax with callable objects
        //auto addCurried = [](int a) {
        //    return [a](int b) {
        //        return a + b;
        //        };
        //    };

        //auto result{ addCurried(10)(11) };

        // std::println("{} ", result);

        // ===============================================================
        // or longer, explanatory version

        class OuterLambda
        {
        private:
            class MiddleLambda
            {
            public:
                inline int operator()(int b) const
                {
                    return m_a + b;
                }

            private:
                int m_a;

            public:
                MiddleLambda(int a) : m_a{ a } {}
            };

        public:
            inline MiddleLambda operator()(int a) const
            {
                MiddleLambda tmp{ a };
                return tmp;
            }
        };

        // short syntax
        OuterLambda addCurried = OuterLambda{};
        auto result{ addCurried(10)(11) };
        std::println("{} ", result);

        // longer, explanatory syntax
        auto firstLambda{ OuterLambda{} };
        auto secondLambda{ firstLambda(21) };
        auto result1{ secondLambda(22) };
        std::println("{} ", result1);
    }

    static void functional_currying_08()
    {
        // look behind the scenes: using syntax with callable objects
        //auto addCurried = [](int a) {
        //    return [a](int b) {
        //        return [a, b](int c) {
        //            return a + b + c;
        //            };
        //        };
        //    };

        //auto result{ addCurried(10)(11)(12)};

        // std::println("{} ", result);

        // ===============================================================
        // or longer, explanatory version

        class OuterLambda
        {
        private:
            class MiddleLambda
            {
            private:
                class InnerLambda
                {
                public:
                    inline int operator()(int c) const
                    {
                        return (m_a + m_b) + c;
                    }

                private:
                    int m_a;
                    int m_b;

                public:
                    InnerLambda(int a, int b) : m_a{ a }, m_b{ b } {}
                };

            public:
                inline InnerLambda operator()(int b) const
                {
                    InnerLambda tmp{ m_a, b };
                    return tmp;
                }

            private:
                int m_a;

            public:
                MiddleLambda(int a) : m_a{ a } {}
            };

        public:
            inline MiddleLambda operator()(int a) const
            {
                MiddleLambda tmp{ a };
                return tmp;
            }
        };

        // longer, explanatory syntax
        auto firstLambda{ OuterLambda{} };
        auto secondLambda{ firstLambda(21) };
        auto thirdLambda{ secondLambda(22) };
        auto result1{ thirdLambda(23) };
        std::println("{} ", result1);

        // short syntax
        OuterLambda lambda = OuterLambda{};
        auto result2{ lambda(10)(11)(12) };
        std::println("{} ", result2);
    }

    // =================================================================================
    // 'Filter-Map-Reduce' Pattern

    class Book 
    {
    public:
        std::string m_title;
        std::string m_author;
        std::size_t m_year;
        double      m_price;
    };

    static void test_functional_filter_map_reduce_01() {

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

        // reduce to result string, e.g. comma separated list
        std::string titles{
            std::accumulate(
                std::begin(bookTitles),
                std::end(bookTitles),
                std::string{},
                [](const std::string& a, const std::string& b) {
                    return a.empty() ? b : std::format("{}, {}", a, b);
                }
            ) 
        };

        std::println("Titles: {}", titles);
    }

    static void test_functional_filter_map_reduce_02() {

        std::list<Book> booksList
        {
            { "C", "Dennis Ritchie", 1972, 11.99 } ,
            { "Java", "James Gosling", 1995, 19.99 },
            { "C++", "Bjarne Stroustrup", 1985, 20.00 },
            { "C#", "Anders Hejlsberg", 2000, 29.99 }
        };

        auto results {
            booksList
            | std::ranges::views::filter([](const Book& book) { return book.m_year >= 1990; })
            | std::ranges::views::transform([](const Book& book) { return book.m_title; })
            | std::ranges::views::common 
        };

        // reduce to result string, e.g. comma separated list
        std::string titles{
            std::accumulate(
                std::begin(results),
                std::end(results),
                std::string{},
                [](const std::string& a, const std::string& b) {
                    return a.empty() ? b : std::format("{}, {}", a, b);
                }
            ) 
        };

        std::println("Titles: {}", titles);
    }
}

void main_functional_programming()
{
    using namespace FunctionalProgramming;

    test_functional_pure_01();
    test_functional_pure_02();
    test_functional_pure_03();

    functional_partial_application_01();
    functional_partial_application_02();
    functional_partial_application_03();
    functional_partial_application_04();
    functional_partial_application_05();

    functional_currying_regular();
    functional_currying_01();
    functional_currying_02();
    functional_currying_03();
    functional_currying_04();
    functional_currying_05();
    functional_currying_06();
    functional_currying_07();
    functional_currying_08();

    test_functional_filter_map_reduce_01();
    test_functional_filter_map_reduce_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
