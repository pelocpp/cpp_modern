// =====================================================================================
// StructuredBinding.cpp // Structured Binding
// =====================================================================================

module modern_cpp:structured_binding;

namespace StructuredBinding {

    std::pair<int, int> divide_remainder(int dividend, int divisor) {
        int quotient = dividend / divisor;
        int remainder = dividend % divisor;
        return std::make_pair(quotient, remainder);
    }

    void test_01() {
        auto result = divide_remainder(16, 3);
        std::cout << "16 / 3 is "
            << result.first << " with a remainder of "
            << result.second << std::endl;
    }

    void test_02() {
        auto [quotient, remainder] = divide_remainder(20, 3);
        std::cout << "20 / 3 is "
            << quotient << " with a remainder of "
            << remainder << std::endl;
    }

    void test_03() {
        int arr[] = { 10, 11, 12 };
        auto [ a, b, c ] = arr;
        std::cout << a << ", " << b << ", " << c << std::endl;
    }

    void test_04() {
        int arr[] = { 10, 11, 12 };
        auto& [a, b, c] = arr;
        std::cout << a << ", " << b << ", " << c << std::endl;

        b = 111;
        std::cout << arr[0] << ", " << arr[1] << ", " << arr[2] << std::endl;
    }

    struct Point 
    {
        int m_x;
        int m_y;
    };

    void test_05() {

        // without structured binding
        Point p1 { 1, 2 };
        std::cout << "X Coordinate : " << p1.m_x << std::endl;
        std::cout << "Y Coordinate : " << p1.m_y << std::endl;

        // with structured binding
        Point p2 { 10, 20 };
        auto [x, y] = p2;
        std::cout << "X Coordinate : " << x << std::endl;
        std::cout << "Y Coordinate : " << y << std::endl;

        // with structured binding and an anonymous object
        auto [x1, y1] = Point{ 100, 200 };
        std::cout << "X Coordinate : " << x1 << std::endl;
        std::cout << "Y Coordinate : " << y1 << std::endl;
    }

    void test_06() {

        Point p { 10, 20 };
        auto& [x, y] = p;
        std::cout << "X Coordinate : " << x << std::endl;
        std::cout << "Y Coordinate : " << y << std::endl;

        x = 100;
        y = 200;
        std::cout << "X Coordinate : " << p.m_x << std::endl;
        std::cout << "Y Coordinate : " << p.m_y << std::endl;
    }

    struct Employee 
    {
        unsigned int id;
        std::string name;
        std::string role;
        unsigned long phone;
    };

    void test_07() {

        Employee worker { 9987, "Sepp", "Engineer", 987654321 };
        Employee manager { 9999, "Hans", "Manager", 123456789 };

        std::vector<Employee> employees { worker, manager };

        for (const auto& [id, name, role, phone] : employees) {
            std::cout
                << "Id: "   << id << ", "
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
    test_04();
    test_05();
    test_06();
    test_07();
}

// =====================================================================================
// End-of-File
// =====================================================================================
