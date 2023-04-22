// =====================================================================================
// Modules_Import.cpp // Keywords module / import
// =====================================================================================

module modern_cpp:module_import;

namespace ModulesAndImport {

    void halloSeminar() {

        std::cout << "Hallo Seminar" << std::endl;
    }
}

void main_modules_import()
{
    using namespace ModulesAndImport;

    halloSeminar();
}

// =====================================================================================
// End-of-File
// =====================================================================================
