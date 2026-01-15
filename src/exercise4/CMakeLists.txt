cmake_minimum_required(VERSION 3.20)
project(SDM-exercise4 CXX)

option(ENABLE_SIMD "Enable AVX2/FMA/BMI2 SIMD instructions" ON)

add_executable(exercise4
    main.cpp
    queries.cpp
    ../soa_table_defs/company_name_soa.cpp
    ../soa_table_defs/keyword.cpp
    ../soa_table_defs/title.cpp

    ../commons/utils.cpp
    
)

target_include_directories(exercise4
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set_target_properties(exercise4 PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_compile_options(exercise4 PRIVATE
    $<$<CONFIG:DEBUG>:-Og -g3 -Wall -Wextra -Wpedantic>
    $<$<CONFIG:RELEASE>:-O3 -Wall -Wextra -Wpedantic>
)

# Interprocedural optimization for Release
set_property(TARGET exercise4 PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
