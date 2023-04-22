// =====================================================================================
// Array.cpp // std::array
// =====================================================================================

module modern_cpp:class_array;


namespace StdArray {

    void test_01() {

        // initialization variants
        [[maybe_unused]] std::array<int, 5> myArray1{};

        [[maybe_unused]] std::array<int, 5> myArray2 = { 1, 2, 3, 4, 5 }; //  initializer list

        [[maybe_unused]] std::array<int, 5> myArray3{ 1, 2, 3, 4, 5 }; // uniform initialization

        // doesn't compile
        // std::array myArray;
        // myArray = { 1, 2, 3, 4, 5 };

        // also doesn't compile
        // int n = 5;
        // std::array <int, n> myArray;

        const int n = 5;
        [[maybe_unused]] std::array<int, n> myArray4{};

        constexpr int m = 5;
        [[maybe_unused]] std::array<int, m> myArray5{};

        // also doesn't compile
        // std::array<int> myArray = { 1, 2, 3, 4, 5 };

        // type is deduced to std::array<int, 5>
        [[maybe_unused]] std::array myArray6{ 9, 7, 5, 3, 1 };

        // type is deduced to std::array<double, 2>
        [[maybe_unused]] std::array myArray7{ 9.7, 7.31 };
    }

    void test_02() {

        std::array<int, 5> myArray;

        myArray = { 0, 1, 2, 3, 4 };       // assignment with initializer list: okay

        myArray = { 9, 8, 7 };             // okay, elements 3 and 4 are set to zero!

        // myArray = { 0, 1, 2, 3, 4, 5 }; // doesn't compile, too many elements in initializer list!
    }

    void test_03() {

        // General Hint:
        // 'at' does bounds checking, is therefore slower - but safer.
        // subscript operator [] does not do any bounds-checking.
        // If an invalid index is provided, unexpected behaviour will happen.

        // use subscript operator to access array
        std::array<int, 5> myArray = { 1, 2, 3, 4, 5 };

        // works like you would expect
        std::cout << myArray[3] << std::endl;

        // undefined behaviour
        // std::cout << myArray[5] << std::endl;

        // valid index
        myArray.at(2) = 33;

        // invalid index
        // myArray.at(9) = 10;

        for (int elem : myArray) {
            std::cout << elem << ' ';
        }
    }

    void printLength(const std::array<int, 5>& myArray)
    {
        std::cout << "Length: " << myArray.size() << std::endl;
    }

    // doesn't compile
    // void printLength(const std::array<int, ??? >& myArray)
    // {
    //     std::cout << "length: " << myArray.size() << std::endl;
    // }

    template<typename T, int LEN>
    void printLength(const std::array<T, LEN>& myArray)
    {
        std::cout << "Length: " << myArray.size() << std::endl;
    }

    // or

    void printLength(const auto& myArray)
    {
        std::cout << "Length: " << myArray.size() << std::endl;
    }

    void test_04() {
        // General Hint:
        // There is no 'array decay' when passing an std::array to a function
        std::array<int, 5> myArray = { 1, 2, 3, 4, 5 };
        printLength(myArray);
    }

    void test_05() {
        std::array<int, 5> myArray = { 1, 2, 3, 4, 5 };
        for (int elem : myArray) {
            std::cout << elem << ' ';
        }

        std::cout << std::boolalpha;
        std::cout << "front: " << myArray.front() << std::endl;
        std::cout << "back: " << myArray.back() << std::endl;
        std::cout << "empty: " << myArray.empty() << std::endl;
        std::cout << "max_size: " << myArray.max_size() << std::endl;

        myArray.fill(9);

        for (int elem : myArray) {
            std::cout << elem << ' ';
        }
    }

    void test_06() {
        // multidimensional std::array
        std::array<std::array<int, 3>, 3> myArray{
            {
                {1, 2, 3}, {4, 5, 6}, {7, 8, 9}
            }
        };

        for (size_t i = 0; i < myArray.size(); i++) {
            for (size_t j = 0; j < myArray[0].size(); j++) {
                std::cout << myArray[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }

    void display(const std::array<std::array<int, 3>, 3>& array)
    {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                std::cout << array[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }

    void test_07() {

        // passing a multidimensional std::array to another function
        std::array<std::array<int, 3>, 3> array{ { {11,12,13}, {14,15,16}, {17,18,19} } };
        display(array);
    }

    class Employee {
    public:
        unsigned m_id{};
        std::string m_name{};
        std::string m_role{};
        unsigned m_phone{};
    };

    void test_08() {

        // arrays of objects
        std::array<Employee, 2> employees{};
        employees[0] = { 9987, "Sepp", "Engineer", 987654321 };
        employees[1] = { 9988, "Hans", "Manager",  123456789 };

        for (const auto& [id, name, role, phone] : employees) {
            std::cout
                << "Id: " << id << ", "
                << "Name: " << name << ", "
                << "Role: " << role << ", "
                << "Phone: " << phone << std::endl;
        }
    }
}

void main_array()
{
    using namespace StdArray;
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
