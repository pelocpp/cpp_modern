#include <iostream>
#include <memory>

// =====================================================================================
// Unique Pointer
// =====================================================================================

namespace UniquePointer {

    // Dummy Window Hierarchy
    class Component { };             
    class Label : public Component { };
    class Textfield : public Component { };

    class Button : public Component {
    public:
        int m_id; // need explicit ID for different buttons
        explicit Button(int id) : m_id{ id } {}
    };

    class Window { };

    class MyDialog : public Window {
        std::string m_title;

        // all these widgets are bound to the lifetime of the corresponding 'MyDialog' object
        std::unique_ptr<Label> m_lblFirstname{ new Label{} };        
        std::unique_ptr<Textfield> m_txtFirstname{ new Textfield{} };
        std::unique_ptr<Label> m_lblLastname{ new Label{} };     
        std::unique_ptr<Textfield> m_txtLastname{ new Textfield{} };
        std::unique_ptr<Button> m_btnOk{ new Button{1} };
        std::unique_ptr<Button> m_btnAbort{ new Button{2} };

    public:
        explicit MyDialog(const std::string& title) : m_title{ title } {}
        std::unique_ptr<Button> showModal() {
            return std::move(m_btnOk);
        }    
    };

    // helper functions
    std::unique_ptr<MyDialog> createDialog() {
        // note: flow of 'raw pointer' !!!
        return std::unique_ptr<MyDialog>{ new MyDialog{ "Enter Name" } };
    }

    int showDialog() {
        std::unique_ptr<MyDialog> dialog = createDialog();     
        std::unique_ptr<Button> pressed = dialog->showModal(); 
        return pressed->m_id;
    }

    void showAnotherDialog() {
        std::unique_ptr<MyDialog> dialog = createDialog();
        std::unique_ptr<Button> pressed1 = dialog->showModal();
        std::cout << "You've clicked " << pressed1->m_id << std::endl;
        std::unique_ptr<Button> pressed2 = dialog->showModal();  // this cannot work !!!
        std::cout << "You've clicked " << pressed2->m_id << std::endl;
    }

    void test_01() {
        int pressed_id = showDialog();
        if (pressed_id == 1) {
            std::cout << "You've clicked Okay" << std::endl;
        }
    }

    void test_02() {
        showAnotherDialog();
    }
}

int main()
// int main_unique_pointer()
{
    using namespace UniquePointer;
    // test_01();
    test_02();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
