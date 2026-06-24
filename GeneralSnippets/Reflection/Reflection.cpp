// =====================================================================================
// Reflection.cpp
// =====================================================================================

module modern_cpp:reflection;

// Still in work:
// See the files 'Reflection_01.txt' and so on being linked in the 
// corresponding Markdown file

namespace Reflection {

    static void test_01()
    {
        std::println("Start:");
        std::println("Done.");
    }
}

// =====================================================================================

void main_reflection()
{
    using namespace Reflection;

    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
