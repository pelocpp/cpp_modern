// =====================================================================================
// Println.cpp // std::print // std::println
// =====================================================================================

module modern_cpp:println;

namespace StdPrintln {

    static void test_01()
    {
        std::println("Hello, world!");
    }

    static void test_02()
    {
        int value{ 123 };
        std::println("Value: {}", value);
    }

    static void test_03()
    {
        int firstValue{ 123 };
        int secondValue{ 456 };

        std::println("First Value: {}, Second Value: {}", firstValue, secondValue);
        std::println("First Value: {0}, Second Value: {1}", firstValue, secondValue);
    }

    // fill and align
    static void test_04()
    {
        int value{ 123 };

        std::println("{}", value);             // "123"
        std::println("{0}", value);            // "123"
        std::println("{:10}", value);          // "       123"
        std::println("!{:_<10}!", value);      // "!123_______!"
        std::println("!{:_>10}!", value);      // "!_______123!"
    }

    // fill, align and precision
    static void test_05()
    {
        int value{ 123 };

        std::println("{}", value);             // "123"
        std::println("{:d}", value);           // "123"
        std::println("{:010}", value);         // "0000000123"
        std::println("{:010d}", value);        // "0000000123"
        std::println("{:0}", value);           // "123"
        std::println("{:+}", value);           // "+123"
        std::println("{:+}", -value);          // "-123"
        std::println("{:+10}", value);         // "      +123"
        std::println("{:+10}", -value);        // "      -123"
        std::println("{:+010}", value);        // "+000000123"
        std::println("{:+010}", -value);       // "-000000123"
    }

    // fill, align and precision
    static void test_06()
    {
        float pi{ 3.1415926535f };

        std::println("{}", pi);                // "3.1415927"
        std::println("{0}", pi);               // "3.1415927"
        std::println("{:15f}", pi);            // "       3.141593"    (width = 15)
        std::println("{:{}f}", pi, 15);        // "       3.141593"    (width = 15)
        std::println("{:.12f}", pi);           // "3.141592741013"     (precision = 12)
        std::println("{:.{}f}", pi, 3);        // "3.142"              (precision = 3)
        std::println("{:15.12f}", pi);         // " 3.141592741013"    (width = 15, precision = 12)
        std::println("{:{}.{}f}", pi, 15, 12); // " 3.141592741013"    (width = 15, precision = 12)
    }

    // fill, align and precision
    static void test_07()
    {
        double pi{ 3.1415926535f };

        std::println("{}", pi);                // "3.1415927"
        std::println("{0}", pi);               // "3.1415927"
        std::println("{:15g}", pi);            // "       3.141593"    (width = 15)
        std::println("{:{}g}", pi, 15);        // "       3.141593"    (width = 15)
        std::println("{:.12g}", pi);           // "3.141592741013"     (precision = 12)
        std::println("{:.{}g}", pi, 3);        // "3.142"              (precision = 3)
        std::println("{:15.12g}", pi);         // " 3.141592741013"    (width = 15, precision = 12)
        std::println("{:{}.{}g}", pi, 15, 12); // " 3.141592741013"    (width = 15, precision = 12)
    }

    // Sign, #, and different formats 
    static void test_08()
    {
        std::println("Hexadecimal:  {:x}", 6);      // "Hexadecimal:  6"
        std::println("Hexadecimal:  {:x}", 30);     // "Hexadecimal: 1e"
        std::println("Hexadecimal:  {:X}", 30);     // "Hexadecimal: 1E"
        std::println("Hexadecimal:  {:#x}", 30);    // "Hexadecimal: 0x1e"
        std::println("Hexadecimal:  {:#X}", 30);    // "Hexadecimal: 0X1E"
        std::println("Hexadecimal:  {:15x}", 6);    // "Hexadecimal:               6"   (width = 15)
        std::println("Hexadecimal:  {:#15X}", 30);  // "Hexadecimal:            0X1E"   (width = 15)

        std::println("Octal:        {:o} ", 12);    // "Octal:       14"
        std::println("Octal:        {:#o} ", 12);   // "Octal:       014"
        std::println("Octal:        {:#o}", 4);     // "Octal:       04"

        std::println("Binary:       {:b} ", 31);    // "Binary:      11111"
        std::println("Binary:       {:#b} ", 31);   // "Binary:      0b11111"
        std::println("Binary:       {:#B}", 7);     // "Binary:      0B111"
        std::println("Binary:       {:#15b} ", 31); // "Binary:              0b11111"   (width = 15)
        std::println("Binary:       {:#15B}", 7);   // "Binary:                0B111"   (width = 15)
    }
}

void main_println()
{
    using namespace StdPrintln;

    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
    test_07();
    test_08();
}

// =====================================================================================
// End-of-File
// =====================================================================================
    