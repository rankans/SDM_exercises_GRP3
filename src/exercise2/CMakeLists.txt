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
    neon_simd_filter.cpp
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
# if(ENABLE_SIMD AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#     target_compile_options(exercise2 PRIVATE
#         $<$<CONFIG:RELEASE>:-mavx2 -mfma -mbmi -mbmi2 -mpopcnt>
#     )
# endif()

# add your SIMD configs here commenting the above one
# Detect architecture automatically
include(CheckCXXCompilerFlag)

if(ENABLE_SIMD)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
        message(STATUS "Building with AVX2 (x86)")
        check_cxx_compiler_flag("-mavx2" COMPILER_SUPPORTS_AVX2)
        if(COMPILER_SUPPORTS_AVX2)
            target_compile_definitions(exercise2 PRIVATE USE_AVX2=1)
            target_compile_options(exercise2 PRIVATE -mavx2 -mfma -mbmi -mbmi2 -mpopcnt)
        endif()
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64")
        message(STATUS "Building with NEON (ARM64)")
        target_compile_definitions(exercise2 PRIVATE USE_NEON=1)
    endif()
endif()

# Interprocedural optimization for Release
set_property(TARGET exercise2 PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
