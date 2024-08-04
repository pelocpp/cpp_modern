// =====================================================================================
// Modules.cpp // Keywords 'module' and 'import'
// =====================================================================================

module modern_cpp:modules;

namespace ModulesDemo {

    static void halloSeminar() {

        std::cout << "Hallo Seminar" << std::endl;
    }
}

void main_modules()
{
    using namespace ModulesDemo;

    halloSeminar();
}

// =====================================================================================
// End-of-File
// =====================================================================================
