// =====================================================================================
// Array.cpp // std::array // std::to_array // std::span
// =====================================================================================

module modern_cpp:class_array;

namespace StdArray {

    // -------------------------------------------------------------------
    // initialization

    static void test_01() {

        // initialization variants
        [[maybe_unused]] std::array<int, 5> array1;

        std::array<int, 5> array2{};

        std::array<int, 5> array3{ 1, 2, 3, 4, 5 };     // brace initialization

        std::array<int, 5> array4 = { 1, 2, 3, 4, 5 };  // initializer list

        std::array array5 = { 1, 2, 3, 4, 5 };          // CTAD - type is deduced to std::array<int, 5>
    }

    // -------------------------------------------------------------------
    // assignment

    static void test_02() {

        std::array<int, 5> array;

        array = { 1, 2, 3, 4, 5 };    // assignment with initializer list: okay

        array = { 9, 8, 7 };          // Okay, elements 3 and 4 are set to zero!

        // array = { 0, 1, 2, 3, 4, 5 }; // doesn't compile, too many elements in initializer list!
    }

    // -------------------------------------------------------------------
    // exception handling

    static void test_03() {

        // Exception handling:
        // 'at' does bounds checking, is therefore slower - but safer.
        // subscript operator [] does not do any bounds-checking:
        // If an invalid index is provided, unexpected behaviour will happen.

        // use subscript operator to access array, works like you would expect
        std::array<int, 5> array { 1, 2, 3, 4, 5 };
        std::println("{}", array[3]);

        // undefined behaviour
        //std::println("{}", array[5]);

        // valid index
        array.at(2) = 33;

        // invalid index
        try {
            array.at(9) = 10;
        }
        catch (const std::out_of_range&)
        {
            std::println("Wrong index used!");
        }

        for (auto elem : array) {
            std::print("{} ", elem);
        }
        std::println();
    }

    // -------------------------------------------------------------------
    // passing std::array as parameter

    static void print(const std::array<int, 5>& array) {
        std::println("Length: {}", array.size());
    }

    template<typename T, int Length>
    void print(const std::array<T, Length>& array) {
        std::println("Length: {}", array.size());
    }

    static void test_04() {

        std::array<int, 5> array1 = { 1, 2, 3, 4, 5 };
        print(array1);

        std::array<int, 10> array2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        print(array2);
    }

    // -------------------------------------------------------------------
    // miscellaneous

    static void test_05() {

        std::array<int, 5> array { 1, 2, 3, 4, 5 };

        for (auto elem : array) {
            std::println("{}", elem);
        }

        std::println("front:{}", array.front());
        std::println("back: {}", array.back());

        array.fill(123);
        for (auto elem : array) {
            std::println("{}", elem);
        }
        std::println();
    }

    // -------------------------------------------------------------------
    // multidimensional arrays

    static void test_06() {

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
                std::print("{} ", array[i][j]);
            }
            std::println();
        }
    }

    static void display(const std::array<std::array<int, 3>, 3>& array) {

        for (size_t i{}; i != 3; i++) {
            for (size_t j{}; j != 3; j++) {
                std::print("{} ", array[i][j]);
            }
            std::println();
        }
    }

    static void test_07() {

        // passing a multidimensional std::array to another function
        std::array<std::array<int, 3>, 3> array
        {
            {
                { 11, 12, 13 },
                { 14, 15, 16 },
                { 17, 18, 19 }
            }
        };

        display(array);
    }

    // -------------------------------------------------------------------
    // arrays of objects

    class Employee {
    public:
        size_t      m_id;
        std::string m_name;
        std::string m_role;
        size_t      m_phone;

        Employee() : Employee(0, "", "", 0) {}

        Employee(size_t m_id, const std::string& m_name, const std::string& m_role, size_t m_phone)
            : m_id{ m_id }, m_name{ m_name }, m_role{ m_role }, m_phone{ m_phone }
        {}
    };

    static void test_08() {

        // arrays of objects
        std::array<Employee, 2> employees
        {
            Employee{ 12345, "Sepp", "Engineer", 987654321 },
            Employee{ 54321, "Hans", "Manager", 123456789 }
        };

        for (const auto& [id, name, role, phone] : employees)
        {
            std::println("Id:    {}", id);
            std::println("Name:  {}", name);
            std::println("Role:  {}", role);
            std::println("Phone: {}", phone);
        }
    }

    // -------------------------------------------------------------------
    // assignment - comparison C-style array with std::string

    static void test_09() {

        /* C-style array
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
        isEqual = std::equal(
            std::begin(cArray),
            std::end(cArray),
            std::begin(other),
            std::end(other)
        );
    }

    static void test_10() {

        /* std::array
        */

        std::array<std::string, 4> array{ "the", "quick", "brown", "fox" };

        // copying via operator= is supported ... in linear time
        std::array<std::string, 4> other;
        other = array;

        // operator== compiles and does expected value comparison of all array elements!
        bool isEqual = (array == other);
    }

    // -------------------------------------------------------------------
    // returning an array - comparison C-style array with std::string

    // returning a C-style

