// =====================================================================================
// Variadic Templates
// =====================================================================================

#include <iostream>
#include <string>
#include <cassert>

// =====================================================================================
// Inhalt:
// - Benutzerdefiniertes Literal mit variadischem Template
// - Traversieren eines binären Baums mit 'folding expression'
// - Benutzerdefiniertes Literal - mit Einzelhochkomma als Trennzeichen
// =====================================================================================

namespace VariadicTemplatesExamples {

    // =====================================================================================
    // =====================================================================================

    /* Benutzerdefiniertes Literal mit variadischem Template
     * hier: Suffix 'b' == binary value of arbitrary length
     */

    template <char C>
    unsigned long long b();

    template <>
    unsigned long long b<'0'>() {
        return 0;
    }

    template <>
    unsigned long long b<'1'>() {
        return 1;
    }

    // verbose version
    //template <char C, char D, char ... REST>
    //unsigned long long b() {
    //    
    //    unsigned long long digit = b<C>();
    //    std::cout << "got " << digit << std::endl;
    //
    //    unsigned long long tmp = digit << (1 + sizeof... (REST));
    //    return tmp | b<D, REST...>();
    //};

    // compact version
    template <char C, char D, char ... REST>
    unsigned long long b() {
    
        return b<C>() << (1 + sizeof... (REST)) | b<D, REST...>();
    };

    template <char... CS>
    unsigned long long operator""  _b() { return b<CS...>(); }

    void test_05() {
        unsigned long long value;
        
        value = 1010_b;
        std::cout << value << std::endl;

        value = 0101_b;
        std::cout << value << std::endl;

        value = 01111111_b;
        std::cout << value << std::endl;

        value = 11111111_b;
        std::cout << value << std::endl;

        value = 100000000_b;
        std::cout << value << std::endl;
    }

    // =====================================================================================
    // =====================================================================================

    /*
     * Traversieren eines binären Baums mit 'folding expression'
     */

    // ========================================================
    // considering at first 'pointer to member of object' 
    // and 'pointer to member of pointer'

    class Example
    {
    public:
        int m_n;

    public:
        Example() : m_n{} {}
        Example(int n) : m_n(n) {}

        friend std::ostream& operator  <<(std::ostream&, const Example&);
    };

    std::ostream& operator  <<(std::ostream& os, const Example& ex) {
        os << "Example: m_n = " << ex.m_n;
        return os;
    }

    void test_06() {

        Example e(1);
        int Example::* pi = &Example::m_n;

        e.m_n = 123;
        std::cout << e << std::endl;

        e.*pi = 456;
        std::cout << e << std::endl;
    }

    void test_07() {

        Example* ep = new Example();
        int Example:: * pi = &Example::m_n;

        ep->m_n = 123;
        std::cout << *ep << std::endl;

        ep->*pi = 456;
        std::cout << *ep << std::endl;
    }

    // define binary tree structure and traverse helpers:
    struct BinaryNode {
    public:
        int m_value;
        BinaryNode* m_left;
        BinaryNode* m_right;
        BinaryNode(int i = 0) : m_value(i), m_left(nullptr), m_right(nullptr) {
        }
    };

    BinaryNode* BinaryNode::* left = &BinaryNode::m_left;   // pointer to class data member
    BinaryNode* BinaryNode::* right = &BinaryNode::m_right; // pointer to class data member

    // oder kürzer

    // auto left = &Node::m_left;
    // auto right = &Node::m_right;

    // traverse tree, using fold expression:
    template<typename T, typename... TP>
    BinaryNode* traverse(T np, TP... paths) {
        return (np ->* ... ->*paths); // np ->* paths1 ->* paths2 ...
    }

    void test_08() {

        // init binary tree structure:
        BinaryNode* root = new BinaryNode{ };
        root->m_left = new BinaryNode{ 1 };
        root->m_left->m_right = new BinaryNode{ 2 };
        root->m_left->m_right->m_left = new BinaryNode{ 3 };

        BinaryNode* node = traverse(root, &BinaryNode::m_left, &BinaryNode::m_right);
        std::cout << node->m_value << std::endl;

        // oder

        node = traverse(root, left, right, left);
        std::cout << node->m_value << std::endl;
    }

    // =====================================================================================
    // =====================================================================================

    template<int B>
    class MathHelper {
    public:
        template<typename T>
        static T power(T exp) {
            static_assert(std::is_integral<T>::value, "Integral required");
            return (exp == 0) ? 1 : B * power(exp - 1);
        }
    };

    class BinarySuffixHelper {
    private:
        static int m_exp;

        template<typename T>
        static unsigned long long bin(T ch) {
            return 0;
        }

    public:
        // non function template definition (end of recursion)
        static unsigned long long bin(char ch)
        {
            // right-most char cannot be a quotation mark
            assert(ch == '0' || ch == '1');
            return (unsigned long long) (ch) - '0';
        }

        // function template definition
        template <typename T, typename ... REST>
        static unsigned long long bin(T ch, REST... rest)
        {
            m_exp = 0;  // reset exponent

            assert(ch == '0' || ch == '1' || ch == '\'');
            unsigned long long digit = (ch == '1') ? 1 : (ch == '0') ? 0 : -1;  // -1 must be '\''

            unsigned long long begin = bin(rest...);

            if (ch == '\'')   // cannot compare unsigned long long with -1
            {
                return begin;  // ignore single quotation mark
            }
            else {
                m_exp++;
                return begin + digit * MathHelper<2>::power<int>(m_exp);
            }
        }
    };

    int BinarySuffixHelper::m_exp = 0;

    template <char... CS>
    unsigned long long operator"" _bin() {
        return BinarySuffixHelper::bin(CS...);
    }

    void test_09() {

        unsigned long long value;

        value = 0011_bin;
        std::cout << value << std::endl;

        value = 1100_bin;
        std::cout << value << std::endl;

        value = 1_bin;
        std::cout << value << std::endl;
        value = 11_bin;
        std::cout << value << std::endl;
        value = 111_bin;
        std::cout << value << std::endl;
        value = 1111_bin;
        std::cout << value << std::endl;
        value = 11111_bin;
        std::cout << value << std::endl;
        value = 111111_bin;
        std::cout << value << std::endl;
        value = 1111111_bin;
        std::cout << value << std::endl;
        value = 11111111_bin;
        std::cout << value << std::endl;
        value = 111111111_bin;
        std::cout << value << std::endl;
        value = 1111111111_bin;
        std::cout << value << std::endl;
        value = 10000000000_bin;
        std::cout << value << std::endl;
    }
}

// =====================================================================================
// =====================================================================================

void main_variadic_templates_examples()
{
    using namespace VariadicTemplatesExamples;

    // user defined literal
    test_05();

    // binary tree traversal with 'folding expression'
    test_06();
    test_07();

    // binary tree traversal with 'folding expression'
    test_08();

    // user defined literal - including quotation marks
    test_09();
}

// =====================================================================================
// End-of-File
// =====================================================================================
