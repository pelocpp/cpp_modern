// =====================================================================================
// Optional.cpp // std::optional
// =====================================================================================

module;

#include <print>

module modern_cpp:optional;

import std;

namespace {

    /*
    * Introduction
    */

    void test_01_optional() {

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

    void test_02_optional() {

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

    std::optional<double> divide(double a, double b) {

        if (b != 0.0) { 
            return a / b; 
        }

        return std::nullopt;
    }

    void test_03_optional() {

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

    void test_04_optional() {

        // construct a std::vector<int> object inside std::optional in-place
        std::optional<std::vector<int>> optVec{
            std::make_optional<std::vector<int>>(5, 123)   // { 123, 123, 123, 123, 123 }
        };

        std::copy(
            optVec->begin(),
            optVec->end(),
            std::ostream_iterator<int>(std::cout, ", ")
        );
        std::println();

        std::set<int> ints{ 1, 2, 3, 4, 5 };

        // construct a std::vector<int> object inside std::optional in-place
        optVec.emplace(ints.begin(), ints.end());

        std::copy(
            optVec->begin(),
            optVec->end(),
            std::ostream_iterator<int>(std::cout, ", ")
        );
        std::println();
    }

    // =================================================================================

    /*
     * Demonstrating monadic interface for std::optional
     */

    struct User
    {
        std::string name;
        std::optional<std::string> email;  // not every user has one
    };

    const std::map<std::size_t, User> database =
    {
        { 1, { "Sepp", "sepp@gmx.de" } },
        { 2, { "Anton", std::nullopt } },
        { 3, { "Hubert", "hubert@GMAIL.COM" } },
        { 4, { "Franz", "www.franzschneider.com" } }
    };

    std::optional<User> findUser(int id) {
        if (auto it = database.find(id); it != database.end()) {
            return it->second;
        }

        return std::nullopt;
    }

    std::optional<std::string> emailDomain(const std::string& email) {
        auto at = email.find('@');
        if (at == std::string::npos) {
            return std::nullopt;
        }

        return email.substr(at + 1);
    }

    std::string toLower(std::string s) {

        std::transform(
            s.begin(),
            s.end(),
            s.begin(),
            [](unsigned char c) { return std::tolower(c); }
        );
        return s;
    }

    std::optional<std::string> domainOf(int id) {
        return findUser(id)                                     // -> optional<User>
            .and_then([](const User& u) { return u.email; })    // -> optional<string>
            .and_then(emailDomain)                              // -> optional<string>
            .transform(toLower);                                // string -> string, re-wrapped
    }

    void test_04_optional_monadic()
    {
        for (int id : { 0, 1, 2, 3, 4, 5 }) {
            auto domain = domainOf(id).or_else([] {
                // std::println("  >>> no valid domain found");
                return std::optional<std::string>{};
                }
            );
            std::println("{}: {}", id, domain.value_or("<none>"));
        }
    }
}

void main_optional()
{
    test_01_optional();
    test_02_optional();
    test_03_optional();
    test_04_optional();
    test_04_optional_monadic();
}

// =====================================================================================
// End-of-File
// =====================================================================================
