#include <iostream>

// =====================================================================================
// static_assert
// =====================================================================================

// =====================================================================================
// https://www.geeksforgeeks.org/understanding-static_assert-c-11/
// und
// https://www.grimm-jaud.de/index.php/blog/statisch-geprueft
// =====================================================================================

#include <iostream> 

template < typename T, int Height, int Width >
struct Grid {
    static_assert(Height >= 0, "Height must be positive.");
    static_assert(Width >= 0, "Width must be positive.");
    static_assert(Height + Width > 0, "Height and Width must be greater than 0.");
};

template <class T, int Size>
class MyVector {

    // Compile time assertion to check if the size of the vector is greater than 3 or not.
    // If any vector is declared whose size is less than 4, the assertion will fail

    static_assert(Size > 3, "Vector size is too small!");
    T m_values[Size];
};

int main_static_assert()
{
    static_assert(sizeof(void*) == 4, "Size of Pointer is 32-bits!");
    // static_assert(sizeof(void*) == 8, "Size of Pointer is 64-bits!");

    Grid<int, 10, 5> intGrid;
    Grid<std::string, 3, 4> strGrid;
    // Grid<double, 0, 0> doubleGrid;   // doesn't compile
    Grid<long long, 1, 0> longGrid;

    MyVector<int, 4> four;     // compiles
    // MyVector<short, 2> two; // doesn't compile
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
