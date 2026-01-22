cmake_minimum_required(VERSION 3.20)

# SOA executable for column-store join operations
add_executable(exercise10_soa
    SOA/main.cpp
    SOA/r1_soa.cpp
    SOA/r2_soa.cpp
)

# AOS executable for row-store join operations  
add_executable(exercise10_aos
    AOS/main.cpp
    AOS/r1_aos.cpp
    AOS/r2_aos.cpp
)

# Combined executable with both SOA and AOS (legacy)
add_executable(exercise10_combined
    SOA/main.cpp
    AOS/r1_aos.cpp
    AOS/r2_aos.cpp
    SOA/r1_soa.cpp
    SOA/r2_soa.cpp
)

# Set properties for all executables
foreach(target exercise10_soa exercise10_aos exercise10_combined)
    set_target_properties(${target} PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
    )

    target_compile_options(${target} PRIVATE
        $<$<CONFIG:DEBUG>:-Og -g3 -Wall -Wextra -Wpedantic>
        $<$<CONFIG:RELEASE>:-O3 -Wall -Wextra -Wpedantic>
    )

    set_property(TARGET ${target} PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
endforeach()

include(CheckCXXCompilerFlag)
