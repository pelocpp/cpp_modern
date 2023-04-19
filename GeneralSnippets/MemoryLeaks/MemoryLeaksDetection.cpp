// =====================================================================================
// MemoryLeaksDetection.cpp // Memory Leaks Detection
// =====================================================================================

module;

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

module modern_cpp:memory_leaks_detection;

namespace MemoryLeaksDetection {

    void test_01() {

        int* ip = new int[10];
        // delete[] ip;   // put this line into comment to generate 'Object dump'
    }
}

void main_memory_leaks_detection () {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    using namespace MemoryLeaksDetection;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
