// =====================================================================================
// VirtualOverrideFinal.cpp // virtual, override und final
// =====================================================================================

module modern_cpp:virtual_override_final;

namespace VirtualOverrideFinal{

    class Base
    {
    public:
        virtual void func(int);
    };

    class Derived : public Base
    {
    public:
        void func(int) override;
    };

    void Base::func(int n)
    {
        std::cout << "Base::func [" << n << "]" << std::endl;
    }

    void Derived::func(int n)
    {
        std::cout << "Derived::func " << n << "]" << std::endl;
    }

    // =========================================================

    class Driver
    {
    public:
        virtual void send(int) {};
    };

    class KeyboardDriver : public Driver
    {
    public:
        void send(int) final {};  // cannot be overriden anymore
    };

    class MouseDriver final : public Driver // cannot be used as base class anymore
    {
    public:
        void send(int) {};  // cannot be overriden anymore
    };

    //class TrackballDriver : public MouseDriver
    //{};

    //class SpecialKeyboardDriver : public KeyboardDriver
    //{
    //public:
    //    void send(int) final;  // cannot be overriden anymore
    //};

    // =========================================================

    void test_01()
    {
        Base* ptr;
        ptr = new Derived();
        ptr->func(123);
    }
}

void main_virtual_override_final()
{
    using namespace VirtualOverrideFinal;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
