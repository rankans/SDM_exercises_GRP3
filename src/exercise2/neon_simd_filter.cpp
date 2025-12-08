#ifdef USE_NEON
#include "neon_simd_filter.hpp"
#include <arm_neon.h>
#include <iostream>

namespace neon_simd_filter
{
    using namespace title_space;
    std::vector<uint32_t>
    neon_filter_positions(const title_record &table,
                          int64_t lower_bound,
                          int64_t upper_bound)
    {
        const int64_t *years = table.production_year().data();
        size_t n = table.size();

        std::vector<uint32_t> matches;
        matches.reserve(n / 4); // heuristic to reduce reallocations

        const int64x2_t lower = vdupq_n_s64(lower_bound);
        const int64x2_t upper = vdupq_n_s64(upper_bound);

        const size_t stride = 2; // NEON loads 2x int64
        size_t i = 0;

        for (; i + stride <= n; i += stride)
        {
            int64x2_t v = vld1q_s64(years + i);

            // v >= lower && v < upper
            uint64x2_t ge_mask = vcgeq_s64(v, lower);
            uint64x2_t lt_mask = vcltq_s64(v, upper);
            uint64x2_t mask = vandq_u64(ge_mask, lt_mask);

            uint64_t lanes[2];
            vst1q_u64(lanes, mask);

            if (lanes[0])
                matches.push_back(i);
            if (lanes[1])
                matches.push_back(i + 1);
        }

        // Tail
        for (; i < n; i++)
            if (years[i] >= lower_bound && years[i] < upper_bound)
                matches.push_back(i);

        return matches;
    }

    void print_titles_from_positions(
        const title_record &table,
        const std::vector<uint32_t> &positions)
    {
        std::cout << "Titles in range:\n";
        for (uint32_t idx : positions)
        {
            std::cout << " - " << table.title()[idx] << "\n";
        }
        std::cout << "Total: " << positions.size() << "\n";
    }

}
#endif
