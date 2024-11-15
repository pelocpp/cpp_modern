// =====================================================================================
// FunctionalProgramming02.cpp // Functional Programming - Variante 1
// =====================================================================================

module;

#include <cctype>   // <-- ::toupper

module modern_cpp:functional_programming;

namespace FunctionalProgramming_01 {

    // =================================================================================

    template <typename TReturn, typename InputIterator, typename TFunctor>
    auto fold(InputIterator begin, InputIterator end, TFunctor&& lambda)
        // not needed, just for demonstration purposes
        -> TReturn
    {
        TReturn init{};
        return std::accumulate(begin, end, init, std::forward<TFunctor>(lambda));
    }

    // =================================================================================

    // alias template
    template <typename T>
    using ValueType = typename std::iterator_traits<T>::value_type;

    template <typename InputIterator, typename TFunctor>
    auto filter(InputIterator begin, InputIterator end, TFunctor&& lambda)
        // not needed, just for demonstration purposes
        -> std::vector<ValueType<InputIterator>>
    {
        std::vector<ValueType<InputIterator>> result;
        result.reserve(std::distance(begin, end));
        std::copy_if(begin, end, std::back_inserter(result), std::forward<TFunctor>(lambda));
        return result;
    }

    // without alias template
    template <typename InputIterator, typename TFunctor>
    auto filterEx(InputIterator begin, InputIterator end, TFunctor&& lambda)
        // not needed, just for demonstration purposes
        -> std::vector<typename std::iterator_traits<InputIterator>::value_type>
    {
        using ValueType = typename std::iterator_traits<InputIterator>::value_type;

        std::vector<ValueType> result;
        result.reserve(std::distance(begin, end));
        std::copy_if(begin, end, std::back_inserter(result), std::forward<TFunctor>(lambda));
        return result;
    }

    // =================================================================================

    template <typename InputIterator, typename TFunctor>
    auto map(InputIterator begin, InputIterator end, TFunctor&& lambda)
        // not needed, just for demonstration purposes
        -> std::vector<decltype(std::declval<TFunctor>()(std::declval<typename std::iterator_traits<InputIterator>::value_type>()))>
    {
        using FunctorValueType = decltype(std::declval<TFunctor>()(std::declval<ValueType<InputIterator>>()));

        std::vector<FunctorValueType> result;
        result.reserve(std::distance(begin, end));
        std::transform(begin, end, std::back_inserter(result), std::forward<TFunctor>(lambda));
        return result;
    }

    // without alias template
    template <typename InputIterator, typename TFunctor>
    auto mapEx(InputIterator begin, InputIterator end, TFunctor&& lambda)
        // not needed, just for demonstration purposes
        -> std::vector<decltype(std::declval<TFunctor>()(std::declval<typename std::iterator_traits<InputIterator>::value_type>()))>
    {
        using ValueType = typename std::iterator_traits<InputIterator>::value_type;
        using FunctorValueType = decltype(std::declval<TFunctor>()(std::declval<ValueType>()));

        std::vector<FunctorValueType> result;
        result.reserve(std::distance(begin, end));
        std::transform(begin, end, std::back_inserter(result), std::forward<TFunctor>(lambda));
        return result;
    }

    // =================================================================================
    // testing 'filter'

    // filtering even numbers in a list of numbers
    static void test_functional_filter_01() {

        std::vector<int> vec(20);
        std::generate(std::begin(vec), std::end(vec), [value = 0]() mutable {
            return ++value;
        });

        std::for_each(std::begin(vec), std::end(vec), [](int value) {
            std::cout << value << ' ';
            }
        );
        std::cout << std::endl;

        std::vector<int> result = filter(
            std::begin(vec), 
            std::end(vec),
            [](unsigned i) { return i % 2 == 0; }
        );

        std::for_each(std::begin(result), std::end(result), [](int value) {
            std::cout << value << ' ';
            });
        std::cout << std::endl;
    }

    // =================================================================================
    // testing 'map'

    // mapping both negative and positive values to a new vector
    // with only positive values
    static void test_functional_map_02a()
    {
        std::vector<int> numbers = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };

        for (int i : numbers) {
            std::cout << "  " << i;
        }
        std::cout << std::endl;

        std::vector<int> result = map(
            std::begin(numbers),
            std::end(numbers),
            [](int const i) { return std::abs(i); }
        );

