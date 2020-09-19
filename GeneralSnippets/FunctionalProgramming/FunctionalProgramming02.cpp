// =====================================================================================
// Functional Programming- Variante 2
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

namespace FunctionalProgramming_02 {

    // =================================================================================

    // note: container is passed by value so that modifying the local copy
    // does not affect the original container
    template <typename TContainer, typename TResult, typename TFunctor>
    TResult foldLeft(TContainer cont, TResult&& init, TFunctor&& lambda)
    {
        return std::accumulate(
            std::begin(cont),
            std::end(cont),
            std::move(init),
            std::forward<TFunctor>(lambda));
    }

    template <typename TContainer, typename TResult, typename TFunctor>
    TResult foldRight(TContainer cont, TResult init, TFunctor&& lambda)
    {
        return std::accumulate(
            std::rbegin(cont),
            std::rend(cont),
            std::move(init),
            std::forward<TFunctor>(lambda));
    }

    // =================================================================================

    template <typename TContainer, typename TFunctor>
    auto filter(TContainer&& cont, TFunctor&& lambda)

        // not needed, just for demonstration purposes
        ->std::vector<typename std::remove_reference<decltype (cont[0])>::type >
    {
        using ValueType1 = decltype (cont[0]);  // retrieve type of single container element
        using ValueType2 = typename std::remove_reference<ValueType1>::type;  

        std::vector<ValueType2 > result;
        result.reserve(std::distance(std::begin(cont), std::end(cont)));
        std::copy_if(
            std::begin(cont),
            std::end(cont), 
            std::back_inserter(result),
            std::forward<TFunctor>(lambda)
        );
        return result;
    }

    // =================================================================================

    template <typename TFunctor, typename TContainer>
    auto map(TContainer cont, TFunctor&& lambda)
        // not needed, just for demonstration purposes
       -> std::vector<decltype(std::declval<TFunctor>()(std::declval<typename TContainer::value_type>()))>
    {
        std::vector<decltype(std::declval<TFunctor>()(std::declval<typename TContainer::value_type>()))> result;

        std::transform(
            std::begin(cont),
            std::end(cont),
            std::back_inserter(result),
            std::forward<TFunctor>(lambda));

        return result;
    }

    // =================================================================================
    // testing 'filter'

    void test_functional_filter_01() {
        std::vector<int> vec(20);
        std::generate(std::begin(vec), std::end(vec), [value = 0]() mutable {
            return ++value;
        });

        std::for_each(std::begin(vec), std::end(vec), [](int value) {
            std::cout << value << ' ';
            }
        );
        std::cout << std::endl;

        auto result = filter(
            vec,
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
    void test_functional_map_02a()
    {
        std::vector<int> numbers = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };

        for (int i : numbers) {
            std::cout << "  " << i;
        }
        std::cout << std::endl;

        std::vector<int> result = map(
            numbers,
            [](int const i) { return std::abs(i); }
        );

        for (int i : result) {
            std::cout << "  " << i;
        }
    }

    void test_functional_map_02b() {
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
            vec,
            [](int i) { return i * 2; }
        );

        std::for_each(std::begin(result), std::end(result), [](int value) {
            std::cout << value << ' ';
            }
        );
        std::cout << std::endl;
    }

    void test_functional_map_02c() {
        std::vector<std::string> vec = { "1", "2", "3", "4", "5", "6", "7" , "8", "9", "10" };
        std::for_each(std::begin(vec), std::end(vec), [](std::string s) {
            std::cout << s << ' ';
            });
        std::cout << std::endl;

        auto result = map(
            vec,
            [](std::string s) { return std::stoi(s); }  // convert strings to int
        );

        std::for_each(std::begin(result), std::end(result), [](int value) {
            std::cout << value << ' ';
            }
        );
        std::cout << std::endl;
    }

