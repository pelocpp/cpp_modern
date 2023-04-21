// =====================================================================================
// ReferenceWrapper.cpp // Reference Wrapper
// =====================================================================================

module modern_cpp:reference_wrapper;

namespace MyReferenceWrapper {

    void test_01() {

        std::vector<std::reference_wrapper<std::string>> names;

        std::string name1 = "Hans";
        std::string name2 = "Sepp";
        std::string name3 = "Georg";

        names.push_back(std::ref(name1));
        names.push_back(std::ref(name2));
        names.push_back(std::ref(name3));

        for (std::string& sr : names) {
            std::cout << sr << std::endl;
        }

        for (std::string& sr : names) {
            sr.append(".");
        }

        for (std::string& sr : names) {
            std::cout << sr << std::endl;
        }
    }

    std::vector<std::reference_wrapper<std::string>> generateVector() {

        std::vector<std::reference_wrapper<std::string>> tmp;

        std::string name1 = "Hans";
        std::string name2 = "Sepp";
        std::string name3 = "Georg";

        tmp.push_back(std::ref(name1));
        tmp.push_back(std::ref(name2));
        tmp.push_back(std::ref(name3));

        return tmp;
    }


    void test_02() {

        std::vector<std::reference_wrapper<std::string>> areThereNames = generateVector();

        for (std::string& sr : areThereNames) {
            std::cout << sr << std::endl;
        }
    }
}

void main_reference_wrapper()
{
    using namespace MyReferenceWrapper;
    test_01();
    //test_02();  // fails at runtime, corrupts ostream library
}

// =====================================================================================
// End-of-File
// =====================================================================================
    