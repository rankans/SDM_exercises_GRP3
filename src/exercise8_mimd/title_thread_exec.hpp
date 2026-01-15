#pragma once
#include <cstdint>
#include <vector>
#include <thread>
#include <iostream>
#include <algorithm>
#include "../soa_table_defs/title.hpp"

class title_thread
{
private:
    int64_t _threadCount;

    void processQuery(const title_record &title_table, int64_t year_start, int64_t year_end);

    void processSubFilter(const std::vector<int64_t> &years,
                          size_t start, size_t end,
                          int64_t year_start, int64_t year_end,
                          std::vector<size_t> *out_positions);

public:
    explicit title_thread(int64_t threadCount = 4)
        : _threadCount(threadCount) {}

    void runQuery(const title_record &title_table,
                  int64_t year_start = 1970,
                  int64_t year_end = 2000);
};