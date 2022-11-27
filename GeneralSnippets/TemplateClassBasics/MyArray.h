// =====================================================================================
// MyArray.h // Demonstrating Templates Inclusion model
// =====================================================================================

#pragma once

#include <iostream>
#include <string>

namespace ClassTemplatesBasics {

    template<typename T, size_t DIM>
    class MyArray
    {
    private:
        T m_data[DIM];

    public:
        // full definitions
        MyArray() : m_data{} {}

        size_t size() { return DIM; }

        void print()
        {
            for (const auto& v : m_data) {
                std::cout << v << ", ";
            }
            std::cout << '\n';
        }

        T& operator[](size_t i)
        {
            return m_data[i];
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
