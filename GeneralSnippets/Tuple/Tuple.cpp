// =====================================================================================
// Tuple.cpp // std::tuple
// =====================================================================================

module modern_cpp:tuple;

namespace TupleSamples {

    // =======================================================
    // demonstrating simple operations on a std::tuple

    static void test_01()
    {
        // declaring tuple 
        std::tuple <char, int, double> values;

        // assigning values to tuple using std::make_tuple
        values = std::make_tuple('A', 123, 123.456);

        // just in one statement
        std::tuple <char, int, double> moreValues{ 'Z', 987, 987.654 };

        // accessing tuple values using std::get
        {
            auto value1{ std::get<0>(values) };
            auto value2{ std::get<1>(values) };
            auto value3{ std::get<2>(values) };

            std::print("The values of tuple are : ");
            std::println("{} - {} - {}", value1, value2, value3);
        }

        // use std::get to change single values of a tuple 
        std::get<0>(values) = 'M';
        std::get<2>(values) = 135.79;

        // printing tuple values again
        {
            auto value1{ std::get<0>(values) };
            auto value2{ std::get<1>(values) };
            auto value3{ std::get<2>(values) };

            std::print("The modified values of tuple are : ");
            std::println("{} - {} - {}", value1, value2, value3);
        }
    }

    // =======================================================
    // demonstrating use of std::vector with std::tuple elements

    using Row = std::tuple<int, char, double, std::string>;

    static std::string rowToString(const Row& row)
    {
        int n = std::get<0>(row);
        char ch = std::get<1>(row);
        double d = std::get<2>(row);
        std::string s = std::get<3>(row);

        return "Id: " +
            std::to_string(n) + ", " + std::to_string(ch) + ", " +
            std::to_string(d) + ", " + s;
    }

    static void test_02()
    {
        Row row1 = std::make_tuple(10, 'A', 1.11, "Mueller");
        Row row2 = std::make_tuple(11, 'B', 2.22, "Sepp");
        Row row3 = std::make_tuple(12, 'C', 3.33, "Hans");

        std::vector<Row> mySheet;

        mySheet.push_back(row1);
        mySheet.push_back(row2);
        mySheet.push_back(row3);

        for (const Row& row : mySheet) {
            std::println("{}", rowToString(row));
        }
    }

    // =======================================================
    // same example, but using C++ 17 structured binding

    static void test_03()
    {
        Row row1 = std::make_tuple(10, 'A', 1.11, "Mueller");
        Row row2 = std::make_tuple(11, 'B', 2.22, "Sepp");
        Row row3 = std::make_tuple(12, 'C', 3.33, "Hans");

        std::vector<Row> mySheet;

        mySheet.push_back(row1);
        mySheet.push_back(row2);
        mySheet.push_back(row3);

        // C++ 17: structured binding
        const auto& [id, abbr, val, name] = mySheet[0];

        std::println("Id:    {}", id);
        std::println("Abbr:  {}", abbr);
        std::println("Value: {}", val);
        std::println("Name:  {}", name);

        for (const auto& [id, abbr, val, name] : mySheet)
        {
            std::println("Id:    {}", id);
            std::println("Abbr:  {}", abbr);
            std::println("Value: {}", val);
            std::println("Name:  {}", name);
        }
    }

    static void test_04()
    {
        Row row1 = std::make_tuple(91, 'a', 1.11, "Mueller");
        Row row2 = std::make_tuple(92, 'b', 2.22, "Sepp");
        Row row3 = std::make_tuple(93, 'c', 3.33, "Hans");

        std::vector<Row> mySheet;

        mySheet.push_back(row1);
        mySheet.push_back(row2);
        mySheet.push_back(row3);

        // C++ 14: std::tie
        int id{};
        char abbr{};
        double val{};
        std::string name{};

        std::tie(id, abbr, val, name) = mySheet[0];

        // or (note: std::ignore)
        // 
        // std::tie(id, std::ignore, val, name) = mySheet[0];

        std::println("Id:    {}", id);
        std::println("Abbr:  {}", abbr);
        std::println("Value: {}", val);
        std::println("Name:  {}", name);

        for (const auto& row : mySheet)
        {
            std::tie(id, abbr, val, name) = row;

            std::println("Id:    {}", id);
            std::println("Abbr:  {}", abbr);
            std::println("Value: {}", val);
            std::println("Name:  {}", name);
        }
    }

    // =======================================================
    // retrieving number of elements of a std::tuple

    static void test_05()
    {
        // declaring tuple 
        std::tuple <char, int, double> tuple { 'A', 123, 123.456 };

        // retrieve number of elements with std::tuple_size
        std::println("std::tuple size: {}",
            std::tuple_size<decltype(tuple)>::value
        );

        // or
        using MyTuple = std::tuple<char, int, double>;
        std::println("std::tuple size: {}",
            std::tuple_size<MyTuple>::value
        );

        // or
        std::println("std::tuple size: {}", 
            std::tuple_size<std::tuple<char, int, double>>::value
        );
    }
}

void main_tuple()
{
    using namespace TupleSamples;
    test_01();
    test_02();
    test_03();
    test_04();
    test_05(); 
}

// =====================================================================================
// End-of-File
// =====================================================================================
