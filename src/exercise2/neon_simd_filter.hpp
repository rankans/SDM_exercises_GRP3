#pragma once
#include "title.hpp"
#include <vector>

namespace neon_simd_filter
{
    std::vector<uint32_t>
    neon_filter_positions(const title_space::title_record &table,
                          int64_t lower, int64_t upper);

    void print_titles_from_positions(
        const title_space::title_record &table,
        const std::vector<uint32_t> &positions);

}
