#include <iostream>
#include <chrono>
#include "neon_simd_filter.hpp"
#include <set>

using namespace std;

int main()
{
    auto title_table = title_space::title_record::load_from_file("/exercise/imdb/csv/title.csv");
    auto &title_val = *title_table;

    // Lab 7: SIMD Intel AVX2
    // avx2_simd_filter::avx2_simd_filter_and_print_titles(title_val); // Only works with SIMD in Intel AVX2 ; with scalar builds disabled
    // neon_simd_filter::

    // Lab 7: SIMD Mac Neon
    auto results = neon_simd_filter::neon_filter_positions(title_val, 1970, 2000);
    neon_simd_filter::print_titles_from_positions(title_val, results);
    std::cout << "Titles in range 1970 – 1999 (using SIMD Mac ARM_Neon): " << results.size() << "\n";

    return 0;
};