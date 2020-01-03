#include <iostream>
#include <string>

// =====================================================================================
// Klassentemplates
// =====================================================================================

namespace ClassTemplatesBasics {

    template <typename T>
    class Optional
    {
        T m_value;
        bool m_hasValue;

    public:
        Optional() : m_hasValue(false), m_value(T{}) {  }
        Optional(T const& value) : m_value(value), m_hasValue(true) { }

        void setValue(T const& value) {
            m_value = value;
            m_hasValue = true;
        }

        void clear() {
            m_hasValue = false;
        }

        T const& getValue() const {
            if (! m_hasValue) {
                std::cerr << "Error! No value present!\n";
            }
            return m_value;
        }

        bool hasValue() const {
            return m_hasValue;
        }
    };

    void test_01() {
        Optional<int> obj;
        std::cout << "Object has value: " << obj.hasValue() << "\n";
        obj.setValue(123);
        std::cout << "Object has value: " << obj.hasValue() << "\n";
        std::cout << "obj = " << obj.getValue() << "\n";
        obj.clear();
        std::cout << "Object has value: " << obj.hasValue() << "\n";
        int dontKnow = obj.getValue();
    }

    void test_02() {
        Optional<std::string> obj;
        std::cout << "Object has value: " << obj.hasValue() << "\n";
        obj.setValue("ABC");
        std::cout << "Object has value: " << obj.hasValue() << "\n";
        std::cout << "obj = " << obj.getValue() << "\n";
        obj.clear();
        std::cout << "Object has value: " << obj.hasValue() << "\n";
        std::string dontKnow = obj.getValue();
    }
}

int main_class_templates_basics()
{
    using namespace ClassTemplatesBasics;

    test_01();
    test_02();

    return 0;
}
