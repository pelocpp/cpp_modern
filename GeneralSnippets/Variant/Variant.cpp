// =====================================================================================
// Variant.cpp // std::variant
// =====================================================================================

module modern_cpp:variant;

namespace VariantDemo {

    static void test_01() {

        std::variant<int, double, std::string> var{ 123 };

        // -------------------------------------------------

        {
            size_t index{ var.index() };
            int n{ std::get<int>(var) };  // std::get using type
            std::println("{} - Value: {}", index, n);
        }

        // -------------------------------------------------

        {
            size_t index{ var.index() };
            int n{ std::get<0>(var) };    // std::get using index
            std::println("{} - Value: {}", index, n);
        }

        // -------------------------------------------------
        {
            var = std::string{ "Hello" }; // we're now a std::string

            size_t index{ var.index() };
            std::string s{ std::get<std::string>(var) };
            std::println("{} - Value: {}", index, s);
        }

        // -------------------------------------------------
        {
            var = 123.456;                // we're now a double

            size_t index{ var.index() };
            double d{ std::get<double>(var) };
            std::println("{} - Value: {}", index, d);
        }

        // -------------------------------------------------

        {
            var.emplace<2>("Hello again");    // we're now a std::string again

            size_t index{ var.index() };
            std::string s{ std::get<std::string>(var) };
            std::println("{} - Value: {}", index, s);
        }
        // -------------------------------------------------
        {
            // std::get returns a reference, so you can change the value:

            std::get<std::string>(var) += std::string{ " World" };
            std::println("{} - Value: {}", var.index(), std::get<std::string>(var));
        }
    }

    // -------------------------------------------------------------------

    static void test_02() {

        // accessing a variant

        std::variant<int, double, std::string> var{ std::string{ "Hello" } };
        std::println("{} - Value: {}", var.index(), std::get<std::string>(var));

        try
        {
            auto f = std::get<double>(var);
            std::println("double! ", f);
        }
        catch (std::bad_variant_access&)
        {
            std::println("Variant doesn't hold a double at this moment ...");
        }

        var = 123;
        std::println("{} - Value: {}", var.index(), std::get<int>(var));
    }

    // -------------------------------------------------------------------

    static void test_03() {

        std::variant<int, double, std::string> var{ 123 };

        // using a generic visitor (matching all types in the variant)
        auto visitor = [](const auto& elem) {
            std::println("{}", elem);
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
        void operator() (int n) {
            std::println("int: {}", n);
        }

        void operator() (double f) {
            std::println("double: {}", f);
        }

        void operator() (const std::string& s) {
            std::println("const std::string&: {}", s);
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
        std::println("Values:      ");
        for (const auto& var : vec) {
            std::visit([](const auto& n) { std::print("{} ", n); }, var);
        }
        std::println();

        // display each type
        std::println("Types:       ");
        for (const auto& var : vec) {
            std::visit([](const auto& arg) { std::print("{} ", typeid(arg).name()); }, var);
        }
        std::println();

        // get the sum
        std::common_type<int, long, long long, float, double>::type res{};
        std::println("Type of Sum: {}", typeid(res).name());

        for (const auto& var : vec) {
            std::visit([&res](const auto& arg) { res += arg; }, var);
        }
        std::println("Sum:         {}", res);

        // double each value of the vector
        std::println("Values:      ");
        for (auto& var : vec) {
            std::visit([](auto& arg) { arg *= 2; }, var);
            std::visit([](const auto& arg) { std::print("{} ", arg); }, var);
        }
        std::println();
    }

    // -------------------------------------------------------------------

    template<class... Ts>
    struct Overload : Ts... { using Ts::operator()...; };
    
    template<class... Ts> Overload(Ts...) -> Overload<Ts...>;

    static void test_06() {

        std::variant<int, double, std::string> var{ "Hello" };

        std::visit(Overload{
            [](const int& i) { std::println("const int&: {}", i); },
            [](const double& f) { std::println("const double&: {}", f); },
            [](const std::string& s) { std::println("const std::string&: {}", s); }
            },
            var
        );

        var = 123;

        std::visit(Overload{
            [](const int& i) { std::println("const int&: {}", i); },
            [](const double& f) { std::println("const double&: {}", f); },
            [](const std::string& s) { std::println("const std::string&: {}", s); }
            },
            var
        );
    }

    // -------------------------------------------------------------------

    static void test_07() {

        std::variant<int, double, std::string> var{ "Hello" };

        Overload overloadSet {
            [](const int& i) { std::println("const int&: {}", i); },
            [](const double& f) { std::println("const double&: {}", f); },
            [](const std::string& s) { std::println("const std::string&: {}", s); }
        };

        std::visit(overloadSet, var);

        var = 123;

        std::visit(overloadSet, var);
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