#pragma warning(push)
#pragma warning(disable : 4172)

    // returning address of local variable or temporary C style array:
    // compiles, but is false

    static int* scalarProduct(int scalar, const int vec[3])
    {
        int result[3] = { scalar * vec[0], scalar * vec[1], scalar * vec[2] };
        return result;
    }

#pragma warning(pop)

    // returning an std::array
    static std::array<int, 3> scalarProduct(int scalar, const std::array<int, 3>& vec)
    {
        std::array result = { scalar * vec[0], scalar * vec[1], scalar * vec[2] };
        return result;
    }

    static void test_11()
    {
        // testing scalarProduct with C-style array
        int vector[3] { 1, 2, 3 };
        int* result{ scalarProduct(3, vector) };
        std::println("Result: {},{},{}", result[0], result[1], result[2]);
        // results can be correct, but that is absolutely coincidental

        // testing scalarProduct with std::array
        std::array vector2 { 1, 2, 3 };
        std::array result2{ scalarProduct(3, vector2) };
        std::println("Result: {},{},{}", result2[0], result2[1], result2[2]);
    }

    // -------------------------------------------------------------------
    // std::to_array
    // helper for creating a std::array from a C-array

    static void test_20() {

        // type is deduced to std::array<char, 13>
        // Note: see std::array above
        auto array1{ std::to_array("Hello C++ 20") };

        // type is deduced to std::array<char, 13>
        // Note: see std::array above
        auto array2{ std::to_array<const char>("Hello C++ 20") };

        // type is deduced to std::array<int, 5>
        auto array3{ std::to_array({ 1, 2, 3, 4, 5 }) };

        // type is deduced to std::array<long, 5>
        auto array4{ std::to_array<long>({ 1, 2, 3, 4, 5 }) };

        // type is deduced to std::array<int, 5>
        int intNumbers[] { 1, 2, 3, 4, 5 };
        auto array5{ std::to_array(intNumbers) };
    }

    // -------------------------------------------------------------------
    // std::span

    // demonstrating printArray with pointer parameter
    static void printArray(const int* array, size_t size) {

        std::println("Number of elements: {}", size);

        // note: range-based loop doesn't work for pointers
        for (size_t i{}; i != size; ++i) {
            std::println("{} ", array[i]);
        }
        std::println();
    }

    static void test_30() {

        int carr[]{ 1, 2, 3, 4, 5 };
        printArray(carr, 5);

        std::array arr{ 6, 7, 8, 9, 10 };
        printArray(arr.data(), arr.size());

        std::vector vec{ 1, 3, 5, 7, 9 };
        printArray(vec.data(), vec.size());
    }

    // --------------------------------------------------------------------
    // demonstrating printArray with std::span parameter

    static void printArray(std::span<int> values) {

        std::println("Number of elements: {}", values.size());
        std::println("Size of span:       {}", values.size_bytes());

        // range-based loop works now
        for (auto elem : values) {
            std::println("{}", elem);
        }
        std::println();
    }

    static void test_31() {

        //int carr[]{ 1, 2, 3, 4, 5 };
        //printArray(carr);

        //std::array arr{ 6, 7, 8, 9, 10 };
        //printArray(arr);

        //std::vector<int> vec{ 1, 3, 5, 7, 9 };
        //printArray(vec);

        int carr[]{ 1, 2, 3, 4, 5 };
        printArray(std::span{ carr });

        std::array arr{ 6, 7, 8, 9, 10 };
        printArray(std::span{ arr });

        std::vector vec{ 1, 3, 5, 7, 9 };
        printArray(std::span{ vec });
    }

    // --------------------------------------------------------------------
    // demonstrating std::span with const type

    static void printArrayConst(std::span<const int> values) {

        std::println("Number of elements: {}", values.size());
        std::println("Size of span:       {}", values.size_bytes());

        for (const auto elem : values) {
            std::println("{}", elem);
        }
        std::println();
    }

    static void test_32() {

        int carr[]{ 1, 2, 3, 4, 5 };
        printArrayConst(carr);

        std::array arr{ 6, 7, 8, 9, 10 };
        printArrayConst(arr);

        std::vector vec{ 1, 3, 5, 7, 9 };
        printArrayConst(vec);
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
