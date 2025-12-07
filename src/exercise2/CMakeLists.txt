cmake_minimum_required(VERSION 3.20)
project(SDM-Exercise2 CXX)

option(ENABLE_SIMD "Enable AVX2/FMA/BMI2 SIMD instructions" ON)

add_executable(exercise2
    main.cpp
    company_name.cpp
    title.cpp
    keyword.cpp
    keywordaos.cpp
    queries.cpp
    utils.cpp
    titleaos.cpp
    company_name_soa.cpp
    avx2_simd_filter.cpp
)

set_target_properties(exercise2 PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_compile_options(exercise2 PRIVATE
    $<$<CONFIG:DEBUG>:-Og -g3 -Wall -Wextra -Wpedantic>
    $<$<CONFIG:RELEASE>:-O3 -Wall -Wextra -Wpedantic>
)

# SIMD flags for AVX2
if(ENABLE_SIMD AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(exercise2 PRIVATE
        $<$<CONFIG:RELEASE>:-mavx2 -mfma -mbmi -mbmi2 -mpopcnt>
    )
endif()

# add your SIMD configs here commenting the above one

# Interprocedural optimization for Release
set_property(TARGET exercise2 PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
