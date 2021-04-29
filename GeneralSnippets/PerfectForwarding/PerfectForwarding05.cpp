// =====================================================================================
// Perfect Forwarding 05
// =====================================================================================

#include <iostream>
#include <vector>
#include <string>

namespace PerfectForwardingRemoveReferenceDemo {

    // ====================================================================
    // using a container directly

    void test_01() {

        std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        using Iterator = std::vector<int>::iterator;
        using ValueType = std::vector<int>::value_type;

        ValueType value = 5;
        Iterator it = std::find(std::begin(vec), std::end(vec), value);

        if (it != std::end(vec)) {
            std::cout << "Found value " << value << std::endl;
        }
        else {
            std::cout << "Value " << value << " not found!" << std::endl;
        }
    }

    // ====================================================================
    // using a container indirectly - in a template function - first try

    template<typename TCONTAINER>
    using ValueTypeEx = typename TCONTAINER::value_type;

    template<typename TCONTAINER>
    using IteratorEx = typename TCONTAINER::iterator;

    template<typename TCONTAINER>
    bool contains_0(TCONTAINER&& cont, ValueTypeEx<TCONTAINER> const& value)
    {
        IteratorEx<TCONTAINER> it = std::find(std::begin(cont), std::end(cont), value);
        return (it != std::end(cont)) ? true : false;
    }

    void test_02() {
        std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        // bool found = contains_0(vec, 6);  // doesn't compile
    }

    // ====================================================================
    // using a container indirectly - in a template function

    template<typename TCONTAINER>
    using ValueType = typename std::remove_reference<TCONTAINER>::type::value_type;

    template<typename TCONTAINER>
    using Iterator = typename std::remove_reference<TCONTAINER>::type::iterator;

    template<typename TCONTAINER>
    bool contains(TCONTAINER&& cont, ValueType<TCONTAINER> const& value)
    {
        Iterator<TCONTAINER> it = std::find(std::begin(cont), std::end(cont), value);
        return (it != std::end(cont)) ? true : false;
    }

    void test_03() {
        std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        bool found = contains(vec, 6);
        std::cout << std::boolalpha << found << std::endl;
    }
}

void main_perfect_remove_reference_demo()
{
    using namespace PerfectForwardingRemoveReferenceDemo;
    test_01();
    test_02();
    test_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
