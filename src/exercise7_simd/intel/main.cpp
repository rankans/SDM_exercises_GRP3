#include <iostream>
#include <chrono>
#include "avx2_simd_filter.hpp"
#include <set>

using namespace std;

int main()
{
    auto title_table = title_space::title_record::load_from_file("/exercise/imdb/csv/title.csv");
    auto &title_val = *title_table;

    // Lab 7: SIMD Intel AVX2
    avx2_simd_filter::avx2_simd_filter_and_print_titles(title_val); // Only works with SIMD in Intel AVX2 ; with scalar builds disabled

    return 0;
};