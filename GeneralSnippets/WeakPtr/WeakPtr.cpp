// =====================================================================================
// Weak Pointer
// =====================================================================================

#include <iostream>
#include <memory>

namespace WeakPointer {

    void test_01() {
        std::cout << std::boolalpha;

        std::cout << "Begin-of-program" << std::endl;
        std::weak_ptr<int> weakPtr;

        {
            std::cout << "Begin-of-Scope" << std::endl;

            std::shared_ptr<int> ptr1 = std::make_shared<int>();

            std::cout << "Usage count shared_ptr: " << ptr1.use_count() << std::endl;
            weakPtr = ptr1;
            std::cout << "Usage count shared_ptr: " << ptr1.use_count() << std::endl;

            // need shared pointer to access weak pointer
            std::cout << "Is weak ptr expired: " << weakPtr.expired() << std::endl;
            std::shared_ptr<int> ptr2 = weakPtr.lock();
            std::cout << "Usage count shared_ptr: " << ptr1.use_count() << std::endl;
            std::cout << "Usage count shared_ptr: " << ptr2.use_count() << std::endl;

            // access weak pointer via shared pointer
            std::cout << "*sharedPtr: " << *ptr2 << std::endl;

            std::cout << "Is weak ptr expired: " << weakPtr.expired() << std::endl;
            std::cout << "End-of-Scope" << std::endl;
        }

        std::cout << "Is weak ptr expired: " << weakPtr.expired() << std::endl;

        // Notw: C++17 initializer syntax: limited variable scope
        if (std::shared_ptr<int> ptr3; (ptr3 = weakPtr.lock()) == nullptr) {
            std::cout << "Don't get the resource!" << std::endl;
        }

        std::cout << "End-of-program" << std::endl;
    }

    // =============================================================================

    class ParentNode;
    class RightNode;
    class LeftNode;

    class ParentNode {
    private:
        std::shared_ptr<const RightNode> m_rightNode;  // <== shared or weak ?
        std::weak_ptr<const LeftNode> m_leftNode;

    public:
        ParentNode() {
            std::cout << "c'tor ParentNode" << std::endl;
        }
        ~ParentNode() {
            std::cout << "d'tor ParentNode" << std::endl;
        }
        void setRightNode(const std::shared_ptr<RightNode> right) {
            m_rightNode = right;
        }
        void setLeftNode(const std::shared_ptr<LeftNode> left) {
            m_leftNode = left;
        }
    };

    class RightNode {
    private:
        std::shared_ptr<const ParentNode> m_parentNode;
    public:
        RightNode(std::shared_ptr<ParentNode> parent)
            : m_parentNode(parent) {
            std::cout << "c'tor RightNode" << std::endl;
        }

        ~RightNode() {
            std::cout << "d'tor RightNode" << std::endl;
        }
    };

    class LeftNode {
    private:
        std::shared_ptr<const ParentNode> m_parentNode;
    public:
        LeftNode(std::shared_ptr<ParentNode> parent)
            : m_parentNode(parent) {
            std::cout << "c'tor LeftNode" << std::endl;
        }

        ~LeftNode() {
            std::cout << "d'tor LeftNode" << std::endl;
        }
    };

    void test_02() {
        std::cout << std::endl;
        {
            std::shared_ptr<ParentNode> parent =
                std::shared_ptr<ParentNode>(new ParentNode);

            std::shared_ptr<RightNode> rightNode =
                std::shared_ptr<RightNode>(new RightNode(parent));

            std::shared_ptr<LeftNode> leftNode =
                std::shared_ptr<LeftNode>(new LeftNode(parent));

            parent->setRightNode(rightNode);
            parent->setLeftNode(leftNode);

            std::cout << std::endl;
        }
    }
}

int main_weak_pointer()
{
    using namespace WeakPointer;
    // test_01();
    test_02();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
