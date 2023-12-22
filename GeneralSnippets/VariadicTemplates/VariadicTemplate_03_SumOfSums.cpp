// =====================================================================================
// VariadicTemplate_03_SumOfSums.cpp // Variadic Templates - Sum of Sums
// =====================================================================================

module modern_cpp:variadic_templates;

namespace VariadicTemplatesSumofSums {

    template<typename ... TContainer>
    int sumOfSums(const TContainer& ... conts) {
        auto sums = std::initializer_list<int> {
            std::accumulate(std::begin(conts), std::end(conts), 0) ...
        };
        return std::accumulate(std::begin(sums), std::end(sums), 0);
    }

    static void test_01() {
        std::vector<int> vec { 1, 2, 3, 4, 5  };
        int sum = std::accumulate(std::begin(vec), std::end(vec), 0);
        std::cout << "sum: " << sum << std::endl;
    }

    static void test_02() {
        std::vector<int> vec{ 1, 2, 3, 4, 5 };
        std::deque<int> queue { 6, 7, 8, 9, 10 };
        std::list<int> list{ 11, 12, 13, 14, 15 };

        int totalSum = sumOfSums(vec, queue, list);
        std::cout << "totalSum: " << totalSum << std::endl;
    }
}

void main_variadic_templates_sum_of_sums()
{
    using namespace VariadicTemplatesSumofSums;
    test_01();
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
