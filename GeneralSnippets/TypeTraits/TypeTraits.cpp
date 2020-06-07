// =====================================================================================
// Typmerkmale // Type Traits
// =====================================================================================

#include <iostream>
#include <vector>
#include <list>
#include <iterator>

namespace MyTypeTraitsDemo {

    template <typename Iterator>
    using ValueType = typename Iterator::value_type;

    template <typename Iterator>
    typename ValueType<Iterator> getMidst(Iterator it, size_t size, std::bidirectional_iterator_tag)
    {
        std::cout << "[Bidirectional Access] ";
        Iterator pos = it;
        for (unsigned i = 0u; i < size / 2; ++i)
            ++pos;
        return *pos;
    }

    template <typename Iterator>
    typename ValueType<Iterator> getMidst(Iterator it, size_t size, std::random_access_iterator_tag)
    {
        std::cout << "[Random Access] ";
        Iterator pos = it + size / 2;
        return *pos;
    }

    template <typename Iterator>
    typename ValueType<Iterator> getMidst(Iterator it, size_t size)
    {
        typename std::iterator_traits<Iterator>::iterator_category category;
        return getMidst(it, size, category);
    }
}

void main_type_traits()
{
    using namespace MyTypeTraitsDemo;

    std::list<int> anyList{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int value = getMidst(anyList.begin(), anyList.size());
    std::cout << "Midst of List: " << value << std::endl;

    std::vector<int> anyVector{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    value = getMidst(anyVector.begin(), anyVector.size());
    std::cout << "Midst of Vector: " << value << std::endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================
