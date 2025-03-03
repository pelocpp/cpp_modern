// =====================================================================================
// Explicit.cpp // Keyword 'explicit'
// =====================================================================================

module modern_cpp:explicit_keyword;

namespace KeywordExplicit {

    class Complex {
    private:
        double m_real;
        double m_imag;

    public:
        // c'tors
        Complex() : Complex {0.0, 0.0}{}

        /* explicit */ Complex(double real) :   // remove or add keyword 'explicit'
            m_real{ real }, m_imag{} {}

        Complex(double real, double imag) :
            m_real{ real }, m_imag{ imag } {}

        // comparison operator
        bool operator == (Complex rhs)
        {
            return (m_real == rhs.m_real && m_imag == rhs.m_imag);
        }
    };
}

void main_explicit_keyword()
{
    using namespace KeywordExplicit;

    // a Complex object
    Complex c{ 3.0, 0.0 };
    
    if (c == 3.0)  // remove or add cast '(Complex)'
    {
        std::cout << "Same objects" << std::endl;
    }
    else
    {
        std::cout << "Not same objects" << std::endl;
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
