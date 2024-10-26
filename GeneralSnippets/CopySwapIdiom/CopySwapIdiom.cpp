// =====================================================================================
// Copy-Swap Idiom // CopySwapIdiom.cpp
// =====================================================================================

module modern_cpp:copy_swap_idiom;

namespace NaiveBigData {

    class BigData
    {
    private:
        // private member data
        size_t m_size;  // current number of elements
        int* m_data;    // array of elements

    public:
        // c'tors and d'tor
        BigData();
        BigData(size_t);
        ~BigData();

        // copy semantics
        BigData(const BigData&);                  // copy c'tor
        BigData& operator= (const BigData&);      // copy assignment

        // move semantics
        BigData(BigData&&) noexcept;              // move c'tor
        BigData& operator= (BigData&&) noexcept;  // move assignment

    public:
        // getter
        size_t size() const;
        bool isEmpty() const;

        // output operator
        friend std::ostream& operator<< (std::ostream&, const BigData&);
    };

    // c'tors and d'tor
    BigData::BigData() {
        // empty buffer
        m_size = 0;
        m_data = nullptr;
    }

    BigData::BigData(size_t size) {
        // create buffer
        m_size = size;
        m_data = new int[m_size];

        // fill buffer with zero values
        for (int i = 0; i != m_size; ++i) {
            m_data[i] = 0;
        }
    }

    BigData::~BigData() {
        delete[] m_data;
    }

    // ---------------------------------------------------------------------------------

    // copy constructor
    BigData::BigData(const BigData& other) {

        // allocate buffer
        m_size = other.m_size;
        m_data = new int[m_size];

        // copy buffer
        for (int i = 0; i != m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }

    // copy assignment
    BigData& BigData::operator= (const BigData& other) {

        // prevent self-assignment
        if (this == &other) {
            return *this;
        }

        // delete old buffer
        delete[] m_data;

        // allocate a new buffer
        m_size = other.m_size;
        m_data = new int[m_size];

        // copy buffer
        for (int i = 0; i != m_size; ++i) {
            m_data[i] = other.m_data[i];
        }

        return *this;
    }

    // copy assignment - alternate implementation
    //BigData& BigData::operator= (const BigData& other) {

    //    // prevent self-assignment
    //    if (this == &other) {
    //        return *this;
    //    }

    //    // get the new data ready before we replace the old
    //    size_t tmpNewSize = other.m_size;
    //    int* tmpNewData = nullptr;

    //    if (tmpNewSize > 0) {
    //        tmpNewData = new int[tmpNewSize];
    //    }

    //    // copy buffer
    //    for (int i = 0; i != tmpNewSize; ++i) {
    //        tmpNewData[i] = other.m_data[i];
    //    }

    //    // replace old data with new data - all are non-throwing operations
    //    delete[] m_data;
    //    m_size = tmpNewSize;
    //    m_data = tmpNewData;

    //    return *this;
    //}

    // ---------------------------------------------------------------------------------

    // move constructor
    BigData::BigData(BigData&& data) noexcept {

        m_data = data.m_data;   // shallow copy
        m_size = data.m_size;
        data.m_data = nullptr;  // reset source object, ownership has been moved
        data.m_size = 0;
    }
    
    // move-assignment
    BigData& BigData::operator= (BigData&& data) noexcept {

        if (this != &data) {
            delete[] m_data;        // release left side
            m_data = data.m_data;   // shallow copy
            m_size = data.m_size;
            data.m_data = nullptr;  // reset source object, ownership has been moved
            data.m_size = 0;
        }
        return *this;
    }

    // ---------------------------------------------------------------------------------

    // getter
    size_t BigData::size() const {
        return m_size;
    }

    bool BigData::isEmpty() const {
        return m_size == 0;
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

    // test method
    static void test_01_naive_big_data() {

        BigData data(10);

        BigData copy(data);

        BigData anotherData;

        anotherData = data;
    }
}

// =====================================================================================

namespace IdiomBigDataWithCopySwap {

    class BigData
    {
    private:
        // private member data
        size_t m_size;  // current number of elements
        int* m_data;    // array of elements

    public:
        // c'tors and d'tor
        BigData();
        BigData(size_t);
        ~BigData();

        // copy semantics
        BigData(const BigData&);                  // copy c'tor
        BigData& operator= (BigData other);       // copy assignment

        // move semantics
        BigData(BigData&&) noexcept;              // move c'tor
        BigData& operator= (BigData&&) noexcept;  // move assignment

    private:
        // private helper methods
        void swap(BigData&, BigData&) noexcept;   // 'swap idiom'

    public:
        // getter
        size_t size() const;
        bool isEmpty() const;

        // output operator
        friend std::ostream& operator<< (std::ostream&, const BigData&);
    };

    // c'tors and d'tor
    BigData::BigData() {
        // empty buffer
        m_size = 0;
        m_data = nullptr;
    }

    BigData::BigData(size_t size) {
        // create buffer
        m_size = size;
        m_data = new int[m_size];

        // fill buffer with zero values
        for (int i = 0; i != m_size; ++i) {
            m_data[i] = 0;
        }
    }

    BigData::~BigData() {
        delete[] m_data;
    }

    // -------------------------------------------------------------------

    // copy semantics
    BigData::BigData(const BigData& other) : BigData(other.m_size) {

        // copy buffer
        for (int i = 0; i != m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }

    BigData& BigData::operator= (BigData other) {

        swap(*this, other);
        return *this;
    }

    // -------------------------------------------------------------------

    // move c'tor - based on so called 'swap idiom'
    BigData::BigData(BigData&& other) noexcept : BigData() {
        swap(*this, other);
    }

    // move-assignment - based on so called 'swap idiom'
    BigData& BigData::operator= (BigData&& other) noexcept {
        if (this == &other)
            return *this;

        BigData tmp(std::move(other));
        swap(*this, tmp);

        return *this;
    }

    // -------------------------------------------------------------------

    // getter
    size_t BigData::size() const {
        return m_size;
    }

    bool BigData::isEmpty() const {
        return m_size == 0;
    }

    // -------------------------------------------------------------------

    // private helper methods
    void BigData::swap(BigData& data1, BigData& data2) noexcept {  // 'swap idiom'
        std::swap(data1.m_data, data2.m_data);
        std::swap(data1.m_size, data2.m_size);
    }

    // -------------------------------------------------------------------

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

    // test method
    static void test_02_big_data_copy_swap_idiom() {

        BigData data(10);

        BigData copy(data);

        BigData anotherData;

        anotherData = data;
    }
}

void main_copy_swap_idiom()
{
    using namespace NaiveBigData;
    using namespace IdiomBigDataWithCopySwap;

    test_01_naive_big_data();
    test_02_big_data_copy_swap_idiom();
}

// =====================================================================================
// End-of-File
// =====================================================================================
