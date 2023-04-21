// =====================================================================================
// Generate.cpp // std::generate
// =====================================================================================

module modern_cpp:generate;

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
