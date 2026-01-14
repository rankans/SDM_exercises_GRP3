cmake_minimum_required(VERSION 3.20)

option(ENABLE_SIMD "Enable AVX2/FMA/BMI2 SIMD instructions" ON)

add_executable(exercise7_intel
    main.cpp
    avx2_simd_filter.cpp

    ../../aos_table_defs/company_name.cpp
    ../../aos_table_defs/keywordaos.cpp
    ../../aos_table_defs/titleaos.cpp
    
    ../../soa_table_defs/company_name_soa.cpp
    ../../soa_table_defs/keyword.cpp
    ../../soa_table_defs/title.cpp

    ../../commons/utils.cpp
)

set_target_properties(exercise7_intel PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_compile_options(exercise7_intel PRIVATE
    $<$<CONFIG:DEBUG>:-Og -g3 -Wall -Wextra -Wpedantic>
    $<$<CONFIG:RELEASE>:-O3 -Wall -Wextra -Wpedantic>
)

include(CheckCXXCompilerFlag)

if(ENABLE_SIMD)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
        message(STATUS "Building with AVX2 (x86)")
        check_cxx_compiler_flag("-mavx2" COMPILER_SUPPORTS_AVX2)
        if(COMPILER_SUPPORTS_AVX2)
            target_compile_definitions(exercise7_intel PRIVATE USE_AVX2=1)
            target_compile_options(exercise7_intel PRIVATE -mavx2 -mfma -mbmi -mbmi2 -mpopcnt)
        endif()
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64")
        message(STATUS "Building with NEON (ARM64)")
        target_compile_definitions(exercise7_intel PRIVATE USE_NEON=1)
    endif()
endif()

set_property(TARGET exercise7_intel PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)