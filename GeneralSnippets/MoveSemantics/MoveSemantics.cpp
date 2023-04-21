// =====================================================================================
// Move Semantics
// =====================================================================================

module modern_cpp:move_semantics;

namespace MoveSemantics {

    class BigData
    {
    private:
        // private member data
        size_t m_size;  // current number of elements
        int* m_data;    // array of elements

    public:
        // c'tors and d'tor
        BigData();
        BigData(size_t, int);
        ~BigData();

        // copy semantics
        BigData(const BigData&); // copy c'tor
        BigData& operator= (const BigData&);  // copy assignment

        // move semantics
        //BigData(BigData&&) noexcept;  // move c'tor
        //BigData& operator= (BigData&&) noexcept; // move assignment

    private:
        // private helper methods
        void cleanup() noexcept;
        void moveFrom(BigData&) noexcept;
        void swap(BigData&, BigData&) noexcept;  // 'swap idiom'

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

    // -------------------------------------------------------------------

    // move semantics
    //BigData::BigData(BigData&& data) noexcept {  // move c'tor

    //    m_data = data.m_data;   // shallow copy
    //    m_size = data.m_size;
    //    data.m_data = nullptr;  // reset source object, ownership has been moved
    //    data.m_size = 0;
    //}

    // first alternate realisation
    //BigData::BigData(BigData&& data) noexcept {  // move c'tor
    //    moveFrom(data);  // move argument to current object
    //}

    // second alternate realisation - based on so called 'swap idiom'
    //BigData::BigData(BigData&& data) noexcept : BigData() {
    //    swap(*this, data);
    //}

    // -------------------------------------------------------------------

    //BigData& BigData::operator= (BigData&& data) noexcept { // move-assignment

    //    if (this != &data) {
    //        delete[] m_data;        // release left side
    //        m_data = data.m_data;   // shallow copy
    //        m_size = data.m_size;
    //        data.m_data = nullptr;  // reset source object, ownership has been moved
    //        data.m_size = 0;
    //    }
    //    return *this;
    //}

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

    // -------------------------------------------------------------------

    // getter
    size_t BigData::size() const {
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

    void test_02_demonstrate_move_ctor() {

        std::vector<BigData> vec;
        vec.push_back(BigData(10, 1));
    }

    void test_03_demonstrate_move_assignment() {

        BigData data;
        data = BigData(10, 1);
    }

    void test_04_demonstrate_move_assignment() {

        std::vector<BigData> vec;

        BigData someData(10, 1);

        vec.push_back(someData);
        // vs.
        vec.push_back(std::move(someData));
    }
}

void main_move_semantics()
{
    using namespace MoveSemantics;
    test_01_move_semantics();
    test_02_demonstrate_move_ctor();
    test_03_demonstrate_move_assignment();
    test_04_demonstrate_move_assignment();
}

// =====================================================================================
// End-of-File
// =====================================================================================
