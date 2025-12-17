#pragma once
#include "title.hpp"
#include <vector>

namespace mimd_ash
{
    // LAB 8 Task 1: filter + count using threads
    void mimd_filter_and_count_titles(const title_space::title_record &table);

    // LAB 8 Task 2: filter + collect positions + print titles using threads
    void mimd_filter_and_print_titles(const title_space::title_record &table);
}
