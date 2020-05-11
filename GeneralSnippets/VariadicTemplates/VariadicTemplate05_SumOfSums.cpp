// =====================================================================================
// Variadic Templates - Sum of Sums
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>

namespace VariadicTemplatesSumofSums {

    template<typename... CONTAINERS>
    int sumOfSums(const CONTAINERS&... conts) {
        const auto sums = std::initializer_list<int>{
            std::accumulate(std::begin(conts),  std::end(conts), 0) ...
        };
        return std::accumulate(std::begin(sums), std::end(sums), 0);
    }

    void test_01() {
        std::vector<int> vec { 1, 2, 3, 4, 5  };
        int sum = std::accumulate(std::begin(vec), std::end(vec), 0);
        std::cout << "sum: " << sum << std::endl;
    }

    void test_02() {
        std::vector<int> vec1{ 1, 2, 3, 4, 5 };
        std::vector<int> vec2{ 6, 7, 8, 9, 10 };
        std::deque<int> queue { 11, 12, 13, 14, 15 };

        int totalSum = sumOfSums(vec1, vec2, queue);
        std::cout << "totalSum: " << totalSum << std::endl;
    }
}

int main_variadic_sum_of_sums()
{
    using namespace VariadicTemplatesSumofSums;
    test_01();
    std::cout << std::endl;
    test_02();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
