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

    static void test_01()
    {
        std::println("Begin-of-Program");

        std::weak_ptr<int> weakPtr;

        {
            std::println("Begin-of-Scope");

            std::shared_ptr<int> ptr1{ std::make_shared<int>(123) };
            // or
            // std::shared_ptr<int> ptr1{ new int{ 123 } };

            std::println("Usage count shared_ptr:     {}", ptr1.use_count());

            weakPtr = ptr1;
            
            std::println("Usage count shared_ptr:     {}", ptr1.use_count());
            std::println("Is weak ptr expired:        {}", weakPtr.expired());

            // need shared pointer to access weak pointer
            std::shared_ptr<int> ptr2{ weakPtr.lock() };
            if (ptr2 != nullptr)
            {
                // access weak pointer via shared pointer
                std::println("*sharedPtr:                 {}", *ptr2);

                std::println("Usage count shared_ptr:     {}", ptr1.use_count());
                std::println("Usage count shared_ptr:     {}", ptr2.use_count());
            }

            std::println("Is weak ptr expired:        {}", weakPtr.expired());
            std::println("End-of-Scope");
        }

        std::println("Is weak ptr expired:        {}", weakPtr.expired());

        // trying once more to access weak pointer
        std::shared_ptr<int> ptr3{ weakPtr.lock() };
        if (ptr3 == nullptr) {
            std::println("Don't get the resource!");
        }

        std::println("End-of-Program");
    }

    // =============================================================================

    class ParentNode;
    class RightNode;
    class LeftNode;

    /**
     * Spoiler Alarm: Don't read this :-)
     * Note: there are 2 cycles!
     * a) Both smart pointer are std::shared_ptr's  ==> No d'tor at all will be called
     * b) One smart pointer is a std::shared_ptr    ==> One d'tor is called
     * c) Both smart pointer are std::weak_ptr's    ==> All d'tors are called
     */

    class ParentNode {
    private:
        std::shared_ptr<RightNode> m_rightNode;   // <== shared or weak ?
        std::shared_ptr<LeftNode> m_leftNode;     // <== shared or weak ?

    public:
        ParentNode() {
            std::println("c'tor ParentNode");
        }
        ~ParentNode() {
            std::println("d'tor ParentNode");
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
        explicit RightNode(std::shared_ptr<ParentNode> parent)
            : m_parentNode{ parent } {
            std::println("c'tor RightNode");
        }

        ~RightNode() {
            std::println("d'tor RightNode");
        }
    };

    class LeftNode {
    private:
        std::shared_ptr<ParentNode> m_parentNode;

    public:
        explicit LeftNode(std::shared_ptr<ParentNode> parent)
            : m_parentNode{ parent } {
            std::println("c'tor LeftNode");
        }

        ~LeftNode() {
            std::println("d'tor LeftNode");
        }
    };

    static void test_02()
    {
        std::shared_ptr parent{ std::make_shared<ParentNode>() };
        std::shared_ptr rightNode{ std::make_shared<RightNode>(parent) };
        std::shared_ptr leftNode{ std::make_shared<LeftNode>(parent) };

        parent->setRightNode(rightNode);
        parent->setLeftNode(leftNode);

        // some informations output
        std::println("Reference-Count parent:    {}", parent.use_count());
        std::println("Reference-Count rightNode: {}", rightNode.use_count());
        std::println("Reference-Count leftNode:  {}", leftNode.use_count());
    }
}

void main_weak_pointer()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    using namespace WeakPointer;
    test_01();
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
