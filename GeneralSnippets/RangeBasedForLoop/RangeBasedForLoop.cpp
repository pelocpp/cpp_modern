// =====================================================================================
// RangeBasedForLoop.cpp
// =====================================================================================

module modern_cpp:range_based_for_loop;

/*
 *  12 ways to iterate through a vector 
 */

namespace RangeBasedForLoop {

    // global function
    void processElement(int n)
    {
        std::cout << n << " ";
    }

    // functor: "callable object" - class which implements operator()
    class ElementProcessor
    {
    public:
        void operator() (int n) const { 
            std::cout << n << " ";
        }
    };

    void test_01()
    {
        // container of integral data type
        std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        // =========================================================================
        // "Classic style" examples

        // a) Very, very classic style ... C-stylistic
        for (size_t i = 0; i != vec.size(); ++i) {
            std::cout << vec[i] << " ";
        }
        std::cout << std::endl;

        // b) Looks like C++, very classic style
        std::for_each(
            std::begin(vec),           // Iterator-object for begin of range
            std::end(vec),             // Iterator-object for end of range
            processElement             // function pointer
        );
        std::cout << std::endl;

        // c) Same as b), modified ranges
        std::for_each(
            std::next(std::begin(vec)),    // Iterator-object for begin of range
            std::prev(std::end(vec)),      // Iterator-object for end of range
            processElement                 // function pointer
        );
        std::cout << std::endl;

        // d) Looks like C++, classic style, 'Functor'-stylistic
        std::for_each(
            std::begin(vec),               // Iterator-object for begin of range
            std::end(vec),                 // Iterator-object for end of range
            ElementProcessor{}        // "callable" object
        );
        std::cout << std::endl;

        // e) Using STL algorithm std::for_each with a lambda: Modern style
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

        // f) Using Range-based 'for' Loop: Very modern style
        for (int n : vec) {
            std::cout << n << " ";
            if (n == 2)  // break is possible
                break;
        }
        std::cout << std::endl;

        // g) Same as f), using 'const int&'
        for (const int& n : vec) {
            std::cout << n << " ";
        }
        std::cout << std::endl;

        // h) Same as f): Using 'auto' keyword to cause type inference to be used
        for (auto n : vec) {
            std::cout << n << " ";
        }
        std::cout << std::endl;

        // i) Same as g), using 'const auto&': type inference by reference
        for (const auto& n : vec) {
            std::cout << n << " ";
        }
        std::cout << std::endl;

        // j) Real C++: How the compiler 'sees' a Range-based 'for' Loop
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
