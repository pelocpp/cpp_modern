// =====================================================================================
// https://github.com/pelocpp // https://peterloos.de
// =====================================================================================

import modern_cpp;
import modern_cpp_exercises;

import std;

#define MessageText "Collection of Modern C++ Code Examples - Copyright (C) 2026 Peter Loos."

#pragma message(MessageText)

int main()
{
    //extern int _main_modules();
    //_main_modules();

    std::println(MessageText);

    // main entry points code snippets
    try
    {
        //main_accumulate();
        //main_algorithms();
        //main_allocator();
        //main_any();
        //main_argument_dependent_name_lookup();
        //main_array();
        //main_array_decay();
        //main_attributes();
        //main_auto();
        //main_back_inserter();
        //main_bind();
        //main_brace_initialization();
        //main_casts();
        //main_common_type();
        //main_concepts_requires_classes();
        //main_concepts_requires_functions();
        //main_const_variants();
        //main_constexpr();
        //main_constexpr_crc();
        //main_constructor_invocations();
        //main_copy_move_elision();
        //main_copy_swap_idiom();
        //main_crtp();
        //main_decltype();
        //main_default_initialization();
        //main_erase_remove_idiom();
        //main_expression_templates();
        //main_exception_safety();
        //main_expected();
        //main_explicit_keyword();
        //main_folding();
        //main_functional_programming_ranges();
        //main_functional_programming();
        //main_functional_programming_alternate();
        //main_generate();
        //main_generic_functions();
        //main_initializer_list();
        //main_input_output_streams();  
        //main_invoke();
        //main_lambdas();
        //main_lambda_and_closure();
        //main_lambdas_this_closure();
        //main_literals();
        //main_memory_leaks_detection();
        //main_metaprogramming_01();
        //main_metaprogramming_02(); 
        //main_modularized_standard_library(); 
        //main_modules();
        //main_move_semantics();
        //main_optional();
        //main_perfect_forwarding();
        //main_placement_new();
        //main_println();
        //main_raii();
        //main_raii_02();
        //main_random();
        //main_range_based_for_loop();
        //main_reference_wrapper();
        //main_regular_expressions();
        //main_rvalue_lvalue();
        //main_sfinae();
        //main_shared_ptr();
        //main_source_location();
        //main_sso();
        //main_static_assert();
        //main_string_view();
        //main_structured_binding();
        //main_templates_class_basics_01();
        //main_templates_class_basics_02();
        //main_templates_function_basics();
        //main_templates_template_parameter_01();
        //main_templates_template_parameter_02();
        //main_templates_specialization();
        //main_to_underlying();
        //main_transform();
        //main_tuple(); 
        //main_two_phase_name_lookup();
        //main_type_erasure();
        //main_type_traits();
        //main_unique_ptr();
        //main_variadic_templates_introduction();
        //main_variadic_templates_working_on_every_argument();
        //main_variadic_templates_sum_of_sums();
        //main_variadic_templates_mixins();
        //main_variant();
        //main_virtual_base_class_destructor();
        //main_virtual_override_final();
        //main_weak_pointer();

        //main_exercises();
    }
    catch (const std::exception& ex) {
        std::println("Exception: {}", ex.what());
    }

    std::println("Done.");
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
