// =====================================================================================
// StandardLibrarySTL.cpp - STL Bibliothek
// =====================================================================================

#include <iostream>
#include <vector>
#include <string>
#include <numeric>

namespace StandardLibrarySTL {

    //===================================================
    // const-Iteratoren std::cbegin und std::cend

    void test_01()
    {
        std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        for (auto it = std::cbegin(vec); it != std::cend(vec); ++it) {
            std::cout << *it << ' ';
            // *it *= 2;   // 'it': you cannot assign to a variable that is const
        }
        std::cout << std::endl;

        for (auto& elem : vec) {
            elem *= 2;
        }

        for (auto it = std::cbegin(vec); it != std::cend(vec); ++it) {
            std::cout << *it << ' ';
        }
        std::cout << std::endl;

        for (const auto& elem : vec) {
            std::cout << elem << ' ';
        }
    }

    //===================================================
    // Function std::make_move_iterator

    void test_02()
    {
        std::vector<std::string> source{ "C++", "Iterator", "Library", "make_move_iterator" };
        std::vector<std::string> target{ 4 };

        std::copy(
            std::make_move_iterator(source.begin()),
            std::make_move_iterator(source.end()),
            target.begin()
        );

        // target now contains unspecified values, clear them
        source.clear();

        std::cout << "Target:" << std::endl;

        for (const std::string& s : target)
            std::cout << s << ' ';

        std::cout << std::endl;
    }

    //===================================================
    // Function shrink_to_fit

    void test_03() {
        std::vector<int> vec;
        vec.reserve(100);

        for (int i = 0; i < 50; i++) {
            vec.push_back(i);
        }

        std::cout << "Size:     " << vec.size() << std::endl;
        std::cout << "Capacity: " << vec.capacity() << std::endl;

        vec.shrink_to_fit();

        std::cout << "Size:     " << vec.size() << std::endl;
        std::cout << "Capacity: " << vec.capacity() << std::endl;
    }
}

void main_standard_library_STL()
{
    using namespace StandardLibrarySTL;

    test_01();
    test_02();
    test_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
