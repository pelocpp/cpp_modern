// =====================================================================================
// Lambda and Visitor
// =====================================================================================

#include <iostream>
#include <functional>

namespace LambdaAndVisitor {

    class BinaryTreeNode {
    public:
        BinaryTreeNode(
            int value,
            BinaryTreeNode* left,
            BinaryTreeNode* right)
            : m_value(value), m_left(left), m_right(right) {
        }

    private:
        int m_value;
        BinaryTreeNode* m_left;
        BinaryTreeNode* m_right;

    public:
        void accept(std::function<void(BinaryTreeNode & node)> visitor) {
            visitor(*this);
            if (m_left != nullptr) m_left->accept(visitor);
            if (m_right != nullptr) m_right->accept(visitor);
        }

        int value() const { return m_value; }
    };

    void test_01() {

        BinaryTreeNode tree(1,
            new BinaryTreeNode(2,
                new BinaryTreeNode(3, nullptr, nullptr),
                new BinaryTreeNode(4, nullptr, nullptr)),
            new BinaryTreeNode(2, nullptr, nullptr)
        );

        tree.accept([](BinaryTreeNode& visit) {
            std::cout << visit.value() << std::endl;
            }
        );
    }
}

int main_lambd_and_visitor()
{
    using namespace LambdaAndVisitor;
    test_01();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
