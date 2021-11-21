// =====================================================================================
// std::generate
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

namespace AlgorithmGenerate {

    void test_01()
    {
        std::vector<int> values(10);

        std::generate(
            std::begin(values),
            std::end(values),
            [count = 1]() mutable { return count++; }
        );

        std::copy(
            std::begin(values),
            std::end(values),
            std::ostream_iterator<int>(std::cout, " ")
        );

        std::cout << std::endl;
    }
}

void main_generate()
{
    using namespace AlgorithmGenerate;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
