// =====================================================================================
// Structured Binding
// =====================================================================================

#include <iostream>
#include <vector>
#include <string>

namespace StructuredBinding {

    std::pair<int, int> divide_remainder(int dividend, int divisor) {
        int quotient = dividend / divisor;
        int remainder = dividend % divisor;
        return std::make_pair(quotient, remainder);
    }

    void test_01() {
        const auto result = divide_remainder(16, 3);
        std::cout << "16 / 3 is "
            << result.first << " with a remainder of "
            << result.second << std::endl;
    }

    void test_02() {
        auto [fraction, remainder] = divide_remainder(20, 3);
        std::cout << "20 / 3 is "
            << fraction << " with a remainder of "
            << remainder << std::endl;
    }

    void test_03() {
        int arr[] = { 10, 11, 12 };
        auto [ a, b, c ] = arr;
        std::cout << a << ", " << b << ", " << c << std::endl;
    }

    void test_03_a() {
        int arr[] = { 10, 11, 12 };
        auto& [a, b, c] = arr;
        std::cout << a << ", " << b << ", " << c << std::endl;

        b = 111;

        auto& [d, e, f] = arr;
        std::cout << d << ", " << e << ", " << f << std::endl;
    }

    class Point {
    public:
        int m_x;
        int m_y;
    };

    void test_04() {

        // without structured binding
        Point p1 = { 1, 2 };
        std::cout << "X Coordinate : " << p1.m_x << std::endl;
        std::cout << "Y Coordinate : " << p1.m_y << std::endl;

        // with structured binding
        Point p2 = { 10, 20 };
        auto [x, y] = p2;
        std::cout << "X Coordinate : " << x << std::endl;
        std::cout << "Y Coordinate : " << y << std::endl;
    }

    void test_04_a() {

        Point p = { 10, 20 };
        auto& [x, y] = p;
        std::cout << "X Coordinate : " << x << std::endl;
        std::cout << "Y Coordinate : " << y << std::endl;

        x = 100;
        y = 200;
        std::cout << "X Coordinate : " << p.m_x << std::endl;
        std::cout << "Y Coordinate : " << p.m_y << std::endl;
    }

    class Employee {
    public:
        unsigned int id;
        std::string name;
        std::string role;
        unsigned long phone;
    };

    void test_05() {

        Employee worker { 9987, "Sepp", "Engineer", 987654321 };
        Employee manager { 999, "Hans", "Manager", 123456789 };

        std::vector<Employee> employees { worker, manager };

        for (const auto& [id, name, role, phone] : employees) {
            std::cout
                << "Name: " << name << ", "
                << "Role: " << role << ", "
                << "Phone: " << phone << std::endl;
        }
    }
}

void main_structured_binding()
{
    using namespace StructuredBinding;
    test_01();
    test_02();
    test_03();
    test_03_a();
    test_04();
    test_04_a();
    test_05();
}

// =====================================================================================
// End-of-File
// =====================================================================================
