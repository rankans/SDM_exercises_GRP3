cmake_minimum_required(VERSION 3.20)

add_executable(exercise6
    main.cpp
    batch/queries.cpp
    soa_tables_updated/company_name_soa.cpp
    soa_tables_updated/keyword.cpp
    soa_tables_updated/title.cpp
    ../commons/utils.cpp
    ../aos_table_defs/company_name.cpp
)

target_include_directories(exercise6
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set_target_properties(exercise6 PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_compile_options(exercise6 PRIVATE
    $<$<CONFIG:DEBUG>:-Og -g3 -Wall -Wextra -Wpedantic>
    $<$<CONFIG:RELEASE>:-O3 -Wall -Wextra -Wpedantic>
)

set_property(TARGET exercise6 PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
