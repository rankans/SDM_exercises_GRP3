cmake_minimum_required(VERSION 3.20)
project(SDM-exercise2_new CXX)

option(ENABLE_SIMD "Enable AVX2/FMA/BMI2 SIMD instructions" ON)

add_executable(exercise2_new
    main.cpp
    queries.cpp
    ../aos_table_defs/company_name.cpp
    ../aos_table_defs/keywordaos.cpp
    ../aos_table_defs/titleaos.cpp

    ../commons/utils.cpp
    
)

target_include_directories(exercise2_new
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set_target_properties(exercise2_new PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_compile_options(exercise2_new PRIVATE
    $<$<CONFIG:DEBUG>:-Og -g3 -Wall -Wextra -Wpedantic>
    $<$<CONFIG:RELEASE>:-O3 -Wall -Wextra -Wpedantic>
)

# Interprocedural optimization for Release
set_property(TARGET exercise2_new PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
