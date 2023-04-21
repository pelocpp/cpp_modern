// =====================================================================================
// InitializerList.cpp // std::initializer_list
// =====================================================================================

module modern_cpp:initializer_list;

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

    void test_02() {
        std::initializer_list<int> list{ 1, 2, 3, 4, 5 };
        std::vector<int> vec{ list };
    }

    // =================================================================================

    class Point {
    public:
        Point() : Point(0.0, 0.0) {}
        Point(double x, double y) : m_x{ x }, m_y{ y } {}

        double X() const { return m_x; }
        double Y() const { return m_y; }

    private:
        double m_x;
        double m_y;
    };

    // container-like classes
    class Polygon {
    public:
        Polygon(std::initializer_list<Point> elements)
            : m_elements{ elements } {}

    private:
        std::vector<Point> m_elements;
    };

    void test_03() {

        Polygon polygon
        {                          // c'tor Polygon - using brace initialization syntax
            {                      // braces for std::initializer_list<Point> object
                { 45.0, 45.0 },    // c'tor Point - using brace initialization syntax
                { 60.0, 60.0 },    // c'tor Point - using brace initialization syntax
                { 120.0, 120.0 },
                { 180.0, 180.0 }
            }
        };

        // same example - with brace elision
        Polygon polygon2
        {                          // c'tor Polygon - using brace initialization syntax
            { 45.0, 45.0 },        // c'tor Point - using brace initialization syntax
            { 60.0, 60.0 },        // c'tor Point - using brace initialization syntax
            { 120.0, 120.0 },
            { 180.0, 180.0 }
        };
    }

    // =================================================================================

    // container-like class: testing precedence of constructors
    class TinyContainer {
    public:
        TinyContainer() {}
        TinyContainer(int value) {}
        TinyContainer(std::initializer_list<int>) {};
        TinyContainer(const std::vector<int>&) {};
    };

    void test_04() {
        TinyContainer tc0;                                 // TinyContainer::TinyContainer ()
        TinyContainer tc1{ 1, 2, 3, 4 };                   // TinyContainer::TinyContainer (std::initializer_list<int>)
        TinyContainer tc2{ 1 };                            // TinyContainer::TinyContainer (std::initializer_list<int>)
        TinyContainer tc3(1);                              // TinyContainer::TinyContainer (int)
        TinyContainer tc4{ };                              // TinyContainer::TinyContainer ()
        TinyContainer tc5{ std::vector<int> { 1, 2, 3} };  // TinyContainer::TinyContainer (const std::vector<int>&)
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

    void test_05() {
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

    void test_06() {
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
    test_06();
}

// =====================================================================================
// End-of-File
// =====================================================================================
