#include <iostream>

// =====================================================================================
// https://www.geeksforgeeks.org/understanding-static_assert-c-11/
// =====================================================================================

#include <iostream> 

template <class T, int Size>
class MyVector {

    // Compile time assertion to check if the size of the vector is greater than 3 or not.
    // If any vector is declared whose size is less than 4, the assertion will fail

    static_assert(Size > 3, "Vector size is too small!");
    T m_values[Size];
};

int main_static_assert()
{
    MyVector<int, 4> four;     // This will work 
    // MyVector<short, 2> two; // This will fail 
    return 0;
}
