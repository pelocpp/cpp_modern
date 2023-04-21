// =====================================================================================
// TemplateSpecialization.cpp // Template Specialization
// =====================================================================================

module modern_cpp:template_specialization;

namespace TemplateSpecialization {

    // Explicit Template Specialization
    namespace ClassTemplates_ExplicitTemplateSpecialization {

        template<typename T>
        class GenericSorter
        {
        public:
            static void sort(std::vector<T>&) { /* ... */ }
        };

        template<>
        class GenericSorter<char>
        {
        public:
            static void sort(std::vector<char>&) { /* ... */ }
        };

        void test_01() {
            std::vector<int>  intVector;
            std::vector<char> charVector;

            GenericSorter<int>::sort(intVector);    // calls sort<std::vector<int>&>
            GenericSorter<char>::sort(charVector);  // calls specialized sort<std::vector<char>&>
        }
    }

    // Partial Template Specialization
    namespace ClassTemplates_PartialTemplateSpecialization {

        template<typename T>
        class GenericSorter
        {
        public:
            static void sort(std::vector<T>&) { /* ... */ }
        };

        template<typename T>
        class GenericSorter<T*>
        {
        public:
            static void sort(std::vector<T*>&) { /* ... */ }
        };

        void test_02() {
            std::vector<int> intVector;
            std::vector<int*> pointerVector;

            GenericSorter<int>::sort(intVector);       // calls sort<std::vector<int>&>
            GenericSorter<int*>::sort(pointerVector);  // calls specialized sort<std::vector<int*>&>
        }
    }
}

void main_template_specialization()
{
    using namespace TemplateSpecialization;
    ClassTemplates_ExplicitTemplateSpecialization::test_01();
    ClassTemplates_PartialTemplateSpecialization::test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
