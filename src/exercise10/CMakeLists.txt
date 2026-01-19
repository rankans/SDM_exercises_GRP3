cmake_minimum_required(VERSION 3.20)

add_executable(exercise10
    SOA/main.cpp
    AOS/r1_aos.cpp
    SOA/r1_soa.cpp
    SOA/r2_soa.cpp
)

set_target_properties(exercise10 PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_compile_options(exercise10 PRIVATE
    $<$<CONFIG:DEBUG>:-Og -g3 -Wall -Wextra -Wpedantic>
    $<$<CONFIG:RELEASE>:-O3 -Wall -Wextra -Wpedantic>
)

include(CheckCXXCompilerFlag)

set_property(TARGET exercise10 PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)