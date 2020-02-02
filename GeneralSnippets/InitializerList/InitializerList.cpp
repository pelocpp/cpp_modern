// =====================================================================================
// Initialisierungsliste
// =====================================================================================

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <map>

// =====================================================================================
// "Peter Pohmann" // Kapitel 2.14
// =====================================================================================

#include <algorithm>

namespace InitializerList {

    int myIntAdderFunction(std::initializer_list<int> list) {

        int result{0};
        std::for_each(
            std::begin(list),
            std::end(list),
            [&result](int value) {
                result += value; 
            });
        return result;
    }

    template<typename T>
    void printMe(std::initializer_list<T> list) {
        for (auto value : list) {
            std::cout << value << " - ";
        }
        std::cout << std::endl;
    }

    template<typename T>
    void printMeToo(std::initializer_list<T> list) {
        std::cout << "Begin of list:" << std::endl;
        std::for_each(
            std::begin(list),
            std::end(list),
            [](T elem) {
                std::cout << elem << std::endl;
            });
        std::cout << "End of list." << std::endl;
    }

    class MyPeople {
        friend std::ostream& operator<<(std::ostream&, const MyPeople&);

    public:
        MyPeople(std::initializer_list<std::string> names) : m_names(names) {}

    private:
        std::vector<std::string> m_names;
    };

    std::ostream& operator<<(std::ostream& os, const MyPeople& people) {

        if (people.m_names.size() == 0) {
            return os;
        }

        std::for_each(
            std::begin(people.m_names),
            std::prev(std::end(people.m_names)),
            [](std::string elem) {
                std::cout << elem << " - ";
            });

        // prevent output of " - " after last element :-)
        std::vector<std::string>::const_iterator last = people.m_names.end();
        --last;
        std::cout << *last;

        return os;
    }

    void test_01() {
        // testing functions expecting lists in function call
        int sum = myIntAdderFunction({ 1, 3, 5, 7, 9 });
        std::cout << sum << std::endl;
        std::cout << myIntAdderFunction({ 2, 4, 6, 8 }) << std::endl;
    }

    void test_02() {
        // testing generic functions expecting lists

        printMe({ 'a', 'b', 'c' });        // template argument T can be deduced automatically
        printMe<char>({ 'a','b', 'c' });   // template argument T specified explicitly
        printMe<int>({ 'A', 'B', 'C' });
        printMe({ "ABC", "DEF", "GHI" });
        printMe<std::string>({ "ABC", "DEF", "GHI" });
        printMe<std::string>({ std::string("RST"), std::string("UVW"), std::string("XYZ") });

        printMeToo({ 'a', 'b', 'c' });        // template argument T can be deduced automatically
        printMeToo<char>({ 'a','b', 'c' });   // template argument T specified explicitly
        printMeToo<int>({ 'A', 'B', 'C' });
        printMeToo({ "ABC", "DEF", "GHI" });
        printMeToo<std::string>({ "ABC", "DEF", "GHI" });
        printMeToo<std::string>({ std::string("RST"), std::string("UVW"), std::string("XYZ") });
    }

    void test_03() {
        // testing functions expecting lists as parameter

        MyPeople people({ "Hans", "Sepp", "Franz" });
        std::cout << people << std::endl;

        MyPeople noFriends({ });
        std::cout << noFriends << std::endl;

        MyPeople manyFriends({ 
            "James", "John", "Robert", "Michael", "William",
            "David", "Richard", "Joseph", "Thomas"
            });
        std::cout << manyFriends << std::endl;
    }
}

int main_initializer_list()
{
    using namespace InitializerList;

    test_01(); 
    test_02();
    test_03();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
