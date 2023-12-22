// =====================================================================================
// CRTP.cpp // Curiously Recurring Template Pattern (CRTP)
// =====================================================================================

module modern_cpp:crtp;

namespace CRTP {

    class ControlBase
    {
    public:
        virtual void draw() = 0;
        virtual ~ControlBase() {}
    };

    template <class T>
    class Control : public ControlBase  // inheritance needed for 'container' example
    {
    public:
        void draw()
        {
            static_cast<T*>(this)->eraseBackground();
            static_cast<T*>(this)->paint();
        }
    };

    template <class T>
    class ControlEx : public ControlBase
    {
    public:
        void draw()
        {
            derived()->erase_background();
            derived()->paint();
        }

    private:
        T* derived() { return static_cast<T*>(this); }
    };

    class Button : public Control<Button>
    {
    public:
        void eraseBackground()
        {
            std::cout << "erasing button background ..." << std::endl;
        }

        void paint()
        {
            std::cout << "painting button ..." << std::endl;
        }
    };

    class ButtonEx : public Control<ButtonEx>
    {
        friend class Control<ButtonEx>;

    private:
        void eraseBackground()
        {
            std::cout << "erasing button background ..." << std::endl;
        }

        void paint()
        {
            std::cout << "painting button ..." << std::endl;
        }
    };

    class Checkbox : public Control<Checkbox>
    {
    public:
        void eraseBackground()
        {
            std::cout << "erasing checkbox background ..." << std::endl;
        }

        void paint()
        {
            std::cout << "painting checkbox ..." << std::endl;
        }
    };

    template <class T>
    void drawControl(Control<T>& c)
    {
        c.draw();
    }

    static void test_01_crtp()
    {
        Button b;
        drawControl(b);

        Checkbox c;
        drawControl(c);
    }

    static void drawControls(std::vector<std::shared_ptr<ControlBase>>& controls) {

        for (auto& control : controls) {
            control->draw();
        }
    }

    static void test_02_crtp()
    {
        std::vector<std::shared_ptr<ControlBase>> vector;

        vector.emplace_back(std::make_shared<Checkbox>());
        vector.emplace_back(std::make_shared<Button>());

        drawControls(vector);
    }
}

void main_crtp()
{
    using namespace CRTP;
    test_01_crtp();
    test_02_crtp();
}

// =====================================================================================
// End-of-File
// =====================================================================================
