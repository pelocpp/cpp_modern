// =====================================================================================
// std::tuple
// =====================================================================================

#include <iostream>
#include <vector>
#include <string>

namespace TupleSamples {

    using ConcreteRow = std::tuple<int, char, double, std::string>;

    std::string rowToString(const ConcreteRow& row) {

        int n = std::get<0>(row);
        char ch = std::get<1>(row);
        double d = std::get<2>(row);
        std::string s = std::get<3>(row);

        return "Id: " + std::to_string(n) + ", " + std::to_string(ch) + ", " + s;
    }

    void test_01_tuples() {

        ConcreteRow row1 = std::make_tuple(10, 'A', 1.11, "Mueller");
        ConcreteRow row2 = std::make_tuple(11, 'B', 2.22, "Sepp");
        ConcreteRow row3 = std::make_tuple(12, 'C', 3.33, "Hans");

        std::vector<ConcreteRow> mySheet;

        mySheet.push_back(row1);
        mySheet.push_back(row2);
        mySheet.push_back(row3);

        for (ConcreteRow row : mySheet) {
            std::cout << rowToString(row) << std::endl;
        }
    }

    void test_02_tuples() {

        ConcreteRow row1 = std::make_tuple(10, 'A', 1.11, "Mueller");
        ConcreteRow row2 = std::make_tuple(11, 'B', 2.22, "Sepp");
        ConcreteRow row3 = std::make_tuple(12, 'C', 3.33, "Hans");

        std::vector<ConcreteRow> mySheet;

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

int main_tuples()
{
    using namespace TupleSamples;
    test_01_tuples();
    test_02_tuples();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
