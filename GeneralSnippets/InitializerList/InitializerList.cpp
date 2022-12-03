// =====================================================================================
// std::initializer_list
// =====================================================================================

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <array>
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

    void test_01() {
        // testing functions expecting lists in function call
        int sum = myIntAdderFunction({ 1, 3, 5, 7, 9 });
        std::cout << sum << std::endl;
        std::cout << myIntAdderFunction({ 2, 4, 6, 8 }) << std::endl;
    }

    // =================================================================================

    class Position {
    public:
        Position() = default;
        Position(double x, double y) : m_x{ x }, m_y{ y } {}

        double X() const { return m_x; };
        double Y() const { return m_y; };

    private:
        double m_x{ };
        double m_y{ };
    };

    // container-like classes
    class Path {
    public:
        Path(std::initializer_list<Position> elements) 
            : m_elements{ elements } {};

    private:
        std::vector<Position> m_elements;
    };

    class FixedSizePath {
    public:

        FixedSizePath(std::initializer_list<Position> elements) {

            const Position* iter = std::begin(elements);
            size_t numElems = (elements.size() <= 16) ? elements.size() : 16;

            for (size_t i{ }; i != numElems; ++i) {
                m_elements[i] = *iter;
                ++iter;
            }
        }

    private:
        std::array<Position, 6> m_elements;
    };

    void test_02() {

        Path track1 { 
            Position { 45.0, 45.0 },
            Position { 60.0, 60.0 },
            Position { 120.0, 120.0 },
            Position { 180.0, 180.0 }
        };

        FixedSizePath track2{
            Position { 45.0, 45.0 },
            Position { 60.0, 60.0 },
            Position { 120.0, 120.0 },
            Position { 180.0, 180.0 }
        };
    }

    // =================================================================================

    // container-like class: testing precedence of constructors
    class TinyContainer {
    public:
        TinyContainer() {}
        TinyContainer(int value) {}
        TinyContainer(std::initializer_list<int>) {};
        TinyContainer(std::vector<int>) {};
    };

    void test_03() {
        TinyContainer tc1{ 1, 2, 3, 4 };  // TinyContainer::TinyContainer (std::initializer_list<int>)
        TinyContainer tc2{ 1 };           // TinyContainer::TinyContainer (std::initializer_list<int>)
        TinyContainer tc3(1);             // TinyContainer::TinyContainer (int)
        TinyContainer tc4{ };             // TinyContainer::TinyContainer ()
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

    void test_04() {
        MyPeople people({ "Hans", "Sepp", "Franz", "Anton" });
        std::cout << people << std::endl;

        MyPeople noFriends({ });
        std::cout << noFriends << std::endl;
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

    void test_05() {
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
}

void main_initializer_list()
{
    using namespace InitializerList;
    test_01(); 
    test_02();
    test_03();
    test_04();
    test_05();
}

// =====================================================================================
// End-of-File
// =====================================================================================
