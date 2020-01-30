// ===============================================================================
// Dummy Class for Testing Purposes
// ===============================================================================

class Dummy
{
private:
    int m_dummy;
public:
    explicit Dummy() : m_dummy (0){
        std::cout << "c'tor Dummy" << std::endl;
    }

    explicit Dummy(int dummy) : m_dummy(dummy) {
        std::cout << "c'tor Dummy" << std::endl;
    }

    // "Big-Three"
    ~Dummy() {
        std::cout << "d'tor Dummy" << std::endl;
    }

    Dummy(const Dummy& other) {
        m_dummy = other.m_dummy;
        std::cout << "Copy-c'tor Dummy" << std::endl;
    };

    Dummy& operator=(Dummy const& other) {
        m_dummy = other.m_dummy;
        std::cout << "Dummy::operator=" << std::endl;
        return *this;
    }

    // Move Semantics / "Big-Five"
    Dummy(Dummy&& other) noexcept {
        m_dummy = other.m_dummy;  // move ownership to target 
        other.m_dummy = 0;        // reset source (symbolic statement)
        std::cout << "Move c'tor Dummy" << std::endl;
    };

    Dummy& operator=(Dummy&& other) noexcept {

        if (this == &other) {
            return *this;
        }

        m_dummy = other.m_dummy;  // move ownership to target 
        other.m_dummy = 0;        // reset source (symbolic statement)
        std::cout << "Move Dummy::operator=" << std::endl;
        return *this;
    }

    // mimimalistic public interface
    int getValue() {
        return m_dummy;
    }

    void saHello() { 
        std::cout << "Hello Dummy" << std::endl;
    }

    // output
    friend std::ostream& operator<< (std::ostream&, const Dummy&);
};

// ===============================================================================
// End-of-File
// ===============================================================================
