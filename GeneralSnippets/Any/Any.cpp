// =====================================================================================
// Any.cpp // Klasse std::any
// =====================================================================================

module modern_cpp:any;

namespace AnySamples {

    static void test_01_any()
    {
        std::any a{ 1 };
        std::println("{}: {}", a.type().name(), std::any_cast<int>(a));

        a = 3.14;
        std::println("{}: {}", a.type().name(), std::any_cast<double>(a));

        a = true;
        std::println("{}: {}", a.type().name(), std::any_cast<bool>(a));

        // bad cast
        try
        {
            a = 1;
            std::println("{}", std::any_cast<float>(a));
        }
        catch (const std::bad_any_cast & e)
        {
            std::println("{}", e.what());
        }

        // has value
        a = 1;

        if (a.has_value())
        {
            std::println("{}", a.type().name());
        }

        // reset
        a.reset();

        if (!a.has_value())
        {
            std::println("no value");
        }

        // pointer to contained data
        a = 1;
        int* i = std::any_cast<int>(&a);
        std::println("{}", *i);
    }

    static void test_02_any()
    {
        std::any a1{ std::make_any<std::string>("Hello, std::any!") };
        std::any a2{ std::make_any<double>(123.456) };

        std::println("{}", std::any_cast<std::string&>(a1));
        std::println("{}", std::any_cast<double&>(a2));
    }

    using Row = std::tuple<std::any, std::any, std::any>;

    // helper method (forward declaration)
    std::string to_string(const std::any&);

    static void test_03_any()
    {
        Row row1{ 1, 2, 3  };
        Row row2{ '1',  std::string{"ABC"}, 99.99 };
        Row row3{ true, 123, false  };

        std::vector<Row> mySheet{ };

        // note: conversion to base class 'std::tuple<std::any, std::any, std::any>'
        mySheet.push_back(row1);
        mySheet.push_back(row2);
        mySheet.push_back(row3);

        for (const auto& [val1, val2, val3] : mySheet) {
            std::cout
                << "Value1:  " << to_string(val1) << std::endl
                << "Value2:  " << to_string(val2) << std::endl
                << "Value3:  " << to_string(val3) << std::endl;

            std::println("Value1: {}", to_string(val1));
            std::println("Value2: {}", to_string(val2));
            std::println("Value3: {}", to_string(val3));
        }
    }

    std::string to_string(const std::any& var) 
    {
        if (var.type() == typeid (int)) {
            return std::to_string(std::any_cast<int>(var));
        }
        else if (var.type() == typeid (double)) {
            return std::to_string(std::any_cast<double>(var));
        }
        else if (var.type() == typeid (bool)) {
            return std::to_string(std::any_cast<bool>(var));
        }
        else if (var.type() == typeid (char)) {
            return std::to_string(std::any_cast<char>(var));
        }
        else if (var.type() == typeid (std::string)) {
            return std::any_cast<std::string>(var);
        }
        else {
            return std::string("<Unknown>");
        }
    }

    static void test_04_any() {

        // array with three instances of std::any (note: brace elision)
        const std::array<std::any, 3> many
        { 
            std::any{ 42 },                   // int
            std::any{ 1.23 },                 // double
            std::any{ std::string{"Hello"} }  // std::string
        };

        // use random access on the container elements.
        auto n{ std::any_cast<int>(many[0]) };
        auto f{ std::any_cast<double>(many[1]) };
        auto s{ std::any_cast<std::string>(many[2]) };

        // query the container size
        const std::size_t size = many.size();

        // iterate container with an algorithm and execute a member function
        bool hasValues{ std::all_of (
            many.cbegin(),
            many.cend(),
            [] (const auto& a) -> bool {
                return a.has_value();
            }
        ) };

        if (hasValues) {
            std::println("All std::any objects contain a value.");
        }
    }
}

void main_any()
{
    using namespace AnySamples;
    test_01_any();
    test_02_any();
    test_03_any();
    test_04_any();
}

// =====================================================================================
// End-of-File
// =====================================================================================
