// =====================================================================================
// Array.cpp // std::array // std::to_array // std::span
// =====================================================================================

module modern_cpp:class_array;

namespace StdArray {

    void test_01() {

        // initialization variants
        std::array<int, 5> array1{};
        std::array<int, 5> array2{ 1, 2, 3, 4, 5 };     // uniform initialization
        std::array<int, 5> array3 = { 1, 2, 3, 4, 5 };  // initializer list
    }

    void test_02() {

        /* initialization variants using CTAD: Class Template Argument Deduction
        */

        // type is deduced to std::array<double, 2>
        std::array array1{ 9.7, 7.31 };

        // type is deduced to std::array<int, 5>
        std::array array2{ 1, 2, 3, 4, 5 };

        // BUT, take care !!!!!
        // type is deduced to std::array<const char*, 1>
        // see std::to_array below
        std::array array3{ "Hello C++ 20" };
    }

    void test_03() {

        std::array<int, 5> array;

        array = { 0, 1, 2, 3, 4 };    // Assignment with initializer list: okay

        array = { 9, 8, 7 };          // Okay, elements 3 and 4 are set to zero!

        // array = { 0, 1, 2, 3, 4, 5 }; // doesn't compile, too many elements in initializer list!
    }

    void test_04() {

        // Exception handling:
        // 'at' does bounds checking, is therefore slower - but safer.
        // subscript operator [] does not do any bounds-checking:
        // If an invalid index is provided, unexpected behaviour will happen.

        // use subscript operator to access array, works like you would expect
        std::array<int, 5> array { 1, 2, 3, 4, 5 };
        std::cout << array[3] << std::endl;

        // undefined behaviour
        // std::cout << myArray[5] << std::endl;

        // valid index
        array.at(2) = 33;

        // invalid index
        try {
            array.at(9) = 10;
        }
        catch (std::out_of_range)
        {
            std::cout << "Wrong index used!" << std::endl;
        }

        for (auto elem : array) {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }

    void print(const std::array<int, 5>& array) {
        std::cout << "Length: " << array.size() << std::endl;
    }

    template<typename T, int Length>
    void print(const std::array<T, Length>& array) {
        std::cout << "Length: " << array.size() << std::endl;
    }

    void test_05() {

        std::array<int, 5> array1 = { 1, 2, 3, 4, 5 };
        print(array1);

        std::array<int, 10> array2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        print(array2);
    }

    void test_06() {

        std::array<int, 5> array { 1, 2, 3, 4, 5 };

        for (auto elem : array) {
            std::cout << elem << ' ';
        }

        std::cout << std::boolalpha;
        std::cout << "front: " << array.front() << std::endl;
        std::cout << "back: " << array.back() << std::endl;
        std::cout << "empty: " << array.empty() << std::endl;
        std::cout << "max_size: " << array.max_size() << std::endl;

        array.fill(9);

        for (auto elem : array) {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }

    void test_07() {

        // multidimensional std::array
        std::array<std::array<int, 3>, 3> array {
            {
                { 1, 2, 3 },
                { 4, 5, 6 },
                { 7, 8, 9 }
            }
        };

        for (size_t i{}; i != array.size(); i++) {
            for (size_t j{}; j != array[0].size(); j++) {
                std::cout << array[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }

    void display(const std::array<std::array<int, 3>, 3>& array) {

        for (size_t i{}; i != 3; i++) {
            for (size_t j{}; j != 3; j++) {
                std::cout << array[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }

    void test_08() {

        // passing a multidimensional std::array to another function
        std::array<std::array<int, 3>, 3> array{
            {
                { 11, 12, 13 },
                { 14, 15, 16 },
                { 17, 18, 19 }
            }
        };

        display(array);
    }

    class Employee {
    public:
        size_t m_id;
        std::string m_name;
        std::string m_role;
        size_t m_phone;

        Employee()
            : Employee(0, "", "", 0) {}

        Employee(size_t m_id, const std::string& m_name, const std::string& m_role, size_t m_phone)
            : m_id(m_id), m_name(m_name), m_role(m_role), m_phone(m_phone) {}
    };

    void test_09() {

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

    void test_10() {

        /* C - style array
        */

        std::string cArray[4] = { "the", "quick", "brown", "fox" };

        // copying via operator= isn't supported:
        // array type 'std::string [4]' is not assignable
        std::string other[4];
        // other = cArray;  

        // algorithm std::copy works
        std::copy(
            std::begin(cArray),
            std::end(cArray),
            std::begin(other)
        );

#pragma warning(push)
#pragma warning(disable : 5056)

        // Worse: operator== compiles, but does the "wrong" thing: address comparison!
        bool isEqual = (cArray == other);

#pragma warning(pop)

        // works as expected - need to use a standard algorithm
        isEqual = std::equal(cArray, cArray + 4, other, other + 4);
    }

    void test_11() {

        /* std::array
        */

        std::array<std::string, 4> array{ "the", "quick", "brown", "fox" };

        // copying via operator= is supported ... in linear time
        std::array<std::string, 4> other;
        other = array;

        // operator== compiles and does expected value comparison of all array elements!
        bool isEqual = (array == other);
    }

    // returning a std::array object: works
    auto crossProduct(
        const std::array<int, 3>& a, const std::array<int, 3>& b) -> std::array<int, 3>
    {
        return { {
            a[1] * b[2] - a[2] * b[1],
            a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0],
        } };
    }

    // returning address of local variable or temporary C style array:
    // compiles, but is false

#pragma warning(push)
#pragma warning(disable : 4172)

    auto c_crossProduct(
        const int a[3], const int b[3]) // -> int[3]
    {
        int result[3]{
            a[1] * b[2] - a[2] * b[1],
            a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0],
        };

        return result;
    }

#pragma warning(pop)

    // =====================================================================================

    // std::to_array
    // helper for creating a std::array from a C-array

    void test_20() {

        // type is deduced to std::array<char, 13>
        // Note: see std::array above
        auto array1 = std::to_array("Hello C++ 20");

        // type is deduced to std::array<char, 13>
        // Note: see std::array above
        auto array2 = std::to_array<const char>("Hello C++ 20");

        // type is deduced to std::array<int, 5>
        auto array3 = std::to_array({ 1, 2, 3, 4, 5 });

        // type is deduced to std::array<long, 5>
        auto array4 = std::to_array<long>({ 1, 2, 3, 4, 5 });

        // type is deduced to std::array<int, 5>
        float numbers[]{ 1.5, 2.5, 3.5, 4.5, 5.5 };
        auto array5 = std::to_array(numbers);
    }

    // =====================================================================================

    // std::span

    void printArray(const int* array, size_t size) {

        std::cout << std::format("Number of elements: {}\n", size);

        for (size_t i{}; i != size; ++i) {
            std::cout << std::format("{} ", array[i]);
        }
        std::cout << std::endl;
    }

    void printSpan(std::span<int> values) {

        std::cout << std::format("Number of elements: {}\n", values.size());
        std::cout << std::format("Size of span: {}\n", values.size_bytes());

        for (auto elem : values) {
            std::cout << std::format("{} ", elem);
        }
        std::cout << std::endl;
    }

    void printSpanConst(std::span<const int> values) {

        std::cout << std::format("Number of elements: {}\n", values.size());
        std::cout << std::format("Size of span: {}\n", values.size_bytes());

        for (const auto elem : values) {
            std::cout << std::format("{} ", elem);
        }
        std::cout << std::endl;
    }

    void test_30() {

        int cArray[]{ 1, 2, 3, 4, 5 };
        printSpan(cArray);

        std::array array{ 6, 7, 8, 9, 10 };
        printSpan(array);

        std::vector vector{ 1, 3, 5, 7, 9 };
        printSpan(vector);
    }

    void test_31() {

        int cArray[]{ 1, 2, 3, 4, 5 };
        printArray(cArray, 5);

        std::array array{ 6, 7, 8, 9, 10 };
        printArray(array.data(), array.size());

        std::vector vector{ 1, 3, 5, 7, 9 };
        printArray(vector.data(), vector.size());
    }

    void test_32() {

        int cArray[]{ 1, 2, 3, 4, 5 };
        printSpanConst(cArray);

        std::array array{ 6, 7, 8, 9, 10 };
        printSpanConst(array);

        std::vector vector{ 1, 3, 5, 7, 9 };
        printSpanConst(vector);
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
    test_09();
    test_10();
    test_11();

    test_20();

    test_30();
    test_31();
    test_32();
}

// =====================================================================================
// End-of-File
// =====================================================================================
