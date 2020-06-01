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

    BigData::BigData(size_t size, int preset) {
        // empty buffer
        m_size = size;
        m_data = new int[m_size];

        // initialize object
        std::fill(m_data, m_data + m_size, preset);
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
        std::copy(data.m_data, data.m_data + m_size, m_data);
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
        std::copy(data.m_data, data.m_data + m_size, m_data);

        return *this;
    }

    // move semantics
    BigData::BigData(BigData&& data) noexcept {  // move c'tor
        m_data = data.m_data;   // shallow copy
        m_size = data.m_size;
        data.m_data = nullptr;  // reset source object, ownership has been moved
        data.m_size = 0;
    }

    // first alternate realisation
    //BigData::BigData(BigData&& data) noexcept {  // move c'tor
    //    moveFrom(data);  // move argument to current object
    //}

    // second alternate realisation - based on so called 'swap idiom'
    //BigData::BigData(BigData&& data) noexcept : BigData() {
    //    swap(*this, data);
    //}

    BigData& BigData::operator= (BigData&& data) noexcept { // move-assignment
        if (this != &data) {
            delete[] m_data;        // release left side
            m_data = data.m_data;   // shallow copy
            m_size = data.m_size;
            data.m_data = nullptr;  // reset source object, ownership has been moved
            data.m_size = 0;
        }
        return *this;
    }

    // first alternate realisation
    //BigData& BigData::operator= (BigData&& data) noexcept { // move-assignment
    //    if (this != &data) {
    //        cleanup();         // release left side
    //        moveFrom(data);    // move right side to left side
    //    }
    //    return *this;
    //}

    // second alternate realisation - based on so called 'swap idiom'
    //BigData& BigData::operator= (BigData&& data) noexcept {
    //    if (this == &data)
    //        return *this;

    //    BigData tmp(std::move(data));
    //    swap(*this, tmp);

    //    return *this;
    //}

    // getter
    int BigData::size() const {
        return m_size;
    }

    bool BigData::isEmpty() const {
        return m_size == 0;
    }

    // private helper methods
    void BigData::cleanup() noexcept {
        delete[] m_data;
        m_data = nullptr;
        m_size = 0;
    }

    void BigData::moveFrom(BigData& data) noexcept {
        // shallow copy
        m_data = data.m_data;
        m_size = data.m_size;

        // reset source  object, because ownership has been moved
        data.m_data = nullptr;
        data.m_size = 0;
    }

    void BigData::swap(BigData& data1, BigData& data2) noexcept {  // 'swap idiom'
        std::swap(data1.m_data, data2.m_data);
        std::swap(data1.m_size, data2.m_size);
    }

    // output operator
    std::ostream& operator<< (std::ostream& os, const BigData& data) {
        constexpr bool verbose = false;

        os << "Size: " << data.m_size << " - Data at " << data.m_data;
        if constexpr (verbose) {
            os << std::endl;
            os << "{";
            for (size_t i = 0; i < data.m_size; i++) {
                os << data.m_data[i];
                if (i < data.m_size - 1)
                    os << ',';
            }
            os << "}";
        }
        return os;
    }

    // test methods
    BigData createHugeData() {
        BigData data(10, 1);
        return data;
    }

    void test_01_move_semantics() {

        BigData data;
        std::cout << data << std::endl;
        data = createHugeData();
        std::cout << data << std::endl;
    }

    void test_02_move_semantics() {

        // copy constructing
        BigData data1(10, 1);
        std::cout << data1 << std::endl;
        BigData data2(data1);
        std::cout << data1 << std::endl;
        std::cout << data2 << std::endl;

        // copy assigning
        BigData data3;
        data3 = data1;

        // move constructing
        BigData data10(std::move(BigData(10, 1)));

        // move assigning
        BigData data11;
        data11 = std::move(data1);
    }

    void test_03_move_semantics() {

        BigData data1(5, 1);
        std::cout << data1 << std::endl;

        BigData data2;
        data2 = data1;
        std::cout << data2 << std::endl;

        BigData data3 = data1;
        std::cout << data3 << std::endl;
    }
}

int main_move_semantics()
{
    using namespace MoveSemantics;
    test_01_move_semantics();
    test_02_move_semantics();
    return 1;
}

// =====================================================================================
// End-of-File
// =====================================================================================