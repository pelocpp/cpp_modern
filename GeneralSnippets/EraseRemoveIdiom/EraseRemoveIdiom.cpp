// =====================================================================================
// EraseRemoveIdiom.cpp // Erase-Remove Idiom
// =====================================================================================

module modern_cpp:erase_remove_idiom;

namespace EraseRemoveIdiom
{
    auto print = [](const std::vector<int>& v) {
        std::cout << "Length:   " << v.size() << std::endl;
        std::cout << "Capacity: " << v.capacity() << std::endl;
        std::for_each(std::begin(v), std::end(v), [](const auto& e) {
            std::cout << e << ' ';
            }
        );
        std::cout << std::endl << std::endl;
    };

    void test_01()
    {
        std::vector<int> vec = { 0, 1, 2, 5, 4, 5, 6, 5, 8, 9 };
        print(vec);

        // remove all '5' elements
        auto it = std::remove(vec.begin(), vec.end(), 5);
        std::cout << "Position of iterator: " << std::distance(vec.begin(), it) << std::endl;
        print(vec);

        // erase the unspecified values and reduce the physical size
        // of the container to match its new logical size
        vec.erase(it, vec.end());
        print(vec);
    }

    void test_02()
    {
        std::vector<int> vec = { 0, 1, 2, 5, 4, 5, 6, 5, 8, 9 };
        print(vec);

        // remove all elements with the value 5
        vec.erase(std::remove(vec.begin(), vec.end(), 5), vec.end());
        print(vec);

        // request the container to reduce its capacity to fit its size
        vec.shrink_to_fit();
        print(vec);
    }
}

void main_erase_remove_idiom()
{
    using namespace EraseRemoveIdiom;
    test_01();
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
