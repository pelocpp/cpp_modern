// =====================================================================================
// Module Interface Partition 'hello_world'
// =====================================================================================

/// HelloWorld.ixx

export module hello_world;

import std;

export namespace MyHelloWorld
{
    int globalData{};

    void sayHello()
    {
        std::printf("Hello Module! Data is %d\n", globalData);
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
