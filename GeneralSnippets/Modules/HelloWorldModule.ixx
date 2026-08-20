// =====================================================================================
// Module Interface Partition 'hello_world_module' // HelloWorldModule.ixx
// =====================================================================================

export module hello_world_module;

import std;

export namespace MyHelloWorld
{
    int globalData{};

    void sayHello()
    {
        std::printf("Hello Module! Data is %d\n", globalData);
    }
}

export void main_modules_hello_world();

// =====================================================================================
// End-of-File
// =====================================================================================
