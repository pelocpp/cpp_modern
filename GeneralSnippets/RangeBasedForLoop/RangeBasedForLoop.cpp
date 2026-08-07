// =====================================================================================
// RangeBasedForLoop.cpp
// =====================================================================================

module modern_cpp:range_based_for_loop;

/*
 *  12 ways to iterate through a vector 
 */

namespace RangeBasedForLoop {

    // free function
    static void processElement(int n)
    {
        std::print("{} ", n);
    }

    // functor: "callable object" - class which implements operator()
    class ElementProcessor
    {
    public:
        void operator() (int n) const { 
            std::print("{} ", n);
        }
    };

    static void test_iterations()
    {
        // container of integral data type
        std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        // =========================================================================
        // "Classic style" examples

        // a) Very, very classic style ... C-stylistic
        for (std::size_t i{}; i != vec.size(); ++i) {
            std::print("{} ", vec[i]);
        }
        std::println();

        // b) Looks like C++, very classic style
        std::for_each(
            vec.cbegin(),                   // Iterator-object for begin of range
            vec.cend(),                     // Iterator-object for end of range
            processElement                  // free function
        );
        std::println();

        // c) Same as b), modified ranges
        std::for_each(
            std::next(vec.cbegin()),        // Iterator-object for begin of range
            std::prev(vec.cend()),          // Iterator-object for end of range
            processElement                  // free function
        );
        std::println();

        // d) Looks like C++, classic style, using "callable" object
        std::for_each(
            vec.cbegin(),                   // Iterator-object for begin of range
            vec.cend(),                     // Iterator-object for end of range
            ElementProcessor{}              // "callable" object
        );
        std::println();

        // e) Using STL algorithm std::for_each with a lambda: Modern style
        std::for_each(
            vec.cbegin(),                   // Iterator-object for begin of range
            vec.cend(),                     // Iterator-object for end of range
            [](int n) {                     // anonymous method (lambda)
                std::print("{} ", n);
            }
        );
        std::println();

        // =========================================================================
        // Range-based 'for' Loop examples

        // f) Using Range-based 'for' Loop: Very modern style
        for (int n : vec) {
            std::print("{} ", n);
            if (n == 2)  // break is possible
                break;
        }
        std::println();

        // g) Same as f), using 'const int&'
        for (const int& n : vec) {
            std::print("{} ", n);
        }
        std::println();

        // h) Same as f): Using 'auto' keyword to cause type inference to be used
        for (auto n : vec) {
            std::print("{} ", n);
        }
        std::println();

        // i) Same as g), using 'const auto&': type inference by reference
        for (const auto& n : vec) {
            std::print("{} ", n);
        }
        std::println();

        // j) Real C++: How the compiler 'sees' a Range-based 'for' Loop
        std::vector<int>::const_iterator begin = vec.cbegin();
        std::vector<int>::const_iterator end = vec.cend();

        while (begin != end) {

            int n{ *begin };
            std::print("{} ", n);
            ++begin;
        }
        std::println();

        // k) Same as h), using 'auto'
        auto begin2 = vec.cbegin();
        auto end2 = vec.cend();

        while (begin2 != end2) {

            int n{ *begin2 };
            std::print("{} ", n);
            ++begin2;
        }
        std::println();

        // l) Range-based 'for' loop with initializer,
        // we can now use the index variable inside the for statement
        for (int index{}; int n : vec) {
            std::println("{}: {} ", index, n);
            ++index;
        }
    }
}

void main_range_based_for_loop()
{
    using namespace RangeBasedForLoop;
    test_iterations();
}

// =====================================================================================
// End-of-File
// =====================================================================================
