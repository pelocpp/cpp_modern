// =====================================================================================
// StaticAssert.cpp // static_assert keyword
// =====================================================================================

module modern_cpp:static_assert_keyword;

namespace StaticAssertDemo {

    template < typename T, int Height, int Width >
    struct Grid {
        static_assert(Height >= 0, "Height must be positive.");
        static_assert(Width >= 0, "Width must be positive.");
        static_assert(Height + Width > 0, "Height and Width must be greater than 0.");
    };

    template <class T, int Size>
    class MyVector {

        // Compile time assertion to check if the size of the vector
        // is greater than 3 or not. If any vector is declared whose size
        // is less than 4, the assertion will fail

        static_assert(Size > 3, "Vector size is too small!");
        T m_values[Size];
    };
}

void main_static_assert()
{
    using namespace StaticAssertDemo;

    //static_assert(sizeof(void*) == 4, "Size of Pointer is 32-bits!");
    static_assert(sizeof(void*) == 8, "Size of Pointer is 64-bits!");

    [[ maybe_unused]] Grid<int, 10, 5> intGrid;
    [[ maybe_unused]] Grid<std::string, 3, 4> stringGrid;
    // Grid<double, 0, 0> doubleGrid;   // doesn't compile
    [[ maybe_unused]] Grid<long long, 1, 0> longGrid;

    [[ maybe_unused]] MyVector<int, 4> four;     // compiles
    // MyVector<short, 2> two; // doesn't compile
}

// =====================================================================================
// End-of-File
// =====================================================================================
