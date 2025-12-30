// =====================================================================================
// EraseRemoveIdiom.cpp // Erase-Remove Idiom
// =====================================================================================

module;

#include "../ScopedTimer/ScopedTimer.h"

module modern_cpp:erase_remove_idiom;

namespace EraseRemoveIdiom
{
    template <typename T>
    static void print(const std::vector<T>& v)
    {
        std::println("Size: {}, Capacity: {}", v.size(), v.capacity());

        for (auto elem : v) {
            std::print("{} ", elem);
        }
        std::println();
        std::println();
    }

    static void test_removing_elements_01()
    {
        // removing an element at a given position

        std::vector<int> vec{ 1, 2, 3, 4, 5 };

        print(vec);

        std::vector<int>::iterator pos = vec.begin() + 2;

        vec.erase(pos);

        print(vec);
    }

    static void test_removing_elements_02()
    {
        // removing the elements of a given subrange

        std::vector<int> vec{ 1, 2, 3, 4, 5 };

        std::vector<int>::iterator first = vec.begin() + 1;
        std::vector<int>::iterator last = vec.end() - 1;

        print(vec);

        vec.erase(first, last);

        print(vec);
    }


    static void test_removing_elements_10()
    {
        // removing the first element equal to a certain value / C++ 20 (!)

        std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8 };

        print(vec);

        int value{ 5 };

        std::vector<int>::iterator it = std::find(
            vec.begin(),
            vec.end(),
            value
        );

        // check that this value is actually in our vector
        if (it != vec.end()) {
            vec.erase(it);
        }

