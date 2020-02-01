// =====================================================================================
// Template Template Parameter
// =====================================================================================

#include <iostream>
#include <vector>
#include <list>
#include <string>

namespace TemplateTemplateParameterFunction {

    template <
        typename Value, 
        template <typename, typename> class Container, 
        typename Allocator = std::allocator<Value>
    >
    void testMe(Container<Value, Allocator>& container, const Value& value)
    {
        container.push_back(value);
        container.push_back(value);
        container.push_back(value);

        for (const auto& elem : container) {
            std::cout << elem << std::endl;
        }
    }

    void test_01_template_template_parameter_function() {

        std::vector<int> intVector;
        testMe(intVector, 123);

        std::vector<float> floatVector;
        testMe(floatVector, 1.2f);

        std::list<std::string> stringList;
        testMe(stringList, std::string("ABC"));
    }
}

namespace TemplateTemplateParameterClass {

    template <
        typename T,
        template <typename E, typename Allocator = std::allocator<E>> class Container = std::vector
    >
    class MyContainer
    {
    public:
        virtual ~MyContainer() = default;
        void testMe(T);

    private:
        Container<T> m_anotherContainer;
    };

    template <
        typename T,
        template <typename E, typename Allocator = std::allocator<E>> class Container
    >
    void MyContainer<T, Container>::testMe(T elem) 
    {
        m_anotherContainer.push_back(elem);
        m_anotherContainer.push_back(elem);
        m_anotherContainer.push_back(elem);

        for (const auto& elem : m_anotherContainer) {
            std::cout << elem << std::endl;
        }
    }

    void test_01_template_template_parameter_class() {

        MyContainer<int, std::vector> myIntContainer;
        myIntContainer.testMe(1);

        MyContainer<float, std::vector> myFloatContainer;
        myFloatContainer.testMe(9.9F);

        MyContainer<std::string, std::vector> myStringContainer;
        myStringContainer.testMe(std::string("XYZ"));
    }
}

int main() {

    using namespace TemplateTemplateParameterFunction;
    using namespace TemplateTemplateParameterClass;

    test_01_template_template_parameter_function();
    test_01_template_template_parameter_class();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
