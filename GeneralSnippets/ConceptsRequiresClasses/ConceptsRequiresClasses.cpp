// =====================================================================================
// ConceptsRequiresClasses.cpp
// =====================================================================================

module modern_cpp:concepts_requires_classes;

namespace ClassesAndConcepts_01 {

    template <typename T>
    concept Number = std::integral<T> || std::floating_point<T>;

    template <typename T>
        requires Number<T>
    class WrappedNumber
    {
    private:
        T  m_number;

    public:
        explicit WrappedNumber(T number) : m_number{ number } {}

        T getNumber() const { return m_number; }
    };

    static void test_concepts_requires_variant_01()
    {
        WrappedNumber wn1{ 123 };
        std::cout << wn1.getNumber() << std::endl;

        WrappedNumber wn2{ 987.654 };
        std::cout << wn2.getNumber() << std::endl;

        // WrappedNumber<std::string> wn3{ std::string {"ABC"}};  // Error: "the associated constraints are not satisfied"
    }
}

namespace ClassesAndConcepts_02 {

    template <typename T>
    concept Number = std::integral<T> || std::floating_point<T>;

    template <typename T, typename U>
        requires Number<T> && Number<U>
    class WrappedPair
    {
    private:
        T  m_firstNumber;
        U  m_secondNumber;

    public:
        WrappedPair(T firstNumber, U secondNumber)
            : m_firstNumber{ firstNumber }, m_secondNumber{ secondNumber }
        {}

        T getFirstNumber() const { return m_firstNumber; }
        U getSecondNumber() const { return m_secondNumber; }
    };

    static void test_concepts_requires_variant_02()
    {
        WrappedPair wn1{ 123, 123.456 };
        std::cout << wn1.getFirstNumber() << std::endl;
        std::cout << wn1.getSecondNumber() << std::endl;

        WrappedPair wn2{ 123l, 456ll };
        std::cout << wn2.getFirstNumber() << std::endl;
        std::cout << wn2.getSecondNumber() << std::endl;

       // WrappedPair<std::string, int> wn3{ std::string {"ABC"}, 111};   // Error: "the associated constraints are not satisfied"
    }
}

namespace ClassesAndConcepts_03 {

    template <typename T>
    concept Number = std::integral<T> || std::floating_point<T>;

    template <Number T>
    class WrappedNumber
    {
    private:
        T  m_number;

    public:
        explicit WrappedNumber(T number) : m_number{ number } {}

        T getNumber() const { return m_number; }
    };

    static void test_concepts_requires_variant_03()
    {
        WrappedNumber wn1{ 123 };
        std::cout << wn1.getNumber() << std::endl;

        WrappedNumber wn2{ 987.654 };
        std::cout << wn2.getNumber() << std::endl;

       //  WrappedNumber<std::string> wn3{ std::string {"ABC"}};   // Error: "the associated constraints are not satisfied"
    }
}

namespace ClassesAndConcepts_04 {

    template <typename T>
    concept Number = std::integral<T> || std::floating_point<T>;

    template <Number T, Number U>
    class WrappedPair
    {
    private:
        T  m_firstNumber;
        U  m_secondNumber;

    public:
        WrappedPair(T firstNumber, U secondNumber)
            : m_firstNumber{ firstNumber }, m_secondNumber{ secondNumber }
        {}

        T getFirstNumber() const { return m_firstNumber; }
        U getSecondNumber() const { return m_secondNumber; }
    };

    static void test_concepts_requires_variant_04()
    {
        WrappedPair wn1{ 123, 123.456 };
        std::cout << wn1.getFirstNumber() << std::endl;
        std::cout << wn1.getSecondNumber() << std::endl;

        WrappedPair wn2{ 123l, 456ll };
        std::cout << wn2.getFirstNumber() << std::endl;
        std::cout << wn2.getSecondNumber() << std::endl;

        // WrappedPair<std::string, int> wn3{ std::string {"ABC"}, 111};   // Error: "the associated constraints are not satisfied"
    }
}

void main_concepts_requires_classes()
{
    ClassesAndConcepts_01::test_concepts_requires_variant_01();
    ClassesAndConcepts_02::test_concepts_requires_variant_02();
    ClassesAndConcepts_03::test_concepts_requires_variant_03();
    ClassesAndConcepts_04::test_concepts_requires_variant_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
