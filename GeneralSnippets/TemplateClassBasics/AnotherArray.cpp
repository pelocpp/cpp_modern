// =====================================================================================
// AnotherArray.cpp // Demonstrating Templates Explicit Instantiation Model
// =====================================================================================

module modern_cpp:another_array;

namespace ClassTemplatesBasics {

    template<typename T, size_t DIM>
    AnotherArray<T, DIM>::AnotherArray() : m_data{} {}

    template<typename T, size_t DIM>
    size_t AnotherArray<T, DIM>::size() { return DIM; }

    template<typename T, size_t DIM>
    void AnotherArray<T, DIM>::print() { 
        for (const auto& v : m_data) {
            std::cout << v << ", ";
        }
        std::cout << '\n';
    }

    template<typename T, size_t DIM>
    T& AnotherArray<T, DIM>::operator[](size_t i) { return m_data[i]; }

    template AnotherArray<int, 5>;
    template AnotherArray<double, 5>;
    template AnotherArray<std::string, 5>;
}

// =====================================================================================
// End-of-File
// =====================================================================================
