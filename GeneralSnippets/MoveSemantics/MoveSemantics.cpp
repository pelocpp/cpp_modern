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
        BigData(const BigData&);                  // copy c'tor
        BigData& operator= (const BigData&);      // copy assignment

        // move semantics
        //BigData(BigData&&) noexcept;              // move c'tor
        //BigData& operator= (BigData&&) noexcept;  // move assignment

    private:
        // private helper methods
        void cleanup() noexcept;
        void moveFrom(BigData&) noexcept;

    public:
        // getter
        size_t size() const;
        bool isEmpty() const;
    };

    // c'tors and d'tor
    BigData::BigData() {
        // empty buffer
        m_size = 0;
        m_data = nullptr;
    }

    BigData::BigData(size_t size, int preset) {
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
    BigData::BigData(const BigData& data) {

        std::println("copy c'tor");

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

    //    std::println("move c'tor");

    //    m_data = data.m_data;   // shallow copy
    //    m_size = data.m_size;
    //    data.m_data = nullptr;  // reset source object, ownership has been moved
    //    data.m_size = 0;
    //}

    // alternate realisation
    //BigData::BigData(BigData&& data) noexcept {  // move c'tor
    //    moveFrom(data);  // move argument to current object
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

    // alternate realisation
    //BigData& BigData::operator= (BigData&& data) noexcept { // move-assignment
    //    if (this != &data) {
    //        cleanup();         // release left side
    //        moveFrom(data);    // move right side to left side
    //    }
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

    // test methods
    static BigData createHugeData() {
        BigData data(10, 1);
        return data;
    }

    static void test_01_move_semantics() {

        BigData data;
        data = createHugeData();
    }

    static void test_02_demonstrate_move_ctor() {

        std::vector<BigData> vec;
        vec.push_back(BigData(10, 1));
    }

    static void test_03_demonstrate_move_assignment() {

        BigData data;
        data = BigData(10, 1);
    }

    static void test_04_demonstrate_move_assignment() {

        std::vector<BigData> vec;

        BigData someData(10, 1);

        vec.push_back(someData);
        // vs.
        vec.push_back(std::move(someData));
    }

    static void test_05_demonstrate_missing_noexept() {

        std::vector<BigData> vec;
        vec.push_back(BigData(10, 1));
        vec.push_back(BigData(20, 2));
    }
}

void main_move_semantics()
{
    using namespace MoveSemantics;
    test_01_move_semantics();
    test_02_demonstrate_move_ctor();
    test_03_demonstrate_move_assignment();
    test_04_demonstrate_move_assignment();
    test_05_demonstrate_missing_noexept();
}

// =====================================================================================
// End-of-File
// =====================================================================================
