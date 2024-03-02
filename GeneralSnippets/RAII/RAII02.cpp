// =====================================================================================
// RAII02.cpp
// =====================================================================================

module modern_cpp:raii;

// See also:  
// https://stackoverflow.com/questions/4802494/do-i-need-to-close-a-stdfstream/4802506

namespace RAIIDemo02 {

    void write_to_file(const std::string& message)
    {
        // mutex to protect file access (shared across threads)
        static std::mutex mtex;

        // lock mutex before accessing file
        std::lock_guard<std::mutex> lock(mtex);

        // try to open file
        std::ofstream file("example.txt");
        if (!file.is_open())
            throw std::runtime_error("unable to open file");

        // write message to file
        file << message << std::endl;

        // a) file will be closed 1st when leaving scope (regardless of exception)
        // b) mutex will be unlocked 2nd (from lock destructor) when leaving
        //    scope (regardless of exception)

        // fstream (rsp. ofstream) is a proper RAII object:
        // it does close automatically at the end of the scope,
        // and there is absolutely no need whatsoever to call close manually
        // when closing at the end of the scope is sufficient.
    }

    static void test_01 () {
        write_to_file("Nachrichtentext");
    }
}

void main_raii_02()
{
    using namespace RAIIDemo02;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
