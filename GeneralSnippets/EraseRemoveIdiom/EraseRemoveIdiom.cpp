// =====================================================================================
// EraseRemoveIdiom.cpp // Erase-Remove Idiom
// =====================================================================================

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
        // this function call has only demonstration purposes

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

        std::print("src: ");
        print(src);

        std::remove_copy(src.begin(), src.end(), std::back_inserter(dst), 5);

        std::print("src: ");
        print(src);
        std::print("dst: ");
        print(dst);
    }

    static void test_removing_elements_51()
    {
        // 'std::remove_copy_if' algorithm

        std::vector<int> src{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::vector<int> dst{};

        std::print("src: ");
        print(src);

        std::remove_copy_if(
            src.begin(),
            src.end(),
            std::back_inserter(dst),
            [](auto elem) { return elem % 2 == 0; }
        );

        std::print("src: ");
        print(src);
        std::print("dst: ");
        print(dst);
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
}

// =====================================================================================
// End-of-File
// =====================================================================================
