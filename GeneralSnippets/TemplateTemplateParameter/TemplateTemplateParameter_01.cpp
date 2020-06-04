// =====================================================================================
// Template Template Parameter
// =====================================================================================

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>

namespace TemplateTemplateParameterFunction {

    template <
        typename T, 
        template <typename type, typename allocator> typename Container,
        typename Allocator = std::allocator<T>
    >
    void testMe(Container<T, Allocator>& container, const T& value)
    {
        container.push_back(value);
        container.push_back(value);
        container.push_back(value);

        for (const auto& elem : container) {
            std::cout << elem << std::endl;
        }
    }

    void test_01_ttp() {

        std::vector<int> intVector;
        testMe(intVector, 123);

        std::deque<float> floatVector;
        testMe(floatVector, 1.2f);

        std::list<std::string> stringList;
        testMe(stringList, std::string("ABC"));
    }
}

namespace TemplateTemplateParameterClass {

    template <
        typename T,
        template <
            typename,
            typename Allocator = std::allocator<T>> typename Container = std::vector
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
        template <
            typename,
            typename Allocator = std::allocator<T>> typename Container
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

    void test_01_ttp() {

        MyContainer<int, std::vector> myIntContainer;
        myIntContainer.testMe(1);

        MyContainer<float, std::deque> myFloatContainer;
        myFloatContainer.testMe(9.9F);

        MyContainer<std::string, std::list> myStringContainer;
        myStringContainer.testMe(std::string("XYZ"));
    }
}

int main_template_template_parameter () {

    using namespace TemplateTemplateParameterFunction;
    // using namespace TemplateTemplateParameterClass;
    test_01_ttp();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
