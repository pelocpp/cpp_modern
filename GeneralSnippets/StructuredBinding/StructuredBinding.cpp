#include <iostream>
#include <vector>
#include <algorithm>

// =====================================================================================
// https://www.geeksforgeeks.org/structured-binding-c/
// =====================================================================================


// IST NICHT KOMPLETT ÜBERNOMMEN !!!

// Siehe auch

// https://www.grimm-jaud.de/index.php/blog/initialisierung


// creating a structure named Point 
class Point {
public:
    int x;
    int y;
};

void test_structured_binding_01() {

    Point p = { 1, 2 };

    int x_coord = p.x;
    int y_coord = p.y;

    std::cout << "X Coordinate : " << x_coord << std::endl;
    std::cout << "Y Coordinate : " << y_coord << std::endl;
}

void test_structured_binding_02() {

    Point p = { 1,2 };

    // structure binding 
    auto [x_coord, y_coord] = p;

    std::cout << "X Coordinate : " << x_coord << std::endl;
    std::cout << "Y Coordinate : " << y_coord << std::endl;
}

int main_structured_binding()
{
    std::cout << "Begin:" << std::endl;
    // test_structured_binding_01();
    test_structured_binding_02();
    std::cout << "End:" << std::endl;

    return 0;
}
