// =====================================================================================
// Generate.cpp // std::generate
// =====================================================================================

module modern_cpp:generate;

namespace AlgorithmGenerate {

    static void test_01()
    {
        std::vector<int> values(10);

        for (int i{}; i != values.size(); ++i) {

            values[i] = 1;
        } 

        std::for_each (
            values.begin(),
            values.end(),
            [](auto n) { std::print("{} ", n); }
        );

        std::println();
    }

    static void test_02()
    {
        std::vector<int> values(10);

        for (int i{}; i != values.size(); ++i) {

            values[i] = 1;
        }

        std::fill(
            values.begin(),
            values.end(),
            2
        );

        std::for_each(
            values.begin(),
            values.end(),
            [](auto n) { std::print("{} ", n); }
        );

        std::println();
    }

    static void test_03()
    {
        std::vector<int> values(10);

        std::for_each(
            values.begin(),
            values.end(),
            [count = 1](auto& n) mutable { n = count; count++; }
        );

        std::for_each(
            values.begin(),
            values.end(),
            [](int n) { std::print("{} ", n); }
        );

        std::cout << std::endl;
    }

    static void test_04()
    {
        std::vector<int> values(10);

        std::generate(
            values.begin(),
            values.end(),
            [count = 1]() mutable { return count++; }
        );

        std::for_each(
            values.begin(),
            values.end(),
            [](auto n) { std::print("{} ", n); }
        );

        std::cout << std::endl;
    }

}

void main_generate()
{
    using namespace AlgorithmGenerate;
    test_01();
    test_02();
    test_03();
    test_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