    void test_functional_map_02d() {
        std::vector<float> vec = { 1.F, 2.f, 3.f, 4.f, 5.f };
        std::for_each(std::begin(vec), std::end(vec), [](float value) {
            std::cout << value << ' ';
            });
        std::cout << std::endl;

        auto result = map(
            vec,
            [](float f) { return std::to_string(f); }  // convert float to string
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
    void test_functional_fold_03a()
    {
        std::vector<int> numbers = std::vector <int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };

        int sum = foldLeft(
            numbers,
            0,
            [](const int n, const int m) {return n + m; }
        );

        std::cout << sum << std::endl;
    }

    // concatenating a list of strings into a single string
    void test_functional_fold_03b() {
        std::list<std::string> list = { "Implementing", "fold", "with", "Modern", "C++" };
        std::for_each(std::begin(list), std::end(list), [](std::string s) {
            std::cout << s << ' ';
            });
        std::cout << std::endl;

        auto result1 = foldLeft(
            list,
            std::string(""),
            [](std::string a, std::string b) { return a + std::string(":") + b; }
        );

        std::cout << result1 << std::endl;

        auto result2 = foldRight(
            list,
            std::string(""),
            [](std::string a, std::string b) { return a + std::string(":") + b; }
        );

        std::cout << result2 << std::endl;
    }

    // concatenating an array of characters into a string
    void test_functional_fold_03c()
    {
        char chars[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 0 };

        auto txt1 = foldLeft<std::string>(
            chars,
            std::string(""),
            std::plus<>());
        std::cout << txt1 << std::endl; // abcdefghij

        auto txt2 = foldRight<std::string>(
            chars,
            std::string(""),
            std::plus<>());
        std::cout << txt2 << std::endl; // jihgfedcba
    }

    // =================================================================================
    // testing 'Filter-Map-Reduce' Pattern

    class Book {
    public:
        std::string m_title;
        std::string m_author;
        int m_year;
        double m_price;
    };

    void test_functional_04a() {
        std::vector<Book> booksList{
            {"C", "Dennis Ritchie", 1972, 11.99 } ,
            {"Java", "James Gosling", 1995, 19.99 },
            {"C++", "Bjarne Stroustrup", 1985, 20.00 },
            {"C#", "Anders Hejlsberg", 2000, 29.99 }
        };

        // a) filter books which appeared past 1990
        // b) extract book title
        // c) reduce to result string, e.g. comma seperated list

        std::vector<Book> result1 = filter(
            booksList,
            [](const Book& book) { return book.m_year >= 1990; }
        );

        std::vector<std::string> result2 = map(
            result1,
            [](const Book& book) { return book.m_title; }  // convert float to string
        );

        std::string result3 = foldLeft(
            result2,
            std::string(""),
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

    void test_functional_04a_compact() {
        std::vector<Book> booksList{
            {"C", "Dennis Ritchie", 1972, 11.99 } ,
            {"Java", "James Gosling", 1995, 19.99 },
            {"C++", "Bjarne Stroustrup", 1985, 20.00 },
            {"C#", "Anders Hejlsberg", 2000, 29.99 }
        };

        // a) filter books which appeared past 1990
        // b) extract book title
        // c) reduce to result string, e.g. comma seperated list

        std::string result = foldLeft(
            map(
                filter(
                    booksList,
                    [] (const Book& book) { return book.m_year >= 1990; }
                ),
                [] (const Book& book) { return book.m_title; }  // convert float to string
            ),
            std::string(""),
            [] (std::string a, std::string b) {
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

        std::cout << result << std::endl;
    }
//
//    // helper class
//    class SearchResult {
//    public:
//        std::string m_title;
//        std::string m_author;
//    };
//
//    void test_functional_04b() {
//        std::list<Book> booksList{
//            {"C", "Dennis Ritchie", 1972, 11.99 } ,
//            {"Java", "James Gosling", 1995, 19.99 },
//            {"C++", "Bjarne Stroustrup", 1985, 20.00 },
//            {"C#", "Anders Hejlsberg", 2000, 29.99 }
//        };
//
//        // a) filter books which appeared past 1990
//        // b) extract book title and authors name
//        // c) reduce to result string, e.g. comma separated list
//
//        auto result1 = filter(
//            std::begin(booksList),
//            std::end(booksList),
//            [](const Book& book) { return book.m_year >= 1990; }
//        );
//
//        auto result2 = map(
//            std::begin(result1),
//            std::end(result1),
//            [](const Book& book) { return SearchResult{ book.m_title, book.m_author }; }
//        );
//
//        auto result3 = fold<std::string>(
//            std::begin(result2),
//            std::end(result2),
//            [](std::string a, SearchResult b) -> std::string {
//                std::ostringstream oss;
//                if (a.empty()) {
//                    oss << b.m_title << " [" << b.m_author << ']';
//                }
//                else {
//                    oss << a << " | " << b.m_title << " [" << b.m_author << ']';
//                }
//                return oss.str();
//            }
//        );
//
//        std::cout << result3 << std::endl;
//    }
//
//    // same query, using 'std::pair' utility class
//    void test_functional_04c() {
//        std::list<Book> booksList{
//            {"C", "Dennis Ritchie", 1972, 11.99 } ,
//            {"Java", "James Gosling", 1995, 19.99 },
//            {"C++", "Bjarne Stroustrup", 1985, 20.00 },
//            {"C#", "Anders Hejlsberg", 2000, 29.99 }
//        };
//
//        // a) filter books which appeared past 1990
//        // b) extract book title and authors name
//        // c) reduce to result string, e.g. comma separated list
//
//        auto result1 = filter(
//            std::begin(booksList),
//            std::end(booksList),
//            [](const Book& book) { return book.m_year >= 1990; }
//        );
//
//        auto result2 = map(
//            std::begin(result1),
//            std::end(result1),
//            [](const Book& book) { return std::make_pair(book.m_title, book.m_author); }
//        );
//
//        auto result3 = fold<std::string>(
//            std::begin(result2),
//            std::end(result2),
//            [](std::string a, std::pair<std::string, std::string> b) -> std::string {
//                std::ostringstream oss;
//                if (a.empty()) {
//                    oss << b.first << " [" << b.second << ']';
//                }
//                else {
//                    oss << a << " | " << b.first << " [" << b.second << ']';
//                }
//                return oss.str();
//            }
//        );
//
//        std::cout << result3 << std::endl;
//    }



}

void main_functional_programming_alternate()
{
    using namespace FunctionalProgramming_02;

    // test 'filter'
    test_functional_filter_01();

    // test 'map'
    //test_functional_map_02a();
    //test_functional_map_02b();
    //test_functional_map_02c();
    //test_functional_map_02d();

    //// test 'fold'
    //test_functional_fold_03a();
    //test_functional_fold_03b();
    test_functional_fold_03c();

    test_functional_04a();
    test_functional_04a_compact();
    //test_functional_04b();
    //test_functional_04c();
}

// =====================================================================================
// End-of-File
// =====================================================================================