        print(vec);
    }


    static void test_removing_elements_11()
    {
        // removing all elements equal to a certain value - C++ 20 (!)

        std::vector<int> vec{ 1, 2, 123, 4, 5, 123, 7, 123, 9 };

        print(vec);

        int value{ 123 };

        std::erase(vec, value);

        print(vec);
    }

    // ===========================================================================

    static void test_removing_elements_20()
    {
        // removing all elements equal to a certain value

        std::vector<int> vec{ 1, 2, 123, 4, 5, 123, 7, 123, 9 };

        print(vec);

        int value{ 123 };

#pragma warning(push)
#pragma warning(disable : 4858)

        // the next statement doesn't make any sense without storing the return value,
        // this function has only demonstration purposes

        std::remove(vec.begin(), vec.end(), value);

#pragma warning(pop)

        print(vec);
    }

    static void test_removing_elements_21()
    {
        // removing and erasing all elements equal to a certain value
        // (Remove-Erase Idiom)

        std::vector<int> vec{ 1, 2, 123, 4, 5, 123, 7, 123, 9 };

        print(vec);

        int value{ 123 };

        std::vector<int>::iterator last = std::remove(vec.begin(), vec.end(), value);

        vec.erase(last, vec.end());

        print(vec);
    }

    static void test_removing_elements_22()
    {
        // removing and erasing all elements equal to a certain value
        // (Remove-Erase Idiom - more compact notation)

        std::vector<int> vec{ 1, 2, 123, 4, 5, 123, 7, 123, 9 };

        print(vec);

        int value{ 123 };

        vec.erase(std::remove(vec.begin(), vec.end(), value), vec.end());

        print(vec);
    }

    // ===========================================================================

    static void test_removing_elements_30()
    {
        // invalid iterator object
        std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::vector<int>::iterator it = vec.begin() + 3;

        std::println("3. Element: {}", *it);

        vec.erase(it);

        std::println("3. Element: {}", *it);  // ???
    }


    static void test_removing_elements_31()
    {
        // valid iterator objects
        std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::vector<int>::iterator it = vec.begin() + 3;

        std::println("3. Element: {}", *it);

        it = vec.erase(it);

        std::println("3. Element: {}", *it);
    }

    // ===========================================================================

    static void test_removing_elements_40()
    {
        // "Swap and Pop" idiom
        std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        print(vec);

        std::vector<int>::iterator it = vec.begin() + 3;

        std::swap(*it, vec.back());
        vec.pop_back();

        print(vec);
    }

    // ===========================================================================

    static void test_removing_elements_50()
    {
        // 'std::remove_copy' algorithm
        std::vector<int> src{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::vector<int> dst{};

        print(src);

        std::remove_copy(src.begin(), src.end(), std::back_inserter(dst), 5);
        print(dst);
    }

    static void test_removing_elements_51()
    {
        // 'std::remove_copy_if' algorithm
        std::vector<int> src{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::vector<int> dst{};

        print(src);

        std::remove_copy_if(
            src.begin(),
            src.end(),
            std::back_inserter(dst),
            [](auto elem) { return elem % 2 == 0; }
        );

        print(dst);
    }

    // ===========================================================================
    // ===========================================================================







    static void test_removing_elements_100()
    {
        // "wrong" implementation
        std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        print(vec);

        // erase all even numbers
        for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
        {
            if (*it % 2 == 0) {
                vec.erase(it);
            }
        }

        print(vec);
    }

    static void test_removing_elements_101()
    {
        // Inefficient implementation
        std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        print(vec);

        // erase all even numbers
        for (std::vector<int>::iterator it = vec.begin(); it != vec.end();)
        {
            if (*it % 2 == 0)
                it = vec.erase(it);
            else
                ++it;
        }

        print(vec);
    }

    static void test_removing_elements_102()
    {
        // Better (good) implementation
        std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        print(vec);

        std::vector<int>::iterator pos = std::remove_if(
            vec.begin(),
            vec.end(),
            [](auto elem) { return elem % 2 == 0; }
        );

        vec.erase(pos, vec.end());

        print(vec);
    }

    // 2 benchmarks

    //constexpr std::size_t Max = 1000;
    //constexpr std::size_t NumIterations = 100;

    constexpr std::size_t Max = 5000;
    constexpr std::size_t NumIterations = 1000;

    static void test_removing_elements_103()
    {
        ScopedTimer watch{};

        for (std::size_t i{}; i != NumIterations; ++i) {

            // inefficient implementation
            std::vector<int> vec(Max);

            std::iota(vec.begin(), vec.end(), 1);

            print(vec);

            // erase all even numbers
            for (std::vector<int>::iterator it = vec.begin(); it != vec.end();)
            {
                if (*it % 2 == 0)
                    it = vec.erase(it);
                else
                    ++it;
            }

            print(vec);
        }
    }

    static void test_removing_elements_104()
    {
        ScopedTimer watch{};

        for (std::size_t i{}; i != NumIterations; ++i) {

            // Better (good) implementation
            std::vector<int> vec(Max);

            std::iota(vec.begin(), vec.end(), 1);

            //  print(vec);

            std::vector<int>::iterator pos = std::remove_if(
                vec.begin(),
                vec.end(),
                [](auto elem) { return elem % 2 == 0; }
            );

            vec.erase(pos, vec.end());

            //  print(vec);
        }
    }
}

void main_erase_remove_idiom()
{
    using namespace EraseRemoveIdiom;

    test_removing_elements_01();
    test_removing_elements_02();

    test_removing_elements_10();
    test_removing_elements_11();

    test_removing_elements_20();
    test_removing_elements_21();
    test_removing_elements_22();

    // test_removing_elements_30();    // crashes - by design
    test_removing_elements_31();

    test_removing_elements_40();

    test_removing_elements_50();
    test_removing_elements_51();

    //test_removing_elements_100();
    //test_removing_elements_101();
    //test_removing_elements_102();
    //test_removing_elements_103();
    //test_removing_elements_104();
}

// =====================================================================================
// End-of-File
// =====================================================================================


//
//#include <cstddef>       // std::size_t
//#include <numeric>       // std::iota
//#include <print>         // std::println
//#include <vector>        // std::vector
//#include <algorithm>     // std::find
//
//// removing elements
//
//// https://gist.github.com/martinlicht/3a40e27cf0a0e5051b18effcde1191b1
//
//// https://www.fluentcpp.com/2018/09/14/how-to-remove-elements-from-a-sequence-container/
//
//// https://www.studyplan.dev/pro-cpp/removal-algorithms
//
//
//// https://medium.com/@ryan_forrester_/c-vector-erase-how-to-guide-ad941ccfa07f
//// WEITER : LESEN
//
//// WEITER: TEXT verfassen
//
//// AUFGABE: Aufgabe
//



//namespace EraseRemoveIdiom
//{
//    static auto print = [](const std::vector<int>& v) {
//        std::cout << "Length:   " << v.size() << std::endl;
//        std::cout << "Capacity: " << v.capacity() << std::endl;
//        std::for_each(
//            v.begin(),
//            v.end(),
//            [](const auto& e) {
//                std::cout << e << ' ';
//            }
//        );
//        std::cout << std::endl << std::endl;
//        };
//
//    static void test_01()
//    {
//        std::vector<int> vec = { 0, 1, 2, 5, 4, 5, 6, 5, 8, 9 };
//        print(vec);
//
//        // remove all '5' elements
//        auto it = std::remove(vec.begin(), vec.end(), 5);
//        std::cout << "Position of iterator: " << std::distance(vec.begin(), it) << std::endl;
//        print(vec);
//
//        // erase the unspecified values and reduce the physical size
//        // of the container to match its new logical size
//        vec.erase(it, vec.end());
//        print(vec);
//    }
//
//    static void test_02()
//    {
//        std::vector<int> vec = { 0, 1, 2, 5, 4, 5, 6, 5, 8, 9 };
//        print(vec);
//
//        // remove all elements with the value 5
//        vec.erase(std::remove(vec.begin(), vec.end(), 5), vec.end());
//        print(vec);
//
//        // request the container to reduce its capacity to fit its size
//        vec.shrink_to_fit();
//        print(vec);
//    }
//}
//
