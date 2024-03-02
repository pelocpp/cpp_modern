// =====================================================================================
// Bind.cpp
// =====================================================================================

module modern_cpp:bind;

namespace Bind {

    static void test_01() {

        using namespace std::placeholders;  // for _1, _2, _3...

        std::vector<double> numbers{ 1, 2, 3, 4, 5, 6 };

        std::vector<double> result(6);

        for (double n : numbers) {
            std::cout << n << '\t';
        }
        std::cout << std::endl;

        std::transform(
            numbers.begin(),
            numbers.end(),
            result.begin(),
            std::bind((double (*)(double, int)) std::pow, _1, 2)
        );

        // or

        //auto g = std::bind((double (*)(double, int)) std::pow, _1, 2);
        //std::transform(
        //    numbers.begin(),
        //    numbers.end(),
        //    result.begin(),
        //    g
        //);

        for (double n : result) {
            std::cout << n << '\t';
        }
        std::cout << std::endl;

        std::transform(
            numbers.begin(),
            numbers.end(),
            result.begin(),
            [](auto value) {
                double result = std::pow(value, 3);
                return result;
            }
        );

        for (double n : result) {
            std::cout << n << '\t';
        }

        // doesn't compile - ambiguous call to overloaded function std::pow 
        //std::transform(
        //    numbers.begin(),
        //    numbers.end(),
        //    result.begin(),
        //    std::bind(std::pow, std::placeholders::_1, 7.0)
        //);

        std::cout << std::endl;
    }
}

void main_bind()
{
    using namespace Bind;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
