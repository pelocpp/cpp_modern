// =====================================================================================
// Optional.cpp // std::optional
// =====================================================================================

module modern_cpp:optional;

namespace OptionalExamples {

    /*
    * Introduction
    */

    static void test_01_optional() {

        std::optional<int> someValue{ 123 };

        if (someValue.has_value()) {
            std::println("Value: {}", someValue.value());
        }

        if (someValue) {
            // providing an interface similar to smart pointers
            std::println("Value: {}", *someValue);
        }

        someValue = std::nullopt;

        if (someValue.has_value()) {
            std::println("Value: {}", someValue.value());
        }
        else {
            std::println("someValue does not contain a value!");
        }
    }

    /*
    * Using optionals to represent the absence of a value
    */ 

    class Contact
    {
    private:
        std::optional<std::string> m_phone;

    public:
        Contact() : m_phone{ std::nullopt } {}

        void setPhone(const std::string& phone) { m_phone = phone; }

        std::optional<std::string> getPhone() { return m_phone; }
    };

    static void test_02_optional() {

        Contact contact{};

        if (contact.getPhone()) {
            std::println("Number: {}", contact.getPhone().value());
        }
        else {
            std::println("No Number found!");
        }

        contact.setPhone("123456789");

        if (contact.getPhone()) {
            std::println("Number: {}", *contact.getPhone());
        }
        else {
            std::println("No Number found!");
        }
    }

    /*
    * Using optionals as return value / std::optional<T>::value_or()
    */

    static std::optional<double> divide(double a, double b) {

        if (b != 0.0) { 
            return a / b; 
        }

        return std::nullopt;
    }

    static void test_03_optional() {

        auto result{ divide(1.0, 3.0) };

        if (result.has_value()) {
            std::println("Result: {}", result.value());
        }
        else {
            std::println("Division by zero!");
        }

        result = divide(1.0, 0.0);

        if (result.has_value()) {
            std::println("Result: {}", result.value());
        }
        else {
            std::println("Division by zero!");
        }

        // Alternatively you can use std::optional<T>::value_or()
        // to use either the result or a default value

        result = divide(1.0, 1.0);

        const double defaultValue{};

        auto value = result.value_or(defaultValue);

        std::println("Result (or default value): {}", value);
    }

    /*
    * Demonstrating std::optional and emplace
    */

    static void test_04_optional() {

        // construct a std::vector<int> object inside std::optional in-place
        std::optional<std::vector<int>> optVec{
            std::make_optional<std::vector<int>>(5, 123)   // { 123, 123, 123, 123, 123 }
        };

        std::copy(
            optVec->begin(),
            optVec->end(),
            std::ostream_iterator<int>(std::cout, ", ")
        );
        std::cout << std::endl;

        std::set<int> ints{ 1, 2, 3, 4, 5 };

        // construct a std::vector<int> object inside std::optional in-place
        optVec.emplace(ints.begin(), ints.end());

        std::copy(
            optVec->begin(),
            optVec->end(),
            std::ostream_iterator<int>(std::cout, ", ")
        );
        std::cout << std::endl;
    }

    // =================================================================================

    /*
     * Demonstrating monadic interface for std::optional
     */

     // =================================================================
     // and_then

    static void test_01_optional_monadic()
    {
        std::optional<int> n{ 123 };
        // or
        // std::optional<int> n{ std::nullopt };

        auto result = n.and_then([](auto x) /*-> std::optional<std::string>*/ {
            if (x == 123) {
                return std::optional<std::string>("Got expected value 123");
            }
            else {
                //return std::nullopt;
                return std::optional<std::string>("Got unexpected value! ");
            }
            });

        if (result) {
            std::println("{}", result.value());
        }

        std::println("Done.");
    }

    class User
    {
    public:
        std::string m_first;
        std::string m_last;
        std::size_t m_age;
    };

    static std::optional<std::string> hasValidName(const User& user) {
        if (!user.m_first.empty() and !user.m_last.empty()) {
            return user.m_first + " " + user.m_last;
        }
        else {
            return std::nullopt;
        }
    }

    static void test_02_optional_monadic()
    {
        auto user = std::make_optional<User>("Hans", "Mueller", 30);
        // or
        // auto user = std::make_optional<User>("Sepp", "", 30);

        auto result = user.and_then([](const auto& user) {
            return hasValidName(user);
            });

        if (result) {
            std::println("Result: {}", result.value());
        }

        std::println("Done.");
    }

    // =================================================================
    // or_else

    static void test_03_optional_monadic()
    {
        auto user = std::make_optional<User>("Hans", "Mueller", 30);
        // or
        // auto user = std::make_optional<User>("Sepp", "", 30);

        auto result = user.and_then([](const auto& user) {
            return hasValidName(user);
            }).or_else([]() {
                return std::optional<std::string>{"Max Mustermann"};
            });

        if (result) {
            std::println("Result: {}", result.value());
        }

        std::println("Done.");
    }

    // =================================================================
    // transform

    static void test_04_optional_monadic()
    {
        auto user = std::make_optional<User>("Hans", "Mueller", 30);
        // or
        // auto user = std::make_optional<User>("Sepp", "", 30);

        auto result = user.and_then([](const auto& user) {
            return hasValidName(user);
            }).transform([](auto name) {

                std::transform(
                    name.begin(),
                    name.end(),
                    name.begin(),
                    [](unsigned char c) { return std::toupper(c); }
                );

                return name;
            });

        if (result) {
            std::println("Result: {}", result.value());
        }

        std::println("Done.");
    }
}

void main_optional()
{
    using namespace OptionalExamples;

    test_01_optional();
    test_02_optional();
    test_03_optional();
    test_04_optional();

    test_01_optional_monadic();
    test_02_optional_monadic();
    test_03_optional_monadic();
    test_04_optional_monadic();
}

// =====================================================================================
// End-of-File
// =====================================================================================
