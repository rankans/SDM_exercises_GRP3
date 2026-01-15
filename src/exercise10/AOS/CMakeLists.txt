cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(exercise10_aos_main 
    main.cpp
)

target_include_directories(exercise10_aos_main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(exercise10_aos_main PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Debug>:-Og -g3>
)