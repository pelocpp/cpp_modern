// =====================================================================================
// Template Specialization
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>

namespace TemplateSpecialization {

    // ==================================================
    // Explicit Template Specialization

    template<typename T>
    class GenericSorter
    {
    public:
        static void sort(std::vector<T>&)
        {
            /* ... */
        };
    };

    template<>
    class GenericSorter<char>
    {
    public:
        static void sort(std::vector<char>&)
        {
            /* ... */
        };
    };

    void test_explicit_template_specialization_01()
    {
        std::vector<int>  vi;
        std::vector<char> vc;

        GenericSorter<int>::sort(vi);   // calls sort<std::vector<int>>
        GenericSorter<char>::sort(vc);  // calls specialized sort<std::vector<char>>
    }

    // ==================================================
    // Partial Template Specialization

    template<typename T1, typename T2, int I>
    class A {};                                        // #1

    template<typename T, int I>
    class A<T, T*, I> {};                              // #2

    template<typename T1, typename T2, int I>
    class A<T1*, T2, I> {};                            // #3

    template<typename T>
    class A<int, T*, 5> {};                            // #4

    template<typename T1, typename T2, int I>
    class A<T1, T2*, I> {};                            // #5

    void test_partial_template_specialization_02()
    {
        [[maybe_unused]]  A<int, int, 1>   a1;  // uses #1

        [[maybe_unused]]  A<int, int*, 1>  a2;  // uses #2, T is int,
                                                //          I is 1

        [[maybe_unused]]  A<int, char*, 5> a3;  // uses #4, T is char

        [[maybe_unused]]  A<int, char*, 1> a4;  // uses #5, T1 is int,
                                                //          T2 is char,
                                                //          I is 1

        // A<int*, int*, 2> a5;  // ambiguous:
        //                       // matches #3 and #5
    }
}

void main_template_specialization()
{
    using namespace TemplateSpecialization;
    test_explicit_template_specialization_01();
    test_partial_template_specialization_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
