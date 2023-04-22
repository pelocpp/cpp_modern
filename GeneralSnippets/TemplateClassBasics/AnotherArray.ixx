// =====================================================================================
// AnotherArray.ixx // Demonstrating Templates Explicit Instantiation Model
// =====================================================================================

export module modern_cpp:another_array;

import std;

namespace ClassTemplatesBasics {

    template<typename T, size_t DIM>
    class AnotherArray
    {
    private:
        T m_data[DIM];

    public:
        AnotherArray();
        size_t size();
        void print();
        T& operator[](size_t i);
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
