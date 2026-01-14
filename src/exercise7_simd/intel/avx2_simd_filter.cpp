#ifdef USE_AVX2
#include <immintrin.h>
#include "avx2_simd_filter.hpp"
#include <iostream>

namespace avx2_simd_filter
{
    using namespace title_space;

    void avx2_simd_filter_and_print_titles(const title_record &table)
    {
        const int64_t *years = table.production_year().data();
        size_t n = table.size();
        int count = 0;

        const size_t stride = 4;
        size_t i = 0;

        const __m256i lower = _mm256_set1_epi64x(1970);
        const __m256i upper = _mm256_set1_epi64x(2000);

        for (; i + stride <= n; i += stride)
        {
            __m256i v = _mm256_loadu_si256((const __m256i *)(years + i));

            __m256i ge_mask = _mm256_cmpgt_epi64(v, _mm256_sub_epi64(lower, _mm256_set1_epi64x(1)));
            __m256i lt_mask = _mm256_cmpgt_epi64(upper, v);

            __m256i mask = _mm256_and_si256(ge_mask, lt_mask);

            // Extract each lane properly
            int64_t lanes[4];
            _mm256_storeu_si256((__m256i *)lanes, mask);
            for (int j = 0; j < 4; ++j)
                if (lanes[j] != 0) // non-zero = true
                    ++count;
        }

        // Tail
        for (; i < n; ++i)
            if (years[i] >= 1970 && years[i] < 2000)
                ++count;

        std::cout << "Titles in range 1970–1999 (using SIMD Intel AVX2): " << count << "\n";
    }
}
#endif