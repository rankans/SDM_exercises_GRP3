#include "avx2_simd_filter.hpp"
#include <iostream>

namespace avx2_simd_filter
{
    using namespace title_space;

    void avx2_simd_filter_and_print_titles(const title_record &table)
    {
        const int64_t *years = table.production_year().data();
        const std::vector<std::string> &titles = table.title();
        size_t n = table.size();

        const size_t stride = 4;
        size_t i = 0;

        const __m256i lower = _mm256_set1_epi64x(1970);
        const __m256i upper = _mm256_set1_epi64x(2000);

        // SIMD loop
        for (; i + stride <= n; i += stride)
        {
            __m256i v = _mm256_loadu_si256((const __m256i *)(years + i));

            __m256i ge_mask = _mm256_cmpgt_epi64(v, _mm256_sub_epi64(lower, _mm256_set1_epi64x(1)));
            __m256i lt_mask = _mm256_cmpgt_epi64(upper, v);

            __m256i cmp = _mm256_and_si256(ge_mask, lt_mask);

            int64_t *cmp_vals = (int64_t *)&cmp;
            for (int lane = 0; lane < 4; lane++)
            {
                if (cmp_vals[lane])
                {
                    std::cout << titles[i + lane] << "\n";
                }
            }
        }

        // Tail elements
        for (; i < n; ++i)
        {
            int64_t y = years[i];
            if (y >= 1970 && y < 2000)
            {
                std::cout << titles[i] << "\n";
            }
        }
    }

}