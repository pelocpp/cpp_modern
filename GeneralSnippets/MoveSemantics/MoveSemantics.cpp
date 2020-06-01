// =====================================================================================
// Move Semantics
// =====================================================================================

#include <iostream>
#include <vector>
#include <algorithm>

#include "MoveSemantics.h"

namespace MoveSemantics {

    // c'tors and d'tor
    BigData::BigData() {
        // empty buffer
        m_size = 0;
        m_data = nullptr;
    }

    BigData::BigData(size_t size) {
        // empty buffer
        m_size = size;
        m_data = new int[m_size];

        // initialize object
        for (size_t i = 0; i < m_size; i++)
            m_data[i] = 0;

        // TBD: Use std::copy 
        // std::copy(m_data, m_data + m_size, 0);
    }

    BigData::~BigData() {
        delete[] m_data;
    }

    // copy semantics
    BigData::BigData(const BigData& data) {

        // allocate buffer
        m_size = data.m_size;
        m_data = new int[m_size];

        // copy object
        for (size_t i = 0; i < m_size; i++)
            m_data[i] = data.m_data[i];

        // TBD: Use std::copy 
        //std::copy(m_data, m_data + m_size, set.m_data);
    }

    BigData& BigData::operator= (const BigData& data) {

        // prevent self-assignment
        if (this == &data)
            return *this;

        // delete old buffer
        delete[] m_data;

        // allocate a new buffer
        m_size = data.m_size;
        m_data = new int[m_size];

        // copy buffer
         // TBD: Use std::copy 
      //  std::copy(m_data, m_data + m_size, 0);
        for (size_t i = 0; i < m_size; i++)
            m_data[i] = data.m_data[i];

        return *this;
    }

    // move semantics
    BigData::BigData(BigData&& other) noexcept {  // move c'tor
        m_data = other.m_data;   // shallow copy
        m_size = other.m_size;
        other.m_data = nullptr;  // reset source object, ownership has been moved
        other.m_size = 0;
    }

    BigData& BigData::operator= (BigData&& other) noexcept { // move-assignment
        if (this != &other) {
            delete[] m_data;         // release left side
            m_data = other.m_data;   // shallow copy
            m_size = other.m_size;
            other.m_data = nullptr;  // reset source object, ownership has been moved
            other.m_size = 0;
        }
        return *this;
    }

    // getter
    int BigData::size() const {
        return m_size;
    }

    bool BigData::isEmpty() const {
        return m_size == 0;
    }

    // output operator
    std::ostream& operator<< (std::ostream& os, const BigData& data) {

        os << "Size: " << data.m_size << " - Data at " << data.m_data;
        return os;
    }

    BigData createHugeData() {
        BigData data(10);
        return data;
    }

    void test_01_move_semantics() {

        BigData data;
        std::cout << data << std::endl;
        data = createHugeData();
    }

    void test_02_move_semantics() {

        // copy constructing
        BigData data1(10);
        std::cout << data1 << std::endl;
        BigData data2(data1);
        std::cout << data1 << std::endl;
        std::cout << data2 << std::endl;

        // copy assigning
        BigData data3;
        data3 = data1;

        // move constructing
        BigData data10(std::move(BigData(10)));

        // move assigning
        BigData data11;
        data11 = std::move(data1);
    }
}

int main()
// int main_move_semantics()
{
    using namespace MoveSemantics;
    test_01_move_semantics();
    test_02_move_semantics();
    return 1;
}

// =====================================================================================
// End-of-File
// =====================================================================================