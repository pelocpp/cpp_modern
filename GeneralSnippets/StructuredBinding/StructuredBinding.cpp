// =====================================================================================
// Structured Binding
// =====================================================================================

#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace C17_News {

    std::pair<int, int> divide_remainder(int dividend, int divisor) {
        int quotient = dividend / divisor;
        int remainder = dividend % divisor;
        return std::make_pair(quotient, remainder);
    }

    void test_01_c17_news() {
        const auto result = divide_remainder(16, 3);
        std::cout << "16 / 3 is "
            << result.first << " with a remainder of "
            << result.second << std::endl;
    }

    void test_02_c17_news() {
        auto [fraction, remainder] = divide_remainder(20, 3);
        std::cout << "20 / 3 is "
            << fraction << " with a remainder of "
            << remainder << std::endl;
    }

    std::tuple<std::string, std::time_t, float>
        stock_info(const std::string& name) {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t t_current = std::chrono::system_clock::to_time_t(now);
        return std::make_tuple<>("INTC", t_current, 49.99F);
    }

    void test_03_c17_news() {
        const auto [name, time, price] = stock_info("INTC");
        std::cout << name << ": "
            << price << " at "
            << std::put_time(std::localtime(&time), "%F %T") << std::endl;
    }

    class Point {
    public:
        int x;
        int y;
    };

    void test_04_c17_news() {

        // without structured binding
        Point p1 = { 1, 2 };

        int x = p1.x;
        int y = p1.y;

        std::cout << "X Coordinate : " << x << std::endl;
        std::cout << "Y Coordinate : " << y << std::endl;

        // with structured binding
        Point p2 = { 10, 20 };

        auto [x_coord, y_coord] = p2;

        std::cout << "X Coordinate : " << x_coord << std::endl;
        std::cout << "Y Coordinate : " << y_coord << std::endl;
    }

    struct employee {
        unsigned id;
        std::string name;
        std::string role;
        unsigned phone;
    };

    void test_05_c17_news() {

        struct employee worker { 9987, "Sepp", "Engineer", 987654321 };
        struct employee manager { 999, "Hans", "Manager", 123456789 };

        std::vector<employee> employees{
            worker,
            manager
        };

        for (const auto& [id, name, role, salary] : employees) {
            std::cout
                << "Name: " << name
                << "Role: " << role
                << "Salary: " << salary << std::endl;
        }
    }
}

int main_structured_binding()
{
    using namespace C17_News;

    test_01_c17_news();
    test_02_c17_news();
    test_03_c17_news();
    test_04_c17_news();
    test_05_c17_news();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
