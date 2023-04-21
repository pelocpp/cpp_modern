// =====================================================================================
// TemplateTemplateParameter_01.cpp // Template Template Parameter
// =====================================================================================

module modern_cpp:template_template_parameter;

namespace TemplateTemplateParameter {

    namespace TemplateTemplateParameterFunction {

        template <
            typename T,
            typename TAllocator = std::allocator<T>,
            template <typename type, typename TAllocator> typename TContainer
        >
            void testMe(TContainer<T, TAllocator>& container, const T& value)
        {
            container.push_back(value);
            container.push_back(value);
            container.push_back(value);

            for (const auto& elem : container) {
                std::cout << elem << std::endl;
            }
        }

        void test_01() {

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

        void test_02() {

            MyContainer<int, std::vector> myIntContainer;
            myIntContainer.testMe(1);

            MyContainer<float, std::deque> myFloatContainer;
            myFloatContainer.testMe(9.9F);

            MyContainer<std::string, std::list> myStringContainer;
            myStringContainer.testMe(std::string("XYZ"));
        }
    }
}

void main_templates_template_parameter_01()
{
    using namespace TemplateTemplateParameter::TemplateTemplateParameterFunction;
    using namespace TemplateTemplateParameter::TemplateTemplateParameterClass;
    test_01();
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
