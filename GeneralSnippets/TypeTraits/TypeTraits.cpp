// =====================================================================================
// Typmerkmale // Type Traits
// =====================================================================================

#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <algorithm>

namespace TypeTraits_Demo_Iterator
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

    void test_01() 
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

namespace TypeTraits_Demo_Remove_Reference
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

    void test_02()
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
    using namespace TypeTraits_Demo_Iterator;
    test_01();

    using namespace TypeTraits_Demo_Remove_Reference;
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
