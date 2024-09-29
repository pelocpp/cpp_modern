// =====================================================================================
// StructuredBinding.cpp // Structured Binding
// =====================================================================================

module modern_cpp:structured_binding;

namespace StructuredBinding {

    static std::pair<int, int> divide_remainder(int dividend, int divisor)
    {
        int quotient{ dividend / divisor };

        int remainder{ dividend % divisor };

        std::pair<int, int> result{ quotient, remainder };

        return result;
    }

    static void test_01()
    {
        auto result{ divide_remainder(16, 3) };

        std::println("16 / 3 is {} with a remainder of {}",
            result.first, result.second
        );
    }

    static void test_02()
    {
        auto [quotient, remainder] { divide_remainder(20, 3) };

        std::println("16 / 3 is {} with a remainder of {}", quotient, remainder);
    }

    static void test_03()
    {
        int arr[] { 123, 456, 789 };

        auto [a, b, c] { arr };

        std::println("{}, {}, {}", a, b, c);
    }

    static void test_04()
    {
        std::array<int, 3> arr { 123, 456, 789 };

        auto [a, b, c] { arr };

        std::println("{}, {}, {}", a, b, c);
    }

    static void test_05()
    {
        int arr[] { 123, 456, 789 };

        auto& [a, b, c] { arr };
        std::println("{}, {}, {}", a, b, c);

        b = 999;
        std::println("{}, {}, {}", arr[0], arr[1], arr[2]);
    }

    static void test_06()
    {
        std::array<int, 3> arr { 123, 456, 789 };

        auto& [a, b, c] { arr };
        std::println("{}, {}, {}", a, b, c);

        b = 999;
        std::println("{}, {}, {}", arr[0], arr[1], arr[2]);
    }

    struct Point 
    {
        int m_x;
        int m_y;
    };

    static void test_07() {

        // without structured binding
        Point p1 { 1, 2 };

        std::println("X Coordinate : {}", p1.m_x);
        std::println("Y Coordinate : {}", p1.m_y);

        // with structured binding
        Point p2 { 10, 20 };
        auto [x, y] { p2 };

        std::println("X Coordinate : {}", x);
        std::println("Y Coordinate : {}", y);

        // with structured binding and an anonymous object
        auto [x1, y1] { Point{ 100, 200 } };

        std::println("X Coordinate : {}", x1);
        std::println("Y Coordinate : {}", y1);
    }

    static void test_08() {

        Point p { 10, 20 };
        auto& [x, y] { p };

        std::println("X Coordinate : {}", x);
        std::println("Y Coordinate : {}", y);

        x = 100;
        y = 200;

        std::println("X Coordinate : {}", p.m_x);
        std::println("Y Coordinate : {}", p.m_y);
    }

    struct Employee 
    {
        unsigned int id;
        std::string name;
        std::string role;
        unsigned long phone;
    };

    static void test_09() {

        Employee worker { 9987, "Sepp", "Engineer", 987654321 };
        Employee manager { 9999, "Hans", "Manager", 123456789 };

        std::vector<Employee> employees { worker, manager };

        for (const auto& [id, name, role, phone] : employees)
        {
            std::print("Id: {}, ", id);
            std::print("Name: {}, ", name);
            std::print("Role: {}, ", role);
            std::println("Phone: {}", phone);
        }
    }
}

void main_structured_binding()
{
    using namespace StructuredBinding;
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
    test_07();
    test_08();
    test_09();
}

// =====================================================================================
// End-of-File
// =====================================================================================
