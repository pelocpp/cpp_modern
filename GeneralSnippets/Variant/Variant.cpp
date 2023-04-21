// =====================================================================================
// Variant.cpp // std::variant
// =====================================================================================

module modern_cpp:variant;

namespace VariantDemo {

    void test_01() {

        std::variant<int, float, std::string> var{ 10.5f };

        std::cout
            << var.index()
            << ", value "
            << std::get<float>(var)
            << std::endl;

        var = std::string{ "Hello" }; // we're now a string

        std::cout
            << var.index()
            << ", value "
            << std::get<std::string>(var)
            << std::endl;

        var = 10; // we're now an int

        std::cout
            << var.index()
            << ", value "
            << std::get<int>(var)
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

        var = 10.1f;
        if (auto pFloat = std::get_if<float>(&var); pFloat)
            *pFloat *= 2.0f;

        std::cout
            << var.index()
            << ", value "
            << std::get<float>(var)
            << std::endl;
    }

    // -------------------------------------------------------------------

    void test_02() {

        // accessing a variant

        std::variant<int, float, std::string> var{ std::string{ "Hello" } };

        std::cout
            << var.index()
            << ", value "
            << std::get<std::string>(var)
            << std::endl;

        try
        {
            auto f = std::get<float>(var);
            std::cout << "float! " << f << "\n";
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

        if (auto intPtr = std::get_if<0>(&var))
            std::cout << "int! => " << *intPtr << std::endl;
    }

    // -------------------------------------------------------------------

    void test_03() {

        std::variant<int, float, std::string> var{ 3.5f };

        // using a generic visitor (matching all types in the variant)
        auto visitor = [](auto const& elem) {
            std::cout << elem << std::endl;
        };

        std::visit(visitor, var);

        var = 10;
        std::visit(visitor, var);

        var = std::string{ "Hello" };
        std::visit(visitor, var);
    }

    // -------------------------------------------------------------------

    template<typename T>
    void visitorFunction (const T& elem) {
        std::cout << elem << std::endl;
    }

    void test_04() {

        std::variant<int, float, std::string> var{ 3.5f };

        // Doesn't work:
        // std::visit requires an object,
        // and template functions aren't objects of functions:
        // std::visit(visitorFunction<float>, var);
    }

    // -------------------------------------------------------------------

    class Visitor
    {
    public:
        Visitor() = default;

        void operator() (int n) {
            std::cout << "int: " << n << std::endl;
        }

        void operator() (float f) {
            std::cout << "float: " << f << std::endl;
        }

        void operator() (std::string s) {
            std::cout << "std::string: " << s << std::endl;
        }
    };

    void test_05() {

        std::variant<int, float, std::string> var{ 3.5f };

        Visitor visitor{};

        std::visit(visitor, var);
        
        var = 10;
        std::visit(visitor, var);
    }

    // -------------------------------------------------------------------

    void test_06() {

        std::vector<std::variant<int, long, long long, float, double>>
            vec = { 100, 200l, 300ll, 400.5f, 500.5 };

        // display each value
        std::cout << "Values:      ";
        for (const auto& var : vec) {
            std::visit([](const auto& n) { std::cout << n << " "; }, var);
        }
        std::cout << std::endl;

        // display each type
        // C++ modules & typeid don't work
        //std::cout << "Types:       ";
        //for (const auto& var : vec) {
        //    std::visit([](const auto& arg) { std::cout << typeid(arg).name() << " "; }, var);
        //}
        //std::cout << std::endl;

        // get the sum
        // C++ modules & typeid don't work
        std::common_type<int, long, long long, float, double>::type res{};
        //std::cout << "Type of Sum: " << typeid(res).name() << std::endl;

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

    void test_07() {

        std::variant<int, float, std::string> intFloatString{ "Hello" };

        std::visit(Overload{
            [](const int& i) { std::cout << "int: " << i << std::endl; },
            [](const float& f) { std::cout << "float: " << f << std::endl; },
            [](const std::string& s) { std::cout << "string: " << s << std::endl; }
            },
            intFloatString
        );

        intFloatString = 123;

        std::visit(Overload{
            [](const int& i) { std::cout << "int: " << i << std::endl; },
            [](const float& f) { std::cout << "float: " << f << std::endl; },
            [](const std::string& s) { std::cout << "string: " << s << std::endl; }
            },
            intFloatString
        );
    }

    // -------------------------------------------------------------------

    void test_08() {

        std::variant<int, float, std::string> intFloatString{ "Hello" };

        Overload overloadSet {
            [](const int& i) { std::cout << "int: " << i << std::endl; },
            [](const float& f) { std::cout << "float: " << f << std::endl; },
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
    test_08();
}

// =====================================================================================
// End-of-File
// =====================================================================================
