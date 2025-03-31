// =====================================================================================
// Variant.cpp // std::variant
// =====================================================================================

module modern_cpp:variant;

namespace VariantDemo {

    static void test_01() {

        std::variant<int, double, std::string> v{ 123 };

        // -------------------------------------------------

        {
            size_t index{ v.index() };
            int n{ std::get<int>(v) };  // std::get using type
            std::println("{} - Value: {}", index, n);
        }

        // -------------------------------------------------

        {
            size_t index{ v.index() };
            int n{ std::get<0>(v) };    // std::get using index
            std::println("{} - Value: {}", index, n);
        }

        // -------------------------------------------------
        {
            v = 123.456;                // we're now a double

            size_t index{ v.index() };
            double d{ std::get<double>(v) };
            std::println("{} - Value: {}", index, d);
        }

        // -------------------------------------------------
        {
            v = std::string{ "Hello" }; // we're now a std::string

            size_t index{ v.index() };
            std::string s{ std::get<std::string>(v) };
            std::println("{} - Value: {}", index, s);
        }

        // -------------------------------------------------

        {
            v.emplace<2>("Hello again");    // we're now a std::string again

            size_t index{ v.index() };
            std::string s{ std::get<std::string>(v) };
            std::println("{} - Value: {}", index, s);
        }

        // -------------------------------------------------

        {
            // std::get returns a reference, so you can change the value:

            std::get<std::string>(v) += std::string{ " World" };
            std::println("{} - Value: {}", v.index(), std::get<std::string>(v));
        }
    }

    // -------------------------------------------------------------------

    static void test_02() {

        std::variant<int, double, std::string> v{};

        auto result{ std::holds_alternative<int>(v) };   // true, int is first alternative

        v = 123;
        result = std::holds_alternative<int>(v);         // true

        v = std::string{ "Hello" };
        result = std::holds_alternative<int>(v);         // false, int was overwritten
        
        v = 123.456;
        result = std::holds_alternative<double>(v);      // true, v is now double
    }
        
        
    // -------------------------------------------------------------------

    static void test_03() {

        // accessing a variant

        std::variant<int, double, std::string> v{ std::string{ "Hello" } };

        std::println("{} - Value: {}", v.index(), std::get<std::string>(v));

        try
        {
            double d = std::get<double>(v);
            std::println("double! ", d);
        }
        catch (std::bad_variant_access&)
        {
            std::println("Variant doesn't hold a double at this moment ...");
        }

        v = 123;
        std::println("{} - Value: {}", v.index(), std::get<int>(v));
    }

    // -------------------------------------------------------------------

    static void test_04() {

        std::variant<int, double, std::string> v{ 123 };

        // using a generic visitor (matching all types in the variant)
        auto visitor = [](const auto& elem) {
            std::println("{}", elem);
        };

        std::visit(visitor, v);

        v = 123.456;
        std::visit(visitor, v);

        v = std::string{ "Hello" };
        std::visit(visitor, v);
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

    static void test_05() {

        std::variant<int, double, std::string> var{ 123 };

        Visitor visitor{};

        std::visit(visitor, var);

        var = 123.456;
        std::visit(visitor, var);

        var = std::string{ "Hello" };
        std::visit(visitor, var);
    }

    // -------------------------------------------------------------------

    static void test_06() {

        std::variant<int, double, std::string> v{ 123 };

        // using a generic visitor
        auto visitor = [](const auto& elem) {

            using ElemType = decltype (elem);
            using ElemTypeWithoutRef = std::remove_reference<ElemType>::type;
            using ElemTypeWithoutRefAndConst = std::remove_const_t<ElemTypeWithoutRef>;

            if constexpr (std::is_same<ElemTypeWithoutRefAndConst, int>::value == true)
            {
                std::println("=> int: {}", elem);
            }
            else if constexpr (std::is_same<ElemTypeWithoutRefAndConst, double>::value == true)
            {
                std::println("=> double: {}", elem);
            }
            else if constexpr (std::is_same<ElemTypeWithoutRefAndConst, std::string>::value == true)
            {
                std::println("=> std::string: {}", elem);
                size_t len = elem.length();
                std::println("=> length: {}", len);
            }
            else
            {
                std::println("=> Unknown: {}", elem);
            }
        };

        std::visit(visitor, v);

        v = 123.456;
        std::visit(visitor, v);

        v = std::string{ "Hello" };
        std::visit(visitor, v);
    }

    // -------------------------------------------------------------------

    static void test_07() {

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

    static void test_08() {

        // Inspecting container according to what types are currently present

        using VariantType = std::variant<int, double, std::string>;

        auto vec = std::vector<VariantType>{ 123, 123.456, 456, 654.3221, 789 };

        auto numInts = std::count_if(
            vec.begin(),
            vec.end(),
            [](auto elem) {
                return std::holds_alternative<int>(elem);
            }
        );

        std::println("Found int's: {}", numInts);
    }

    // -------------------------------------------------------------------

    static void test_09() {

        // Inspecting container to find content by both type and value

        using VariantType = std::variant<int, double, std::string>;

        auto vec = std::vector<VariantType>{ 123, 123.456, 456, 654.3221, 789 };

        auto contains = std::any_of(
            vec.begin(),
            vec.end(),
            [](auto v) {
                return std::holds_alternative<int>(v) && std::get<int>(v) == 789;
            }
        );

        std::println("Found 789: {}", contains);
    }
    
    // -------------------------------------------------------------------

    template<class... Ts>
    struct Overload : Ts... { using Ts::operator()...; };
    
    template<class... Ts> Overload(Ts...) -> Overload<Ts...>;

    static void test_10() {

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

    static void test_11() {

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
    test_08();
    test_09();
    test_10();
    test_11();
}

// =====================================================================================
// End-of-File
// =====================================================================================
