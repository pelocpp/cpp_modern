// =====================================================================================
// std::initializer_list
// =====================================================================================

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>

namespace InitializerList {

    // function using std::initializer_list
    int myIntAdderFunction(std::initializer_list<int> list)
    {
        int result{};
        std::for_each(
            std::begin(list),
            std::end(list),
            [&result](int value) {
                result += value; 
            });
        return result;
    }

    // delegating std::initializer_list with range based loop
    void printMe(std::initializer_list<int> list) {
        for (const auto& value : list) {
            std::cout << value << " - ";
        }
        std::cout << std::endl;
    }

    // =================================================================================

    // delegating templated std::initializer_list to range based loop
    template<typename T>
    void printMe(std::initializer_list<T> list) {
        for (const auto& value : list) {
            std::cout << value << " - ";
        }
        std::cout << std::endl;
    }

    // delegating templated std::initializer_list to std::for_each with lambda
    template<typename T>
    void printMeToo(std::initializer_list<T> list) {
        std::cout << "Begin of list: ";
        std::for_each(
            std::begin(list),
            std::end(list),
            [](const T& elem) {
                std::cout << elem << " - ";
            });
        std::cout << " End of list." << std::endl;
    }

    // =================================================================================

    // delegating std::initializer_list to std::vector
    class MyPeople {
        friend std::ostream& operator<< (std::ostream&, MyPeople);

    private:
        std::vector<std::string> m_names;

    public:
        MyPeople(std::initializer_list<std::string> names) : m_names{ names } {}

        size_t size() const { return m_names.size(); }
    };

    std::ostream& operator<< (std::ostream& os, MyPeople peoples) {

        os << '[';
        for (int idx{}; const auto & elem : peoples.m_names) {
            os << elem;
            if (idx < peoples.size() - 1) {
                os << " - ";
            }
            ++idx;
        }
        os << ']';

        return os;
    }

    // =================================================================================

    void test_01() {
        // testing functions expecting lists in function call
        int sum = myIntAdderFunction({ 1, 3, 5, 7, 9 });
        std::cout << sum << std::endl;
        std::cout << myIntAdderFunction({ 2, 4, 6, 8 }) << std::endl;
    }

    void test_02() {
        // testing generic functions expecting lists

        printMe({ 11, 12, 13, 14, 15 });

        std::cout << "--------------------------------" << std::endl;

        printMe({ 'a', 'b', 'c' });        // template argument T can be deduced automatically
        printMe<char>({ 'a','b', 'c' });   // template argument T specified explicitly
        printMe<int>({ 'A', 'B', 'C' });
        printMe({ "ABC", "DEF", "GHI" });
        printMe<std::string>({ "ABC", "DEF", "GHI" });
        printMe<std::string>({ std::string("RST"), std::string("UVW"), std::string("XYZ") });

        std::cout << "--------------------------------" << std::endl;

        printMeToo({ 'a', 'b', 'c' });        // template argument T can be deduced automatically
        printMeToo<char>({ 'a','b', 'c' });   // template argument T specified explicitly
        printMeToo<int>({ 'A', 'B', 'C' });
        printMeToo({ "ABC", "DEF", "GHI" });
        printMeToo<std::string>({ "ABC", "DEF", "GHI" });
        printMeToo<std::string>({ std::string("RST"), std::string("UVW"), std::string("XYZ") });
    }

    void test_03() {
        MyPeople people({ "Hans", "Sepp", "Franz", "Anton" });
        std::cout << people << std::endl;

        MyPeople noFriends({ });
        std::cout << noFriends << std::endl;
    }
}

void main_initializer_list()
{
    using namespace InitializerList;
    test_01(); 
    test_02();
    test_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
