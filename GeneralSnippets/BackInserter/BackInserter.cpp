// =====================================================================================
// BackInserter.cpp
// =====================================================================================

module modern_cpp:back_inserter;

namespace BackInserter {

    static void test_01() {

        // declaring first container 
        std::vector<int> vec1 = { 1, 2, 3 };

        // declaring second container for copying values 
        std::vector<int> vec2 = { 4, 5, 6 };

        // using std::back_inserter inside std::copy 
        std::copy(
            vec1.begin(),
            vec1.end(),
            std::back_inserter(vec2)
        );

        std::cout << "vec1 = ";
        std::copy(
            vec1.begin(),
            vec1.end(),
            std::ostream_iterator<int>(std::cout, " ")
        );
        std::cout << std::endl;

        std::cout << "vec2 = ";
        std::copy(
            vec2.begin(),
            vec2.end(),
            std::ostream_iterator<int>(std::cout, " ")
        );
        std::cout << std::endl;
    }

    static void test_02() {

        // No prior knowledge of size of container required : 
        // One of the scenario where such a function can be extremely helpful is
        // when we don’t know the size of the container, i.e., how many elements
        // will be inserted into it, so one way is to make that container
        // of extremely large size, but the most efficient way will be
        // to use std::back_inserter() in such a case,
        // without declaring the size of the container.

        // declaring first container 
        std::vector<int> vec1 = { 1, 2, 3 };

        // declaring second container without specifying its size 
        std::vector<int> vec2;

        // using std::back_inserter inside std::copy 
        std::copy(
            vec1.begin(),
            vec1.end(),
            std::back_inserter(vec2)
        );
        // v2 now contains 1 2 3 

        // displaying v1 and v2 
        std::cout << "vec1 = ";
        std::copy(
            vec1.begin(),
            vec1.end(),
            std::ostream_iterator<int>(std::cout, " ")
        );
        std::cout << std::endl;

        std::cout << "vec2 = ";
        std::copy(
            vec2.begin(),
            vec2.end(),
            std::ostream_iterator<int>(std::cout, " ")
        );
        std::cout << std::endl;
    }
}

void main_back_inserter()
{
    using namespace BackInserter;
    test_01();
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
