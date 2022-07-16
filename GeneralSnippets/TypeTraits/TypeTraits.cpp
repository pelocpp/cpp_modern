// =====================================================================================
// Typmerkmale // Type Traits
// =====================================================================================

#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>

namespace TypeTraits_Demo_Iterator_01
{
    void whichIterator(const std::input_iterator_tag)
    {
        std::cout << "[Input Iterator]" << std::endl;
    }

    void whichIterator(const std::output_iterator_tag)
    {
        std::cout << "[Output Iterator]" << std::endl;
    }

    void whichIterator(const std::forward_iterator_tag)
    {
        std::cout << "[Forward Iterator]" << std::endl;
    }

    void whichIterator(const std::bidirectional_iterator_tag)
    {
        std::cout << "[Bidirectional Iterator Iterator]" << std::endl;
    }

    void whichIterator(const std::random_access_iterator_tag)
    {
        std::cout << "[Random Access Iterator]" << std::endl;
    }

    template <typename TIterator>
    auto getIteratorType(const TIterator&)
    {
        typename std::iterator_traits<TIterator>::iterator_category tag{};
        return tag;
    }

    void test_1()
    {
        std::vector<int> vec;
        whichIterator(getIteratorType(vec.begin()));

        // oder:
        std::vector<int>::iterator it;
        whichIterator(getIteratorType(it));

        // oder:
        std::vector<int>::iterator::iterator_category iter_cat{};
        whichIterator(iter_cat);
    }

    void test_2()
    {
        std::list<int> list;
        whichIterator(getIteratorType(list.begin()));

        // oder:
        std::list<int>::iterator it;
        whichIterator(getIteratorType(it));

        // oder:
        std::list<int>::iterator::iterator_category iter_cat{};
        whichIterator(iter_cat);
    }

    void test_3()
    {
        std::forward_list<int> fwlist;
        whichIterator(getIteratorType(fwlist.begin()));

        // oder:
        std::forward_list<int>::iterator it;
        whichIterator(getIteratorType(it));

        // oder:
        std::forward_list<int>::iterator::iterator_category iter_cat{};
        whichIterator(iter_cat);
    }

    void test_4()
    {
        std::ifstream source;
        std::istream_iterator<int> input(source);
        whichIterator(getIteratorType(input));

        // oder:
        std::istream_iterator<int> it{};
        whichIterator(getIteratorType(it));

        // oder:
        std::istream_iterator<int>::iterator_category iter_cat{};
        whichIterator(iter_cat);
    }

    void test_5()
    {
        std::ofstream source;
        std::ostream_iterator<int> output(source);
        whichIterator(getIteratorType(output));

        // oder:
        // std::ostream_iterator<int> has no default c'tor

        // oder:
        std::ostream_iterator<int>::iterator_category iter_cat{};
        whichIterator(iter_cat);
    }

    void test_01()
    {
        test_1();
        test_2();
        test_3();
        test_4();
        test_5();
    }
}

namespace TypeTraits_Demo_Iterator_02
{
    template <typename Iterator>
    using ValueType = typename Iterator::value_type;

    template <typename Iterator>
    using Category = typename Iterator::iterator_category;

    template <typename Iterator>
    ValueType<Iterator> getAt(Iterator it, size_t position, std::forward_iterator_tag)
    {
        std::cout << "[Forward Iterator] ";
        Iterator pos = it;
        for (size_t i{}; i != position; ++i)
            ++pos;
        return *pos;
    }

    template <typename Iterator>
    ValueType<Iterator> getAt(Iterator it, size_t position, std::bidirectional_iterator_tag)
    {
        std::cout << "[Bidirectional Access] ";
        Iterator pos = it;
        for (size_t i{}; i != position; ++i)
            ++pos;
        return *pos;
    }

    template <typename Iterator>
    ValueType<Iterator> getAt(Iterator it, size_t position, std::random_access_iterator_tag)
    {
        std::cout << "[Random Access] ";
        Iterator pos = it + position;
        return *pos;
    }

    template <typename Iterator>
    ValueType<Iterator> getAt(Iterator it, size_t size)
    {
        Category<Iterator> category{};
        return getAt(it, size, category);
    }

    void test_02() 
    {
        std::forward_list<char> charList{ 'A', 'B', 'C', 'D', 'E' };
        char ch = getAt(charList.begin(), 3);
        std::cout << "std::forward_list: " << ch << std::endl;

        std::list<int> intList{ 1, 2, 3, 4, 5 };
        int value = getAt(intList.begin(), 3);
        std::cout << "std::list:     " << value << std::endl;

        std::vector<int> doubleVector{ 10, 20, 30, 40, 50 };
        double d = getAt(doubleVector.begin(), 3);
        std::cout << "std::vector:          " << d << std::endl;
    }
}

namespace TypeTraits_Demo_Remove_Reference_03
{
    template<typename Container>
    void sort_01(Container& container)
    {
        std::sort(
            std::begin(container),
            std::end(container),
            [](auto n1, auto n2) -> bool {
                return n1 < n2;
            }
        );
    }

    template<typename Container>
    void sort_02(Container& container)
    {
        std::sort(
            std::begin(container),
            std::end(container),
            [](typename Container::value_type n1, typename Container::value_type n2) {
                return n1 < n2;
            }
        );
    }

    template<typename Container>
    void sort_03(Container& container)
    {
        std::sort(
            std::begin(container),
            std::end(container),
            []( decltype (container[0]) n1, 
                decltype (container[0]) n2) {
                    return n1 < n2;
            }
        );
    }

    template<typename Container>
    void sort_04(Container& container)
    {
        std::sort(
            std::begin(container),
            std::end(container),
            []( std::remove_reference<decltype (container[0])>::type n1,
                std::remove_reference<decltype (container[0])>::type n2) {
                    return n1 < n2;
            }
        );
    }

    void test_03()
    {
        std::vector<int> vec{ 5, 4, 6, 3, 7, 2, 8, 1, 9 };

        sort_01<std::vector<int>>(vec);
        sort_02<std::vector<int>>(vec);
        sort_03<std::vector<int>>(vec);
        sort_04<std::vector<int>>(vec);

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;
    }
}

void main_type_traits()
{
    using namespace TypeTraits_Demo_Iterator_01;
    test_01();

    using namespace TypeTraits_Demo_Iterator_02;
    test_02();

    using namespace TypeTraits_Demo_Remove_Reference_03;
    test_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
