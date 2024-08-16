// =====================================================================================
// Generate.cpp // std::generate
// =====================================================================================

module modern_cpp:generate;

namespace AlgorithmGenerate {

    static void test_01()
    {
        std::vector<int> values(10);

        std::generate(
            values.begin(),
            values.end(),
            [count = 1]() mutable { return count++; }
        );

        std::copy(
            values.begin(),
            values.end(),
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
