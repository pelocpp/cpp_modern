// =====================================================================================
// SourceLocation.cpp // std::source_location
// =====================================================================================

module modern_cpp:source_location;

import std;

namespace {

    static void log(
        const std::string_view message, 
        const std::source_location location = std::source_location::current())
    {
        std::println("File:          {}", location.file_name());
        std::println("Function Name: {}", location.function_name());
        std::println("Column :       {}", location.column());
        std::println("Line:          {}", location.line());
        std::println();
    }

    template<typename T>
    static void function(T x)
    {
        log(x);
    }

    void source_location() {

        log("Hello World!");
        function("Hello Function!");
    }
}

void main_source_location()
{
    source_location();
}

// =====================================================================================
// End-of-File
// =====================================================================================
