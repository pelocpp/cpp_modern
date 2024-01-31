// =====================================================================================
// Variant.cpp // std::variant
// =====================================================================================

module modern_cpp:variant;

namespace VariantDemo {

    static void test_01() {

        std::variant<int, double, std::string> var{ 123 };

        // std::get with type
        std::cout
            << var.index()
            << ", value "
            << std::get<int>(var)
            << std::endl;

        // works too: std::get with index
        std::cout
            << var.index()
            << ", value "
            << std::get<0>(var)
            << std::endl;

        var = std::string{ "Hello" }; // we're now a std::string

        std::cout
            << var.index()
            << ", value "
            << std::get<std::string>(var)
            << std::endl;

        var = 123.456; // we're now a double

        std::cout
            << var.index()
            << ", value "
            << std::get<double>(var)
            << std::endl;

        var.emplace<2>("Hello again"); // we're now a string again

        std::cout
            << var.index()
            << ", value "
            << std::get<std::string>(var)
            << std::endl;

        // std::get returns a reference, so you can change the value:

        std::get<std::string>(var) += std::string{ " World" };

        std::cout
            << var.index()
            << ", value "
            << std::get<std::string>(var)
            << std::endl;

        var = 654.321;
        if (auto pd = std::get_if<double>(&var); pd != nullptr) {
            *pd *= 2.0;
        }

        std::cout
            << var.index()
            << ", value "
            << std::get<double>(var)
            << std::endl;
    }

    // -------------------------------------------------------------------

    static void test_02() {

        // accessing a variant

        std::variant<int, double, std::string> var{ std::string{ "Hello" } };

        std::cout
            << var.index()
            << ", value "
            << std::get<std::string>(var)
            << std::endl;

        try
        {
            auto f = std::get<double>(var);
            std::cout << "double! " << f << "\n";
        }
        catch (std::bad_variant_access&)
        {
            std::cout << "Variant doesn't hold float at this moment ..." << std::endl;
        }

        var = 123;

        std::cout
            << var.index()
            << ", value "
            << std::get<int>(var)
            << std::endl;

        if (auto ip = std::get_if<0>(&var)) {
            std::cout << "int! => " << *ip << std::endl;
        }
    }

    // -------------------------------------------------------------------

    static void test_03() {

        std::variant<int, double, std::string> var{ 123 };

        // using a generic visitor (matching all types in the variant)
        auto visitor = [](const auto& elem) {
            std::cout << elem << std::endl;
        };

        std::visit(visitor, var);

        var = 123.456;
        std::visit(visitor, var);

        var = std::string{ "Hello" };
        std::visit(visitor, var);
    }

    // -------------------------------------------------------------------

    class Visitor
    {
    public:
        Visitor() = default;

        void operator() (int n) {
            std::cout << "int: " << n << std::endl;
        }

        void operator() (double f) {
            std::cout << "double: " << f << std::endl;
        }

        void operator() (std::string s) {
            std::cout << "std::string: " << s << std::endl;
        }
    };

    static void test_04() {

        std::variant<int, double, std::string> var{ 123 };

        Visitor visitor{};

        std::visit(visitor, var);

        var = 123.456;
        std::visit(visitor, var);

        var = std::string{ "Hello" };
        std::visit(visitor, var);
    }

    // -------------------------------------------------------------------

    static void test_05() {

        std::vector<std::variant<int, long, long long, float, double>>
            vec = { 100, 200l, 300ll, 400.5f, 500.5 };

        // display each value
        std::cout << "Values:      ";
        for (const auto& var : vec) {
            std::visit([](const auto& n) { std::cout << n << " "; }, var);
        }
        std::cout << std::endl;

        // display each type
        std::cout << "Types:       ";
        for (const auto& var : vec) {
            std::visit([](const auto& arg) { std::cout << typeid(arg).name() << " "; }, var);
        }
        std::cout << std::endl; 

        // get the sum
        std::common_type<int, long, long long, float, double>::type res{};
        std::cout << "Type of Sum: " << typeid(res).name() << std::endl;

        for (const auto& var : vec) {
            std::visit([&res](const auto& arg) { res += arg; }, var);
        }
        std::cout << "Sum:         " << res << std::endl;

        // double each value of the vector
        std::cout << "Values:      ";
        for (auto& var : vec) {
            std::visit([](auto& arg) { arg *= 2; }, var);
            std::visit([](const auto& arg) { std::cout << arg << " "; }, var);
        }
        std::cout << std::endl;
    }

    // -------------------------------------------------------------------

    template<class... Ts>
    struct Overload : Ts... { using Ts::operator()...; };
    
    template<class... Ts> Overload(Ts...) -> Overload<Ts...>;

    static void test_06() {

        std::variant<int, double, std::string> intFloatString{ "Hello" };

        std::visit(Overload{
            [](const int& i) { std::cout << "int: " << i << std::endl; },
            [](const double& f) { std::cout << "double: " << f << std::endl; },
            [](const std::string& s) { std::cout << "string: " << s << std::endl; }
            },
            intFloatString
        );

        intFloatString = 123;

        std::visit(Overload{
            [](const int& i) { std::cout << "int: " << i << std::endl; },
            [](const double& f) { std::cout << "double: " << f << std::endl; },
            [](const std::string& s) { std::cout << "string: " << s << std::endl; }
            },
            intFloatString
        );
    }

    // -------------------------------------------------------------------

    static void test_07() {

        std::variant<int, double, std::string> intFloatString{ "Hello" };

        Overload overloadSet {
            [](const int& i) { std::cout << "int: " << i << std::endl; },
            [](const double& f) { std::cout << "double: " << f << std::endl; },
            [](const std::string& s) { std::cout << "string: " << s << std::endl; }
        };

        std::visit(overloadSet, intFloatString);

        intFloatString = 123;

        std::visit(overloadSet, intFloatString);
    }
}

void main_variant()
{
    using namespace VariantDemo;
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
    test_07();
}

// =====================================================================================
// End-of-File
// =====================================================================================
