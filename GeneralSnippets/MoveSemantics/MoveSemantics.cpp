// =====================================================================================
// Move Semantics
// =====================================================================================

module modern_cpp:move_semantics;

import std;

namespace {

    class BigData
    {
    private:
        // private member data
        std::size_t m_size;    // current number of elements
        int*        m_data;    // array of elements

    public:
        // c'tors and d'tor
        BigData();
        BigData(std::size_t, int);
        ~BigData();

        // copy semantics
        BigData(const BigData&);                     // copy c'tor
        BigData& operator= (const BigData&);         // copy assignment

        // move semantics
        //BigData(BigData&&) noexcept;              // move c'tor
        //BigData& operator= (BigData&&) noexcept;  // move assignment

    private:
        // private helper methods
        void cleanup() noexcept;
        void moveFrom(BigData&) noexcept;

    public:
        // getter
        std::size_t size() const;
        bool isEmpty() const;
    };

    // c'tors and d'tor
    BigData::BigData() {
        // empty buffer
        m_size = 0;
        m_data = nullptr;
    }

    BigData::BigData(std::size_t size, int preset) {
        // create buffer
        m_size = size;
        m_data = new int[m_size];

        // initialize buffer
        std::fill(m_data, m_data + m_size, preset);
    }

    BigData::~BigData() {
        delete[] m_data;
    }

    // copy semantics
    BigData::BigData(const BigData& other) {

        std::println("copy c'tor");

        // allocate buffer
        m_size = other.m_size;
        m_data = new int[m_size];

        // copy object
        std::copy(other.m_data, other.m_data + m_size, m_data);
    }

    BigData& BigData::operator= (const BigData& other) {

        // prevent self-assignment
        if (this == &other)
            return *this;

        // delete old buffer
        delete[] m_data;

        // allocate a new buffer
        m_size = other.m_size;
        m_data = new int[m_size];

        // copy buffer
        std::copy(other.m_data, other.m_data + m_size, m_data);

        return *this;
    }

    // -------------------------------------------------------------------

    // move semantics
    //BigData::BigData(BigData&& other) noexcept {  // move c'tor

    //    std::println("move c'tor");

    //    m_data = other.m_data;   // shallow copy
    //    m_size = other.m_size;
    //    other.m_data = nullptr;  // reset source object, ownership has been moved
    //    other.m_size = 0;
    //}

    // alternate realisation
    //BigData::BigData(BigData&& other) noexcept {  // move c'tor
    //    moveFrom(other);  // move argument to current object
    //}

    // -------------------------------------------------------------------

    //BigData& BigData::operator= (BigData&& other) noexcept { // move-assignment
    //    if (this != &other) {
    //        delete[] m_data;         // release left side
    //        m_data = other.m_data;   // shallow copy
    //        m_size = other.m_size;   //
    //        other.m_data = nullptr;  // reset source object, ownership has been moved
    //        other.m_size = 0;        //
    //    }
    //    return *this;
    //}

    // alternate realisation
    //BigData& BigData::operator= (BigData&& other) noexcept { // move-assignment
    //    if (this != &other) {
    //        cleanup();          // release left side
    //        moveFrom(other);    // move right side to left side
    //    }
    //    return *this;
    //}

    // -------------------------------------------------------------------

    // getter
    std::size_t BigData::size() const {
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

    void BigData::moveFrom(BigData& other) noexcept {
        // shallow copy
        m_data = other.m_data;
        m_size = other.m_size;

        // reset source  object, because ownership has been moved
        other.m_data = nullptr;
        other.m_size = 0;
    }

    // test methods
    BigData createHugeData() {
        BigData data(10, 1);
        return data;
    }

    void move_semantics_01() {

        BigData data;
        data = createHugeData();
    }

    void move_semantics_02_move_ctor() {

        std::vector<BigData> vec;
        vec.push_back(BigData(10, 1));
    }

    void move_semantics_03_move_assignment() {

        BigData data;
        data = BigData(10, 1);
    }

    void move_semantics_04_move_assignment() {

        std::vector<BigData> vec;

        BigData someData(10, 1);

        vec.push_back(someData);
        // vs.
        vec.push_back(std::move(someData));
    }

    void move_semantics_05_missing_noexept() {

        std::vector<BigData> vec;
        vec.push_back(BigData(10, 1));
        vec.push_back(BigData(20, 2));
    }
}

void main_move_semantics()
{
    move_semantics_01();
    move_semantics_02_move_ctor();
    move_semantics_03_move_assignment();
    move_semantics_04_move_assignment();
    move_semantics_05_missing_noexept();
}

// =====================================================================================
// End-of-File
// =====================================================================================
