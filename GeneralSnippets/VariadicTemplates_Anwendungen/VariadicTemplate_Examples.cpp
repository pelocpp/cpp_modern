// =====================================================================================
// Variadic Templates
// =====================================================================================

#include <iostream>
#include <string>

/*
 * Logische Operationen für beliebig viele Operanden
 */

namespace VariadicTemplatesExamples {

    // =============================================================
    // Logical And - with variadic template

    template<typename T>
    bool allAnd(T cond) {
        return cond;
    }

    template<typename T, typename... Ts>
    bool allAnd(T cond, Ts... conds) {
        return cond && allAnd(conds...);
    }

    // oder

    //bool allAnd() {
    //    std::cout << "a)" << std::endl;
    //    return true;
    //}
    //
    //template<typename T, typename... Ts>
    //bool allAnd(T cond, Ts... conds) {
    //    return cond && allAnd(conds...);
    //}

    void test_01() {

        bool result = allAnd(true, (1 > 2), true);
        std::cout << std::boolalpha << result << std::endl;

        result = allAnd(true, true, true);
        std::cout << std::boolalpha << result << std::endl;
    }

    // =============================================================
    // Logical Or - with variadic template

    template<typename T>
    bool allOr(T cond) {
        return cond;
    }

    template<typename T, typename... Ts>
    bool allOr(T cond, Ts... conds) {
        return cond || allOr(conds...);
    }

    void test_02() {

        bool result = allOr(false, false, true);
        std::cout << std::boolalpha << result << std::endl;

        result = allAnd(false, false, false, false, false);
        std::cout << std::boolalpha << result << std::endl;
    }

    // =============================================================
    // Logical And - with folding expression

    template<typename ...Args>
    bool anotherAllAnd(Args ...args) {
        return (args && ... && true);  // binary right fold (init == true)
    }

    void test_03() {

        bool result = anotherAllAnd(true, (1 > 2), true);
        std::cout << std::boolalpha << result << std::endl;

        result = anotherAllAnd(true, true, true);
        std::cout << std::boolalpha << result << std::endl;
    }

    // =============================================================
    // Logical Or - with folding expression

    template<typename ...Args>
    bool anotherAllOr(Args ...args) {
        return (args || ...);  // unary right fold
    }

    void test_04() {

        bool result = anotherAllOr(false, false, true);
        std::cout << std::boolalpha << result << std::endl;

        result = anotherAllOr(false, false, false, false, false);
        std::cout << std::boolalpha << result << std::endl;
    }

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
        int(Example:: * pi) = &Example::m_n;

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
    BinaryNode* BinaryNode::* right = &BinaryNode::m_right;  // pointer to class data member

    // oder kürzer

    //auto left = &Node::m_left;
    //auto right = &Node::m_right;

    // traverse tree, using fold expression:
    template<typename T, typename... TP>
    BinaryNode* traverse(T np, TP... paths) {
        return (np ->* ... ->*paths); // np ->* paths1 ->* paths2 ...
    }

    void test_08() {

        // init binary tree structure:
        BinaryNode* root = new BinaryNode{ 0 };
        root->m_left = new BinaryNode{ 1 };
        root->m_left->m_right = new BinaryNode{ 2 };
        root->m_left->m_right->m_left = new BinaryNode{ 3 };

        BinaryNode* node = traverse(root, &BinaryNode::m_left, &BinaryNode::m_right);
        std::cout << node->m_value << std::endl;

        // oder

        node = traverse(root, left, right, left);
        std::cout << node->m_value << std::endl;
    }
}

// =============================================================

int main_variadic_templates_examples()
{
    using namespace VariadicTemplatesExamples;

    // logical operations
    test_01();
    test_02();
    test_03();
    test_04();

    // user defined literal
    test_05();

    // binary tree traversal with 'folding expression'
    test_06();
    test_07();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
