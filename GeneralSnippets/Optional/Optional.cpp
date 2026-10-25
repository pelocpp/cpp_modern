// =====================================================================================
// Optional.cpp // std::optional
// =====================================================================================

module;

#include <print>      // module implementation too unstable

module modern_cpp:optional;

import std;

namespace {

    /*
    * Introduction
    */

    void optional_01_standard_creation() {

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
            std::println("std::optional variable does not contain a value!");
        }
    }

    void optional_02_more_creation_options() {

        // direct:
        std::optional<int> oInt(10);
        std::optional oIntDeduced(10); // deduction guides

        // make_optional
        auto optDouble = std::make_optional(3.0);
        auto optComplex = std::make_optional<std::complex<double>>(3.0, 4.0);

        // in_place
        std::optional<std::complex<double>> optComplex2{ std::in_place, 3.0, 4.0 };

        // will call vector with direct init of {1, 2, 3}
        std::optional<std::vector<int>> oVec{ std::in_place,{ 1, 2, 3 } };

        std::optional<std::string> jack{ "Jack" };
        std::println("{}", jack.value());        // OK: contains a value

        jack.reset(); // now empty

        try
        {
            std::println("{}", jack.value());        // no value exists
        }
        catch (const std::bad_optional_access&)
        {
            std::println("No nickname");
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

    void optional_03_with_methods() {

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

    void optional_04_value_or() {

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

    void optional_05_monadic()
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
    optional_01_standard_creation();
    optional_02_more_creation_options();
    optional_03_with_methods();
    optional_04_value_or();
    optional_05_monadic();
}

// =====================================================================================
// End-of-File
// =====================================================================================
