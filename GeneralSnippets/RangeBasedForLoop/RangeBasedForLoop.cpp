// =====================================================================================
// RangeBasedForLoop.cpp
// =====================================================================================

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>

/*
*  12 ways to iterate through a vector 
*/

namespace RangeBasedForLoop {

    // global function
    template <typename T>
    void processElement(const T& n)
    {
        std::cout << n << " ";
    }

    // functor: "callabe object" - class which implements operator()
    template <typename T>
    class ElementProcessor
    {
    public:
        void operator() (const T& n) { std::cout << n << " "; }
    };

    void test_01()
    {
        // container of integral data type
        std::vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.push_back(4);
        vec.push_back(7);
        vec.push_back(0);
        vec.push_back(9);

        // =========================================================================
        // "Classic style" examples

        // a) Very, very old style ... I wouldn't do this ... C-stylistic
        for (size_t i = 0; i != vec.size(); ++i) {
            std::cout << vec[i] << " ";
        }
        std::cout << std::endl;

        // b) Looks like C++, very classic style
        std::for_each(
            std::begin(vec),           // Iterator-object for begin of range
            std::end(vec),             // Iterator-object for end of range
            processElement<int>        // function pointer
        );
        std::cout << std::endl;

        // c) Same as b), modified ranges
        std::for_each(
            std::next(std::begin(vec)),    // Iterator-object for begin of range
            std::prev(std::end(vec)),      // Iterator-object for end of range
            processElement<int>            // function pointer
        );
        std::cout << std::endl;

        // d) Looks like C++, classic style, 'functor'-stylistic
        std::for_each(
            std::begin(vec),               // Iterator-object for begin of range
            std::end(vec),                 // Iterator-object for end of range
            ElementProcessor<int>{}        // "callable" object
        );
        std::cout << std::endl;

        // e) Using STL algorithm std::for_each with a lambda: Looks like C++, modern style
        std::for_each(
            std::begin(vec),               // Iterator-object for begin of range
            std::end(vec),                 // Iterator-object for end of range
            [](int n) {                    // anonymous method (lambda)
                std::cout << n << " ";
            }
        );
        std::cout << std::endl;

        // =========================================================================
        // Range-based 'for' Loop examples

        // f) Using Range-based 'for' Loop: Looks like C++, very modern style
        for (int n : vec) {
            std::cout << n << " ";
            if (n == 2)  // break is possible
                break;
        }
        std::cout << std::endl;

        // g) Same as f), using 'const&'
        for (const int& n : vec) {
            std::cout << n << " ";
        }
        std::cout << std::endl;

        // h) Same as f): Using 'auto' keyword to cause type inference to be used
        for (auto n : vec) {
            std::cout << n << " ";
        }
        std::cout << std::endl;

        // i) Same as g), using 'const&': Type inference by reference
        for (const auto& n : vec) {
            std::cout << n << " ";
        }
        std::cout << std::endl;

        // j) Real C++: How the compiler 'sees' a Range-based 'for' Loop - you never ever do this
        std::vector<int>::iterator begin = std::begin(vec);
        std::vector<int>::iterator end = std::end(vec);

        while (begin != end) {

            int n = *begin;
            std::cout << n << " ";
            ++begin;
        }
        std::cout << std::endl;

        // k) Same as h), using 'auto'
        auto begin2 = std::begin(vec);
        auto end2 = std::end(vec);

        while (begin2 != end2) {

            int n = *begin2;
            std::cout << n << " ";
            ++begin2;
        }
        std::cout << std::endl;

        // l) Range-based 'for' loop with initializer,
        // we can now use the index variable inside the for statement
        for (int index{}; int n : vec) {
            std::cout << index << ": " << n << " " << std::endl;
            ++index;
        }
    }
}

void main_range_based_for_loop()
{
    using namespace RangeBasedForLoop;
    test_01(); 
}

// =====================================================================================
// End-of-File
// =====================================================================================
