// =====================================================================================
// InputOutputStreams.cpp // Input/Output Streams
// =====================================================================================

module modern_cpp:input_output_streams;

namespace InputOutputStreams {

    void test_01() {

        // input of several values with one statement
        int val1, val2;
        std::cout << "Please enter 2 int-values:";
        std::cin >> val1 >> val2;
        std::cout << val1 << " : " << val2 << std::endl;
    }

    void test_02() {

        // output with put and write - unformatted output
        std::string s("ABC");
        for (char ch : s) {
            std::cout.put(ch);
        }

        std::cout << 10 << std::endl;
        std::cout.put(10) << std::endl;  // is newline '\n'

        char charData[] = { '1', '2', '3', '4' };
        std::cout.write(charData, 4);

        std::cout.put(10) << std::endl;  // is newline '\n'
        std::cout.flush();  // is newline '\n'
    }

    void checkIOstate(std::ios& stream) {
        if (stream.good()) {
            std::cout << "Everything Okay" << std::endl;
        }
        else if (stream.bad()) {
            std::cout << "Fatal Error" << std::endl;
        }
        else if (stream.fail()) {
            std::cout << "Error during Input/Output" << std::endl;
            if (stream.eof()) {
                std::cout << "EOF reached" << std::endl;
            }
        }
        stream.clear();
    }

    void test_03() {

        int val = 0;
        std::cout << "Enter value: ";
        std::cin >> val;
        checkIOstate(std::cin);
        //= enter value - everything shold be okay, if you enter an int value

        std::ifstream file;
        file.open("notExisting.txt");
        checkIOstate(file);
        //= error during IO

        std::fstream fstr;
        fstr.open("newFile.txt", std::ofstream::out | std::ofstream::in  | std::ofstream::binary | std::ofstream::trunc);
        fstr << "this is some text in this file\n";
        fstr.seekp(std::ios_base::beg);

        char ch;
        while (fstr.good()) {
            fstr.get(ch);
            if (fstr.good()) 
                std::cout.put(ch);
        }
        checkIOstate(fstr);
        //= error during IO
        //= EOF reached
    }

    void f() {
        bool b = true;
        std::cout << b << std::endl;     // output: "true"
    }

    void test_04() {
        bool b = true;
        std::cout << std::boolalpha << b << std::endl;     // output: "true"
        b = false;
        std::cout << b << std::endl;                       // output: "false"
        f();
        std::cout << std::noboolalpha << b << std::endl;   // output: "0"
        b = true;
        std::cout << b << std::endl;                       // output: "1"
    }

    void g() {
        int val = 100;
        std::cout << val << std::endl;   // output: 0x64
    }

    void test_05() {
        int val = 255;
        std::cout << std::showbase << std::endl;
        std::cout << std::dec << val << std::endl;  // output: 255
        std::cout << std::hex << val << std::endl;  // output: 0xff
        g();
        std::cout << std::oct << val << std::endl;  // output: 0377
        std::cout << val << std::endl;  // output: 0377
        std::cout << std::dec;
        std::cout << val << std::endl;  // output: 255
    }

    void test_06() {
        int val = -123;
        std::cout << std::setw(10) << std::internal << val << std::endl;
        //= -     123
        std::cout << std::setw(10) << std::left << val << std::endl;
        //= -123
        std::cout << std::setw(10) << std::right << val << std::endl;
        //=      -123

        val = 987;
        std::cout << std::setw(10) << std::internal << val << std::endl;
        //=       987
        std::cout << std::setw(10) << std::left << val << std::endl;
        //= 987
        std::cout << std::setw(10) << std::right << val << std::endl;
        //=       987
    }

    void test_07() {
        // note: setw must be caller for every output seperately
        int val = 12345;
        std::cout << std::setw(10);
        std::cout << std::right << val << std::endl;
        std::cout << std::right << val << std::endl;
        std::cout << std::right << val << std::endl;

        std::cout << std::setw(20);
        std::cout << std::right << val << std::endl;
        std::cout << std::right << val << std::endl;
    }

    void test_08() {
        // note: setfill must be reset
        int val = 12345;
        std::cout << std::setw(10) << std::setfill('.');
        std::cout << std::right << val << std::endl;
        std::cout << std::right << val << std::endl;
        std::cout << std::setw(20);
        std::cout << std::right << val << std::endl;
        std::cout << std::right << val << std::endl;
        std::cout << std::setw(10) << std::setfill(' ');
        std::cout << std::right << val << std::endl;
    }

    // writing manipulators without parameters
    std::ostream& hash(std::ostream& os) {
        os << '#';
        return os;
    }

    auto hashLambda = [](std::ostream& os) -> std::ostream& {
        return os << "#";
    };

    void test_09() {
        std::cout << "Some Text " << hash << " Some Text" << std::endl;
        std::cout << "some text " << hashLambda << " some text" << std::endl;
    }

    // writing manipulators with parameters 
    // here: putting n exclamation marks into the output stream
    class exmarks { 
    private:
        int m_numExMarks;
    public:
        exmarks(int n = 1) : m_numExMarks{ n } {}

        std::ostream& operator()(std::ostream& os) const { // Functor
            for (int i = 0; i < m_numExMarks; ++i) 
                os << '!';
            // return os << '\n';
            return os;
        }
    };

    std::ostream& operator<<(std::ostream& os, const exmarks& elem) {
        return elem(os);
    }

    void test_10() {

        std::cout << "AAA" << exmarks()  << "AAA" << std::endl;
        std::cout << "AAA" << exmarks(1) << "AAA" << std::endl;
        std::cout << "AAA" << exmarks(2) << "AAA" << std::endl;
        std::cout << "AAA" << exmarks(3) << "AAA" << std::endl;
        std::cout << "AAA" << exmarks(4) << "AAA" << std::endl;
    }
}

void main_input_output_streams()
{
    using namespace InputOutputStreams;

    // test_01();   // needs console input
    test_02();
    // test_03();   // needs console input
    test_04();
    test_05();
    test_06();
    test_07();
    test_08();
    test_09();
    test_10();
}

// =====================================================================================
// End-of-File
// =====================================================================================
