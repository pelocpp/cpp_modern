// =====================================================================================
// std::tuple
// =====================================================================================

#include <iostream>
#include <vector>
#include <string>

namespace TupleSamples {

    using Row = std::tuple<int, char, double, std::string>;

    // forward declaration
    std::string rowToString(const Row& row);

    void test_01() {

        Row row1 = std::make_tuple(10, 'A', 1.11, "Mueller");
        Row row2 = std::make_tuple(11, 'B', 2.22, "Sepp");
        Row row3 = std::make_tuple(12, 'C', 3.33, "Hans");

        std::vector<Row> mySheet;

        mySheet.push_back(row1);
        mySheet.push_back(row2);
        mySheet.push_back(row3);

        for (Row row : mySheet) {
            std::cout << rowToString(row) << std::endl;
        }
    }

    std::string rowToString(const Row& row) {

        int n = std::get<0>(row);
        char ch = std::get<1>(row);
        double d = std::get<2>(row);
        std::string s = std::get<3>(row);

        return "Id: " + std::to_string(n) + ", " + std::to_string(ch) + ", " + s;
    }

    void test_02() {

        Row row1 = std::make_tuple(10, 'A', 1.11, "Mueller");
        Row row2 = std::make_tuple(11, 'B', 2.22, "Sepp");
        Row row3 = std::make_tuple(12, 'C', 3.33, "Hans");

        std::vector<Row> mySheet;

        mySheet.push_back(row1);
        mySheet.push_back(row2);
        mySheet.push_back(row3);

        // C++17 structured binding
        auto [id, abbr, val, name] = mySheet[0];

        std::cout
            << "Id:    " << id << std::endl
            << "Abbr:  " << abbr << std::endl
            << "Value: " << val << std::endl
            << "Name:  " << name << std::endl;

        for (const auto& [id, abbr, val, name] : mySheet) {
            std::cout 
                << "Id:    " << id << std::endl
                << "Abbr:  " << abbr << std::endl
                << "Value: " << val << std::endl
                << "Name:  " << name << std::endl;
        }
    }
}

void main_tuples()
{
    using namespace TupleSamples;
    test_01();
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
