// =====================================================================================
// Typmerkmale // Type Traits
// =====================================================================================

#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
// #include <iterator>

namespace MyTypeTraitsDemo {

    template <typename Iter>
    using ValueType = typename Iter::value_type;

    template <typename Iter>
    ValueType<Iter> getMidst(Iter it, size_t size, std::forward_iterator_tag)
    {
        std::cout << "[Forward Iterator] ";
        Iter pos = it;
        for (unsigned i = 0u; i < size / 2; ++i)
            ++pos;
        return *pos;
    }

    template <typename Iter>
    ValueType<Iter> getMidst(Iter it, size_t size, std::bidirectional_iterator_tag)
    {
        std::cout << "[Bidirectional Access] ";
        Iter pos = it;
        for (unsigned i = 0u; i < size / 2; ++i)
            ++pos;
        return *pos;
    }

    template <typename Iter>
    ValueType<Iter> getMidst(Iter it, size_t size, std::random_access_iterator_tag)
    {
        std::cout << "[Random Access] ";
        Iter pos = it + size / 2;
        return *pos;
    }

    template <typename Iter>
    ValueType<Iter> getMidst(Iter it, size_t size)
    {
        typename std::iterator_traits<Iter>::iterator_category category{};
        return getMidst(it, size, category);
    }
}

void main_type_traits()
{
    using namespace MyTypeTraitsDemo;

    std::forward_list<char> charList{ 'A', 'B', 'C', 'D', 'E' };
    char ch = getMidst(charList.begin(), 2);
    std::cout << "Midst of List: " << ch << std::endl;

    std::list<int> intList{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int value = getMidst(intList.begin(), intList.size());
    std::cout << "Midst of List: " << value << std::endl;

    std::vector<int> doubleVector{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    double d = getMidst(doubleVector.begin(), doubleVector.size());
    std::cout << "Midst of Vector: " << d << std::endl;
}

// =====================================================================================
// End-of-File
// =====================================================================================
