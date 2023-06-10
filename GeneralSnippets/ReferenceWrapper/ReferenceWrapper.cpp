// =====================================================================================
// ReferenceWrapper.cpp // Reference Wrapper // std::reference_wrapper // std::ref
// =====================================================================================

module modern_cpp:reference_wrapper;

namespace MyReferenceWrapper {

    void task (int& data) {    // expecting a reference to int 
        data = 123;
    }

    void test_01() {

        int data{ 1 };

        std::cout << data << std::endl;

        // std::thread t{ task, data };  // doesn't compile

        std::thread t{ task, std::ref(data) };      // works

        t.join();

        std::cout << data << std::endl;
    }

    void test_02() {

        /*  A reference does not satisfy the STL container element requirements
         *  (in this case: Erasable)
         */

        // std::vector<std::string&> names;  // doesn't compile

        std::vector<std::reference_wrapper<std::string>> names;

        std::string name1{ "Hans" };
        std::string name2{ "Sepp" };
        std::string name3{ "Georg" };

        names.push_back(std::ref(name1));
        names.push_back(std::ref(name2));
        names.push_back(std::ref(name3));

        for (const std::string& sr : names) {
            std::cout << sr << std::endl;
        }

        for (std::string& sr : names) {
            sr.append(".");
        }

        for (const std::string& sr : names) {
            std::cout << sr << std::endl;
        }
    }

    std::vector<std::reference_wrapper<std::string>> generateVector() {

        std::vector<std::reference_wrapper<std::string>> names;

        std::string name1{ "Hans" };
        std::string name2{ "Sepp" };
        std::string name3{ "Georg" };

        names.push_back(std::ref(name1));
        names.push_back(std::ref(name2));
        names.push_back(std::ref(name3));

        return names;
    }

    void test_03() {

        std::vector<std::reference_wrapper<std::string>> areThereNames {
            generateVector()
        };

        for (const std::string& sr : areThereNames) {
            std::cout << sr << std::endl;
        }
    }

    // =================================================================================

    /*
    * Possible implementation
    */

    template<typename T>
    class my_reference_wrapper {
    private:
        T* m_ptr;

    public:
        my_reference_wrapper(T& t) noexcept : m_ptr{ &t } {}

        operator T& () const noexcept { return *m_ptr; }

        T& get() const noexcept { return *m_ptr; }
    };

    template<typename T>
    my_reference_wrapper<T> my_ref(T& t) noexcept {
        return my_reference_wrapper<T>(t);
    }

    void test_04() {

        int result{ 1 };

        auto task = [] (int& r) {
            r = 123;
        };

        std::cout << result << std::endl;

        // std::thread t{ task, result };  // doesn't compile
         
        // pass result "by reference" to the thread
        std::thread t{task, my_ref(result)}; 

        t.join();

        std::cout << result << std::endl;
    }
}

void main_reference_wrapper()
{
    using namespace MyReferenceWrapper;

    test_01();
    test_02();
    // test_03();  // fails at runtime
    test_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
    