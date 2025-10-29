// =====================================================================================
// Excepted.cpp // std::expected
// =====================================================================================

module modern_cpp:expected;

namespace StdExpected {

    //==================================================================================
    // classical implementions with error handling: using return codes
    
    static bool divideReturnCode(double numerator, double denominator, double& result, std::string& error) {

        if (denominator == 0.0) {
            error = "Error: Division by zero";
            return false;
        }

        result = numerator / denominator;
        return true;
    }

    //==================================================================================
    // classical implementions with error handling: using exceptions

    static double divideException(double numerator, double denominator) {

        if (denominator == 0.0) {
            throw std::runtime_error("Error: Division by zero");
        }

        return numerator / denominator;
    }

    static void testDivideException()
    {
        // -------------------------------------------------------------------
        // demonstrating use of return codes

        double result{};
        std::string error{};

        bool success{ divideReturnCode(10, 0, result, error) };
        if (!success) {
            std::println("Error: {}", error);
        }

        // -------------------------------------------------------------------
        // demonstrating use of exception handling

        try
        {
            divideException(10, 0);
        }
        catch (const std::runtime_error& error)
        {
            std::println("Error: {}", error.what());
        }
        catch (const std::exception& error)
        {
            std::println("Error: {}", error.what());
        }
    }

    //==================================================================================
    // std::expected

    static std::expected<double, std::string> divide(double numerator, double denominator) {

        if (denominator == 0.0) {
            return std::unexpected{ "Error: Division by zero" };
        }

        return std::expected<double, std::string> { numerator / denominator };
    }

    static void test_excepted_01()
    {
        auto numerator = 10.0;
        auto denominator = 2.5;

        auto result = divide(numerator, denominator);

        if (result.has_value()) {
            std::println("{} / {} = {}", numerator, denominator, result.value());
        }

        denominator = 0.0;

        result = divide(numerator, denominator);

        if (!result.has_value()) {
            std::println("Error: {}", result.error());
        }
    }

    //==================================================================================
    // and_then

    static auto square(auto value) {
        return value * value;
    }

    static std::expected<double, std::string> squareIfSuccess(double numerator, double denominator) {

        auto result{ divide(numerator, denominator) };

        auto squareResult{ result.and_then(
            [](auto value) {
                return std::expected<double, std::string>{ square(value) };
            })
        };

        return squareResult;
    }

    static std::expected<double, std::string> squareIfSuccessEx(double numerator, double denominator) {

        return divide(numerator, denominator).and_then(
            [](auto value) {
                return std::expected<double, std::string>(square(value));
            }
        );
    }
 
    static void test_excepted_02()
    {
        auto numerator = 10.0;
        auto denominator = 2.5;

        auto result = squareIfSuccess(numerator, denominator);

        if (result.has_value()) {
            std::println("Square: {}", result.value());
        }

        denominator = 0.0;

        result = squareIfSuccess(numerator, denominator);

        if (!result.has_value()) {
            std::println("Error: {}", result.error());
        }
    }

    //==================================================================================
    // transform

    static void test_excepted_03()
    {
        auto numerator = 10.0;
        auto denominator = 2.5;

        auto result = divide(numerator, denominator);

        if (result.has_value())
        {
            auto transformedResult = result.transform([](auto value) { return value + 1; });

            // check result
            if (transformedResult.has_value()) {
                std::println("Result: {}", transformedResult.value());
            }
        }

        denominator = 0.0;

        result = divide(numerator, denominator);

        if (!result.has_value()) {

            std::println("Error: {}", result.error());
        }
    }

    static void test_excepted_04()
    {
        auto numerator = 10.0;
        auto denominator = 2.5;

        // using transform to apply a transformation to the value if it exists
        auto result = divide(numerator, denominator).transform([](auto value) {
            return value + 1;
            }
        );

        // check result
        if (result.has_value()) {
            std::println("Result: {}", result.value());
        }

        denominator = 0.0;

        result = divide(numerator, denominator).transform([](auto value) {
            return value + 1;
            }
        );

        // check result
        if (!result.has_value()) {
            std::println("Error: {}", result.error());
        }
    }

    //==================================================================================
    // more chaining: or_else

    // add five
    static std::expected<double, std::string> add_five(double value) {
        return value + 5;
    }

    // to the power of three
    static std::expected<double, std::string> powerOfThree(double value) {
        return value * value * value;
    }

    // now we are calling a dangerous function
    static std::expected<double, std::string> russianRoulette(double value) {

        auto remainder = static_cast<int>(value) % 2;

        if (remainder == 0) {
            return std::unexpected{ "Error: Value is multiple of Two" };
        }
        else
        {
            return static_cast<double>(value);
        }
    }

    static void test_excepted_05()
    {
        auto numerator = 20.0;
        auto denominator = 2.5;         // success
        // auto denominator = 20.0;     // error

        auto result = divide(numerator, denominator)
            .and_then(add_five)
            .and_then(powerOfThree)
            .and_then(russianRoulette)
            .and_then(powerOfThree);

        // check
        if (result.has_value()) {
            std::println("Final Result: {}", result.value());
        }
        else {
            std::println("Error: {}", result.error());
        }
    }

    static void test_excepted_06()
    {
        auto numerator = 20.0;
        auto denominator = 0.0;

        // use 'or_else' to handle errors
        auto errorResult = divide(numerator, denominator)
            .and_then(add_five)
            .and_then(powerOfThree)
            .or_else([](const std::string& error) {
                std::println("Error occurred: {}", error);
                return std::expected<double, std::string>(0); // providing a default value
            }
        );

        // check
        if (errorResult.has_value()) {
            std::println("Result: {}", errorResult.value());
        }
        else {
            std::println("Error: {}", errorResult.error());
        }
    }
}

void main_expected()
{
    using namespace StdExpected;

    test_excepted_01();   // std::expected
    test_excepted_02();   // and_then
    test_excepted_03();   // transform
    test_excepted_04();   // transform
    test_excepted_05();
    test_excepted_06();
}

// =====================================================================================
// End-of-File
// =====================================================================================
