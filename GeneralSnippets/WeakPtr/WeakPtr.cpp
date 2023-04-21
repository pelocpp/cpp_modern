// =====================================================================================
// WeakPtr.cpp // std::weak_ptr
// =====================================================================================

module;

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif

#endif  // _DEBUG

module modern_cpp:weak_ptr;

namespace WeakPointer {

    void test_01() {
        std::cout << std::boolalpha;

        std::cout << "Begin-of-program" << std::endl;
        std::weak_ptr<int> weakPtr;

        {
            std::cout << "Begin-of-Scope" << std::endl;

            std::shared_ptr<int> ptr1{ std::make_shared<int>(123) };
            // or
            // std::shared_ptr<int> ptr1{ new int{ 123 } };

            std::cout << "Usage count shared_ptr:     " << ptr1.use_count() << std::endl;
            weakPtr = ptr1;
            std::cout << "Usage count shared_ptr:     " << ptr1.use_count() << std::endl;

            // need shared pointer to access weak pointer
            std::cout << "Is weak ptr expired:        " << weakPtr.expired() << std::endl;

            std::shared_ptr<int> ptr2{ weakPtr.lock() };
            if (ptr2 != nullptr) {

                std::cout << "Usage count shared_ptr:     " << ptr1.use_count() << std::endl;
                std::cout << "Usage count shared_ptr:     " << ptr2.use_count() << std::endl;

                // access weak pointer via shared pointer
                std::cout << "*sharedPtr:                 " << *ptr2 << std::endl;
            }

            std::cout << "Is weak ptr expired:        " << weakPtr.expired() << std::endl;
            std::cout << "End-of-Scope" << std::endl;
        }

        std::cout << "Is weak ptr expired:        " << weakPtr.expired() << std::endl;

        // Note: C++17 initializer syntax: limited variable scope
        if (std::shared_ptr<int> ptr3; (ptr3 = weakPtr.lock()) == nullptr) {
            std::cout << "Don't get the resource!" << std::endl;
        }

        std::cout << "End-of-program" << std::endl;
    }

    // =============================================================================

    class ParentNode;
    class RightNode;
    class LeftNode;

    /**
     * Spoiler Alarm: Don't read this :-)
     * Note: there are 2 cycles!
     * a) Both smart pointers are std::shared_ptr's ==> No d'tor at all will be called
     * b) One smart pointer is a std::shared_ptr    ==> One d'tor is called
     * c) Both smart pointers are std::weak_ptr's   ==> All d'tors are called
     */

    class ParentNode {
    private:
        std::shared_ptr<RightNode> m_rightNode;   // <== shared or weak ?
        std::shared_ptr<LeftNode> m_leftNode;     // <== shared or weak ?

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
        std::shared_ptr<ParentNode> m_parentNode;

    public:
        RightNode(std::shared_ptr<ParentNode> parent)
            : m_parentNode{ parent } {
            std::cout << "c'tor RightNode" << std::endl;
        }

        ~RightNode() {
            std::cout << "d'tor RightNode" << std::endl;
        }
    };

    class LeftNode {
    private:
        std::shared_ptr<ParentNode> m_parentNode;

    public:
        LeftNode(std::shared_ptr<ParentNode> parent)
            : m_parentNode{ parent } {
            std::cout << "c'tor LeftNode" << std::endl;
        }

        ~LeftNode() {
            std::cout << "d'tor LeftNode" << std::endl;
        }
    };

    void test_02()
    {
        std::shared_ptr<ParentNode> parent{ new ParentNode {} };
        std::shared_ptr<RightNode> rightNode{ new RightNode { parent } };
        std::shared_ptr<LeftNode> leftNode{ new LeftNode { parent } };

        parent->setRightNode(rightNode);
        parent->setLeftNode(leftNode);
    }

    void test_03()
    {
        std::shared_ptr<ParentNode> parent{ new ParentNode {} };
        std::shared_ptr<RightNode> rightNode{ new RightNode { parent } };
        std::shared_ptr<LeftNode> leftNode{ new LeftNode { parent } };

        parent->setRightNode(rightNode);
        parent->setLeftNode(leftNode);

        std::cout << "Reference-Count parent: " << parent.use_count() << std::endl;
        std::cout << "Reference-Count rightNode: " << rightNode.use_count() << std::endl;
        std::cout << "Reference-Count leftNode: " << leftNode.use_count() << std::endl;
    }
}

void main_weak_pointer()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    using namespace WeakPointer;
    test_01();
    test_02();
    test_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
