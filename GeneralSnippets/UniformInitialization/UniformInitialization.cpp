// =====================================================================================
// Uniform Initialization
// =====================================================================================

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

namespace UniformInitialization {

    void test_00() {
        // defaut initialization of miscellaneous variables rsp. objects   
        int n{};                 // n equals 0
        float f{};               // f equals 0.0
        double d{};              // d equals 0.0
        std::string s{};         // s equals ""
        std::vector<float> v{};  // v equals an empty vector

        std::cout << "n: " << n << std::endl;
        std::cout << "f: " << f << std::endl;
        std::cout << "d: " << d << std::endl;
        std::cout << "s: " << s << std::endl;
        std::cout << "v.size(): " << v.size() << std::endl;
    }

    void test_01() {

        int n{ 99 };
        std::string s{ "Hans" };

        // dynamically allocated arrays
        int* pi = new int[5]{ 1, 2, 3, 4, 5 };
        double* pd = new double[5]{ 1.0, 2.0, 3.0, 4.0, 5.0 };

        // static allocated array
        int intArray[] { 1, 2, 3, 4, 5 };

        std::cout << n << std::endl;
        std::cout << s << std::endl;
    }

    void test_02() {

        std::vector<int> myArray { 1, 2, 3, 4, 5 };
        std::map<std::string, int> myMap { { "Hans", 1958 }, { "Sepp", 1956 } };

        std::for_each(std::begin(myArray), std::end(myArray), [] (int value) {
            std::cout << value << ", ";
            }
        );
        std::cout << std::endl;

        std::for_each(
            std::begin(myMap), 
            std::end(myMap),
            [] (std::pair<std::string, int> value) {
                std::cout << value.first << " - " << value.second << std::endl;
            }
        );
    }

    class MyDataClass {
    public:
        int m_x;
        double m_y;

        void operator()() {
            std::cout << "x: " << m_x << ", y: " << m_y << std::endl;
        }
    };

    void test_03() {
        // initialization of public attributes of an arbitrary object
        MyDataClass obj1 { 111, 1.23 };
        MyDataClass obj2 { 123, 99.9 };
        obj1();
        obj2();
    }

    class MyAnotherClass {
    private:
        int m_data[5];
        int m_n;

    public:
        MyAnotherClass() : m_data{ 10, 20, 30, 40, 50 }, m_n{ 98 } {}
        MyAnotherClass(int a, int b, int c, int d, int e)
            : m_data{ a, b, c, d, e }, m_n{ 99 } {}

    public:
        void operator()() {
            std::cout << "m_n: " << m_n << std::endl;
            for (size_t i{ 0 }; i < 5; ++i) {
                std::cout << i << ": " << m_data[i] << std::endl;
            }
        }
    };

    void test_04() {
        // delegating parameters of memberwise initialization list
        MyAnotherClass obj1;
        MyAnotherClass obj2{ 11, 12, 13, 14, 15 };
        obj1();
        obj2();
    }

    class MyYetAnotherClass {
    private:
    std::vector<int> m_vec;

    public:
        MyYetAnotherClass() : m_vec{ 100, 200, 300 } {}

    public:
        void operator()() {
            for (size_t i{ 0 }; i < m_vec.size(); ++i) {
                std::cout << i << ": " << m_vec[i] << std::endl;
            }
        }
    };

    void test_05() {
        MyYetAnotherClass obj{};
        obj();
    }
}

int main_uniform_initialization()
{
    using namespace UniformInitialization;

    test_00();
    test_01(); 
    test_02();
    test_03();
    test_04();
    test_05();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
