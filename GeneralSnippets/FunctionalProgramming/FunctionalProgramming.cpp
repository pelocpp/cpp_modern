// =====================================================================================
// Functional Programming
// =====================================================================================

#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <type_traits>
#include <vector>
#include <list>
#include <sstream>

// std::forward<TFunctor>(lambda)

namespace FunctionalProgramming {

    template <typename TReturn, typename InputIterator, typename TFunctor>
    auto fold(InputIterator begin, InputIterator end, TFunctor lambda)
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
    auto filter(InputIterator begin, InputIterator end, TFunctor lambda)
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
    auto filterEx(InputIterator begin, InputIterator end, TFunctor lambda)
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
    auto map(InputIterator begin, InputIterator end, TFunctor lambda)
        // not needed, just for demonstration purposes
        -> std::vector<decltype(std::declval<TFunctor>()(std::declval<typename std::iterator_traits<InputIterator>::value_type>()))>
    {
        using FunctorValueType = decltype(std::declval<TFunctor>()(std::declval<ValueType<InputIterator>>()));

        std::vector<FunctorValueType> result;
        result.reserve(unsigned(std::distance(begin, end)));
        std::transform(begin, end, std::back_inserter(result), std::forward<TFunctor>(lambda));
        return result;
    }

    // without alias template
    template <typename InputIterator, typename TFunctor>
    auto mapEx(InputIterator begin, InputIterator end, TFunctor lambda)
        // not needed, just for demonstration purposes
        -> std::vector<decltype(std::declval<TFunctor>()(std::declval<typename std::iterator_traits<InputIterator>::value_type>()))>
    {
        using ValueType = typename std::iterator_traits<InputIterator>::value_type;
        using FunctorValueType = decltype(std::declval<TFunctor>()(std::declval<ValueType>()));

        std::vector<FunctorValueType> result;
        result.reserve(unsigned(std::distance(begin, end)));
        std::transform(begin, end, std::back_inserter(result), std::forward<TFunctor>(lambda));
        return result;
    }

    // =================================================================================

    // test 'filter'
    void test_functional_01() {
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

    // test 'map'
    void test_functional_02a() {
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

    // test 'map'
    void test_functional_02b() {
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

    // test 'map'
    void test_functional_02c() {
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

    // test 'fold'
    void test_functional_03a() {
        std::list<std::string> list = { "Implementing", "fold", "with", "Modern", "C++" };
        std::for_each(std::begin(list), std::end(list), [](std::string s) {
            std::cout << s << ' ';
            });
        std::cout << std::endl;

        auto result = fold<std::string>(
            std::begin(list),
            std::end(list),
            [](std::string a, std::string b) { return a + std::string(":") + b; }
        );

        std::cout << result << std::endl;
    }

    // testing 'Filter-Map-Reduce' Pattern
    class Book {
    public:
        std::string m_title;
        std::string m_author;
        int m_year;
        double m_price;
    };

    void test_functional_04a() {
        std::list<Book> booksList{
            {"C", "Dennis Ritchie", 1972, 11.99 } ,
            {"Java", "James Gosling", 1995, 19.99 },
            {"C++", "Bjarne Stroustrup", 1985, 20.00 },
            {"C#", "Anders Hejlsberg", 2000, 29.99 }
        };

        // a) filter books which appeared past 1990
        // b) extract book title
        // c) reduce to result string, e.g. comma seperated list

        auto result1 = filter(
            std::begin(booksList),
            std::end(booksList),
            [](const Book& book) { return book.m_year >= 1990; }
        );

        auto result2 = map(
            std::begin(result1),
            std::end(result1),
            [](const Book& book) { return book.m_title; }  // convert float to string
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

    void test_functional_04b() {
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
    void test_functional_04c() {
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
    using namespace FunctionalProgramming;

    // test 'filter'
    test_functional_01();

    // test 'map'
    test_functional_02a();
    test_functional_02b();
    test_functional_02c();

    // test 'fold'
    test_functional_03a();

    test_functional_04a();
    test_functional_04b();
    test_functional_04c();
}

// =====================================================================================
// End-of-File
// =====================================================================================