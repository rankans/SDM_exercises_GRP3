add_executable(exercise3
    main.cpp
    company_name.cpp
    utils.cpp
    title.cpp
    keyword.cpp
    queries.cpp
)


set_target_properties(exercise3 PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_compile_options(exercise3 PRIVATE
    $<$<CONFIG:DEBUG>:-Og -g3 -Wall -Wextra -Wpedantic -Werror>
    $<$<CONFIG:RELEASE>:-O3 -Wall -Wextra -Wpedantic -Werror>
)

set_property(TARGET exercise3 PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
