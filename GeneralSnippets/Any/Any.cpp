// =====================================================================================
// Any.cpp // Klasse std::any
// =====================================================================================

module modern_cpp:any;

namespace AnySamples {

    void test_01_any() 
    {
        std::any a{ 1 };
        std::cout << a.type().name() << ": " << std::any_cast<int>(a) << std::endl;

        a = 3.14;
        std::cout << a.type().name() << ": " << std::any_cast<double>(a) << std::endl;

        a = true;
        std::cout << a.type().name() << ": " << std::any_cast<bool>(a) << std::endl;

        // bad cast
        try
        {
            a = 1;
            std::cout << std::any_cast<float>(a) << std::endl;
        }
        catch (const std::bad_any_cast & e)
        {
            std::cout << e.what() << std::endl;
        }

        // has value
        a = 1;
        if (a.has_value())
        {
            std::cout << a.type().name() << std::endl;
        }

        // reset
        a.reset();
        if (!a.has_value())
        {
            std::cout << "no value\n";
        }

        // pointer to contained data
        a = 1;
        int* i = std::any_cast<int>(&a);
        std::cout << *i << std::endl;
    }

    void test_02_any()
    {
        std::any a1 = std::make_any<std::string>("Hello, std::any!");
        std::any a2 = std::make_any<std::complex<double>>(1.5, 2.5);

        std::cout << std::any_cast<std::string&>(a1) << std::endl;
        std::cout << std::any_cast<std::complex<double>&>(a2) << std::endl;
    }

    using Row = std::tuple<std::any, std::any, std::any>;

    // helper method (forward declaration)
    std::string to_string(const std::any&);

    void test_03_any() 
    {
        Row row1{ 1, 2, 3  };
        Row row2{ '1',  std::string("ABC"), 99.99  };
        Row row3{  true, 123, false  };

        std::vector<Row> mySheet;

        // note: conversion to base class 'std::tuple<std::any, std::any, std::any>'
        mySheet.push_back(row1);
        mySheet.push_back(row2);
        mySheet.push_back(row3);

        for (const auto& [val1, val2, val3] : mySheet) {
            std::cout
                << "Val1:    " << to_string(val1) << std::endl
                << "Val2:    " << to_string(val2) << std::endl
                << "Val3:    " << to_string(val3) << std::endl;
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
}

void main_any()
{
    using namespace AnySamples;
    test_01_any();
    test_02_any();
    test_03_any();
}

// =====================================================================================
// End-of-File
// =====================================================================================
