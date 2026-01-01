add_executable(exercise2_new
    main.cpp
    company_name.cpp
    utils.cpp
    title.cpp
    keyword.cpp
    queries.cpp
)


set_target_properties(exercise2_new PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_compile_options(exercise2_new PRIVATE
    $<$<CONFIG:DEBUG>:-Og -g3 -Wall -Wextra -Wpedantic -Werror>
    $<$<CONFIG:RELEASE>:-O3 -Wall -Wextra -Wpedantic -Werror>
)

set_property(TARGET exercise2_new PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
