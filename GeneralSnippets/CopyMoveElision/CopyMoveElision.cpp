// =====================================================================================
// CopyMoveElision.cpp // Copy/Move Elision
// =====================================================================================

module modern_cpp:copy_move_elision;

namespace CopyMoveElision {

    class Foo
    {
    private:
        int m_value;

    public:
        Foo() : m_value{} {
            std::cout << "c'tor() [" << m_value << "]" << std::endl;
        }

        Foo(int value) : m_value{ value } {
            std::cout << "c'tor (int) [" << m_value << "]" << std::endl;
        }

        // "Rule-of-Three"
        ~Foo() {
            std::cout << "d'tor [" << m_value << "]" << std::endl;
        }

        Foo(const Foo& other) {
            m_value = other.m_value;
            std::cout << "copy-c'tor !!!!!!!!!!! [" << m_value << "]" << std::endl;
        }

        Foo& operator=(const Foo& other) {
            m_value = other.m_value;
            std::cout << "operator=" << std::endl;
            return *this;
        }
    };

    // test method
    static Foo createData() {
        Foo data{ 1 };
        return data;

        // return Foo{ 1 };   // Note: Mandatory copy / move elision
    }

    static void test_copy_elision() {
        Foo data{ createData() };
    }
}

void main_copy_move_elision()
{
    using namespace CopyMoveElision;
    test_copy_elision();
}

// =====================================================================================
// End-of-File
// =====================================================================================