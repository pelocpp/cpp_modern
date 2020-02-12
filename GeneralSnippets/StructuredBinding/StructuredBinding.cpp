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

namespace StructuredBinding {

    std::pair<int, int> divide_remainder(int dividend, int divisor) {
        int quotient = dividend / divisor;
        int remainder = dividend % divisor;
        return std::make_pair(quotient, remainder);
    }

    void test_01_sb() {
        const auto result = divide_remainder(16, 3);
        std::cout << "16 / 3 is "
            << result.first << " with a remainder of "
            << result.second << std::endl;
    }

    void test_02_sb() {
        auto [fraction, remainder] = divide_remainder(20, 3);
        std::cout << "20 / 3 is "
            << fraction << " with a remainder of "
            << remainder << std::endl;
    }

    std::tuple<std::string, std::time_t, float>
    stock_info(const std::string& name) {
        std::chrono::system_clock::time_point now = 
            std::chrono::system_clock::now();
        std::time_t current_time =
            std::chrono::system_clock::to_time_t(now);
        return std::make_tuple<>("INTC", current_time, 49.99F);
    }

    void test_03_sb() {
        const auto [name, time, price] = stock_info("INTC");
        std::cout << name << ": "
            << price << " at "
            << std::put_time(std::localtime(&time), "%F %T") << std::endl;
    }

    class Point {
    public:
        int m_x;
        int m_y;
    };

    void test_04_sb() {

        // without structured binding
        Point p1 = { 1, 2 };
        std::cout << "X Coordinate : " << p1.m_x << std::endl;
        std::cout << "Y Coordinate : " << p1.m_y << std::endl;

        // with structured binding
        Point p2 = { 10, 20 };
        auto [x, y] = p2;
        std::cout << "X Coordinate : " << x << std::endl;
        std::cout << "Y Coordinate : " << x << std::endl;
    }

    class Employee {
    public:
        unsigned id;
        std::string name;
        std::string role;
        unsigned phone;
    };

    void test_05_sb() {

        Employee worker { 9987, "Sepp", "Engineer", 987654321 };
        Employee manager { 999, "Hans", "Manager", 123456789 };

        std::vector<Employee> employees { worker, manager };

        for (const auto& [id, name, role, salary] : employees) {
            std::cout
                << "Name: " << name
                << "Role: " << role
                << "Salary: " << salary << std::endl;
        }
    }
}

int main_structuredbinding()
{
    using namespace StructuredBinding;

    test_01_sb();
    test_02_sb();
    test_03_sb();
    test_04_sb();
    test_05_sb();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
