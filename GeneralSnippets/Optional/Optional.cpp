// =====================================================================================
// Optional.cpp // std::optional
// =====================================================================================

module modern_cpp:optional;

namespace OptionalExamples {

    /*
    * Introduction
    */

    static void test_01_optional() {

        std::optional<int> someValue;

        if (someValue.has_value()) {
            
            std::cout << "Value:" << someValue.value() << std::endl;
        }

        someValue = std::nullopt;

        if (someValue) {

            std::cout << "Value:" << someValue.value() << std::endl;
        }

        someValue = 123;

        if (someValue.has_value()) {

            std::cout << "Value: " << someValue.value() << std::endl;
        }

        if (someValue) {

            // providing an interface similar to smart pointers
            std::cout << "Value: " << *someValue << std::endl;
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

        void setPhone(std::string phone) { m_phone = phone; }

        std::optional<std::string> getPhone() { return m_phone; }
    };

    static void test_02_optional() {

        Contact contact{};

        if (contact.getPhone()) {
            std::cout << "Number: " << contact.getPhone().value() << std::endl;
        }
        else {
            std::cout << "No Number found!" << std::endl;
        }

        contact.setPhone("123456789");

        if (contact.getPhone()) {
            std::cout << "Number: " << *contact.getPhone() << std::endl;
        }
        else {
            std::cout << "No Number found!" << std::endl;
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

            std::cout << "Result: " << result.value() << std::endl;
        }
        else {
            std::cout << "Division by zero!" << std::endl;
        }

        result = divide(1.0, 0.0);

        if (result.has_value()) {

            std::cout << "Result: " << result.value() << std::endl;
        }
        else {
            std::cout << "Division by zero!" << std::endl;
        }

        // Alternatively you can use std::optional<T>::value_or()
        // to use either the result or a default value

        result = divide(1.0, 1.0);

        const double defaultValue{};

        auto value = result.value_or(defaultValue);

        std::cout << "Result (or default value): " << value << std::endl;
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
}

void main_optional()
{
    using namespace OptionalExamples;
    test_01_optional();
    test_02_optional();
    test_03_optional();
    test_04_optional();
}

// =====================================================================================
// End-of-File
// =====================================================================================