        for (int i : result) {
            std::cout << "  " << i;
        }
    }

    // mapping list of numbers to new list with each number multiplied by 2 
    static void test_functional_map_02b() {
        std::vector<int> vec(20);
        std::generate(std::begin(vec), std::end(vec), [value = 0]() mutable {
            return ++value;
        });

        std::for_each(std::begin(vec), std::end(vec), [](int value) {
            std::cout << value << ' ';
            }
        );
        std::cout << std::endl;

        std::vector<int> result = map(
            std::begin(vec),
            std::end(vec),
            [](int i) { return i * 2; }
        );

        std::for_each(std::begin(result), std::end(result), [](int value) {
            std::cout << value << ' ';
            }
        );
        std::cout << std::endl;
    }

    // mapping list of strings to new list with integers 
    static void test_functional_map_02c() {
        std::vector<std::string> vec = { "1", "2", "3", "4", "5", "6", "7" , "8", "9", "10" };
        std::for_each(std::begin(vec), std::end(vec), [](std::string s) {
            std::cout << s << ' ';
            });
        std::cout << std::endl;

        auto result = map(
            std::begin(vec),
            std::end(vec),
            [](std::string s) { return std::stoi(s); }  // convert strings to int
        );

        std::for_each(std::begin(result), std::end(result), [](int value) {
            std::cout << value << ' ';
            }
        );
        std::cout << std::endl;
    }

    static void test_functional_map_02d() {
        std::vector<float> vec = { 1.F, 2.f, 3.f, 4.f, 5.f };
        std::for_each(std::begin(vec), std::end(vec), [](float value) {
            std::cout << value << ' ';
            });
        std::cout << std::endl;

        auto result = map(
            std::begin(vec),
            std::end(vec),
            [](float f) { return std::to_string(f); }  // convert float to string
        );

        std::for_each(std::begin(result), std::end(result), [](std::string s) {
            std::cout << s << ' ';
            }
        );
        std::cout << std::endl;
    }

    static void test_functional_map_02e() {

        std::vector<std::string> words = {
            std::string("one"),
            std::string("two"),
            std::string("three")
        };

        std::for_each(std::begin(words), std::end(words), [](const std::string& word) {
            std::cout << word << ' ';
            });
        std::cout << std::endl;

        auto result = map(
            std::begin(words),
            std::end(words),
            [](std::string word) {
                // convert std::string to upper case
                std::transform(std::begin(word), std::end(word), std::begin(word), ::toupper);
                return word;
            }
        );

        std::for_each(std::begin(result), std::end(result), [](std::string s) {
            std::cout << s << ' ';
            }
        );
        std::cout << std::endl;
    }

    // =================================================================================
    // testing 'fold'

    // adding the values of a vector of integers
    static void test_functional_fold_03a()
    {
        std::vector<int> numbers = std::vector <int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };

        int sum1 = fold<int>(
            std::begin(numbers),
            std::end(numbers),
            [](const int n, const int m) {return n + m; }
        );

        std::cout << sum1 << std::endl;
    }

    // concatenating a list of strings into a single string
    static void test_functional_fold_03b() {
        std::list<std::string> words = { "Implementing", "fold", "with", "Modern", "C++" };
        std::for_each(std::begin(words), std::end(words), [](std::string s) {
            std::cout << s;
            });
        std::cout << std::endl;

        // testing left fold
        auto result1 = fold<std::string>(
            std::begin(words),
            std::end(words),
            [](std::string a, std::string b) { return a + std::string(":") + b; }
        );

        std::cout << result1 << std::endl;

        // testing right fold - note usage of reverse iterators
        auto result2 = fold<std::string>(
            std::rbegin(words),
            std::rend(words),
            [](std::string a, std::string b) { return a + std::string(":") + b; }
        );

        std::cout << result2 << std::endl;
    }

    // concatenating an array of characters into a string
    static void test_functional_fold_03c()
    {
        char chars[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };

        auto txt1 = fold<std::string>(
            std::begin(chars),
            std::end(chars),
            std::plus<>()); 
        std::cout << txt1 << std::endl; // abcdefghij

        auto txt2 = fold<std::string>(
            std::rbegin(chars),
            std::rend(chars),
            std::plus<>());
        std::cout << txt2 << std::endl; // jihgfedcba
    }

    //// =================================================================================

    static void test_functional_fmr_pattern_04a()
    {
        auto numbers = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };

        std::vector<int> result = map(
            std::begin(numbers),
            std::end(numbers),
            [](int i) { return std::abs(i); }
        );

        for (int i : result) {
            std::cout << "  " << i;
        }
        std::cout << std::endl;

        std::vector<int> result2 = map(
            std::begin(numbers),
            std::end(numbers),
            [](int i) { return i * i; }
        );

        for (int i : result2) {
            std::cout << "  " << i;
        }
        std::cout << std::endl;

        int sum = fold<int>(
            std::begin(result2),
            std::end(result2),
            [](int n, int m) {return n + m; }
        );

        std::cout << sum << std::endl;
    }

    // testing 'Filter-Map-Reduce' Pattern
    class Book {
    public:
        std::string m_title;
        std::string m_author;
        int m_year;
        double m_price;
    };

    static void test_functional_fmr_pattern_04b() {

        std::list<Book> booksList{
            {"C", "Dennis Ritchie", 1972, 11.99 } ,
            {"Java", "James Gosling", 1995, 19.99 },
            {"C++", "Bjarne Stroustrup", 1985, 20.00 },
            {"C#", "Anders Hejlsberg", 2000, 29.99 }
        };

        // a) filter books which appeared past 1990
        // b) extract book title
        // c) reduce to result string, e.g. comma separated list

        auto result1 = filter(
            std::begin(booksList),
            std::end(booksList),
            [](const Book& book) { return book.m_year >= 1990; }
        );

        auto result2 = map(
            std::begin(result1),
            std::end(result1),
            [](const Book& book) { return book.m_title; }  // convert Book to string
        );

        auto result3 = fold<std::string>(
            std::begin(result2),
            std::end(result2),
            [](std::string a, std::string b) {
                std::ostringstream oss;
                if (a.empty()) {
                    oss << b;
                }
                else {
                    oss << a << ", " << b;
                }
                return oss.str();
            }
        );

        std::cout << result3 << std::endl;
    }

    // helper class
    class SearchResult {
    public:
        std::string m_title;
        std::string m_author;
    };

    static void test_functional_fmr_pattern_04c() {

        std::list<Book> booksList{
            {"C", "Dennis Ritchie", 1972, 11.99 } ,
            {"Java", "James Gosling", 1995, 19.99 },
            {"C++", "Bjarne Stroustrup", 1985, 20.00 },
            {"C#", "Anders Hejlsberg", 2000, 29.99 }
        };

        // a) filter books which appeared past 1990
        // b) extract book title and authors name
        // c) reduce to result string, e.g. comma separated list

        auto result1 = filter(
            std::begin(booksList),
            std::end(booksList),
            [](const Book& book) { return book.m_year >= 1990; }
        );

        auto result2 = map(
            std::begin(result1),
            std::end(result1),
            [](const Book& book) { return SearchResult{ book.m_title, book.m_author }; }
        );

        auto result3 = fold<std::string>(
            std::begin(result2),
            std::end(result2),
            [](std::string a, SearchResult b) -> std::string {
                std::ostringstream oss;
                if (a.empty()) {
                    oss << b.m_title << " [" << b.m_author << ']';
                }
                else {
                    oss << a << " | " << b.m_title << " [" << b.m_author << ']';
                }
                return oss.str();
            }
        );

        std::cout << result3 << std::endl;
    }

    // same query, using 'std::pair' utility class
    static void test_functional_fmr_pattern_04d() {

        std::list<Book> booksList{
            {"C", "Dennis Ritchie", 1972, 11.99 } ,
            {"Java", "James Gosling", 1995, 19.99 },
            {"C++", "Bjarne Stroustrup", 1985, 20.00 },
            {"C#", "Anders Hejlsberg", 2000, 29.99 }
        };

        // a) filter books which appeared past 1990
        // b) extract book title and authors name
        // c) reduce to result string, e.g. comma separated list

        auto result1 = filter(
            std::begin(booksList),
            std::end(booksList),
            [](const Book& book) { return book.m_year >= 1990; }
        );

        auto result2 = map(
            std::begin(result1),
            std::end(result1),
            [](const Book& book) { return std::make_pair(book.m_title, book.m_author); }
        );

        auto result3 = fold<std::string>(
            std::begin(result2),
            std::end(result2),
            [](std::string a, std::pair<std::string, std::string> b) -> std::string {
                std::ostringstream oss;
                if (a.empty()) {
                    oss << b.first << " [" << b.second << ']';
                }
                else {
                    oss << a << " | " << b.first << " [" << b.second << ']';
                }
                return oss.str();
            }
        );

        std::cout << result3 << std::endl;
    }
}

void main_functional_programming()
{
    using namespace FunctionalProgramming_01;

    // testing 'filter'
    test_functional_filter_01();

    // testing 'map'
    test_functional_map_02a();
    test_functional_map_02b();
    test_functional_map_02c();
    test_functional_map_02d();
    test_functional_map_02e();

    // testing 'fold'
    test_functional_fold_03a();
    test_functional_fold_03b();
    test_functional_fold_03c();

    // testing 'fold-map-reduce' pattern
    test_functional_fmr_pattern_04a();
    test_functional_fmr_pattern_04b();
    test_functional_fmr_pattern_04c();
    test_functional_fmr_pattern_04d();
}

// =====================================================================================
// End-of-File
// =====================================================================================
