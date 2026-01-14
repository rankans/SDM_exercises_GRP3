cmake_minimum_required(VERSION 3.20)

add_executable(exercise8
    main.cpp
    thread_execution_ran.cpp
    title_thread_exec.cpp

    ../aos_table_defs/company_name.cpp
    ../aos_table_defs/keywordaos.cpp
    ../aos_table_defs/titleaos.cpp
    
    ../soa_table_defs/company_name_soa.cpp
    ../soa_table_defs/keyword.cpp
    ../soa_table_defs/title.cpp

    ../commons/utils.cpp
)

set_target_properties(exercise8 PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_compile_options(exercise8 PRIVATE
    $<$<CONFIG:DEBUG>:-Og -g3 -Wall -Wextra -Wpedantic>
    $<$<CONFIG:RELEASE>:-O3 -Wall -Wextra -Wpedantic>
)

include(CheckCXXCompilerFlag)

set_property(TARGET exercise8 PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)