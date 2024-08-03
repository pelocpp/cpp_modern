// =====================================================================================
// Modules.cpp // Keywords 'module' and 'import'
// =====================================================================================

module modern_cpp:modules;

namespace ModulesAndImport {

    static void halloSeminar() {

        std::cout << "Hallo Seminar" << std::endl;
    }
}

void main_modules()
{
    using namespace ModulesAndImport;

    halloSeminar();
}

// =====================================================================================
// End-of-File
// =====================================================================================
