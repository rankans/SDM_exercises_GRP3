#include "mimd_ash.hpp"
#include <thread>
#include <vector>
#include <iostream>
#include <iterator>

namespace mimd_ash
{
    using namespace title_space;

    // Task 1: Filter + Aggregation
    void count_worker(const int64_t *years,
                      size_t start,
                      size_t end,
                      int &local_count)
    {
        int count = 0;
        for (size_t i = start; i < end; ++i)
            if (years[i] >= 1970 && years[i] < 2000)
                ++count;

        local_count = count;
    }

    void mimd_filter_and_count_titles(const title_record &table)
    {
        const int64_t *years = table.production_year().data();
        size_t n = table.size();

        unsigned int num_threads = std::thread::hardware_concurrency();
        if (num_threads == 0) num_threads = 4;

        std::vector<std::thread> threads;
        std::vector<int> local_counts(num_threads, 0);

        size_t chunk_size = n / num_threads;

        for (unsigned int t = 0; t < num_threads; ++t)
        {
            size_t start = t * chunk_size;
            size_t end = (t == num_threads - 1) ? n : start + chunk_size;

            threads.emplace_back(count_worker, years, start, end, std::ref(local_counts[t]));
        }

        for (auto &th : threads) th.join();

        int total_count = 0;
        for (int c : local_counts) total_count += c;

        std::cout << "Titles in range 1970–1999 (MIMD count): " << total_count << "\n";
    }

    // Task 2: Filter + Selection
    void position_worker(const int64_t *years,
                         size_t start,
                         size_t end,
                         std::vector<size_t> &local_positions)
    {
        for (size_t i = start; i < end; ++i)
            if (years[i] >= 1970 && years[i] < 2000)
                local_positions.push_back(i);
    }

    void mimd_filter_and_print_titles(const title_record &table)
    {
        const int64_t *years = table.production_year().data();
        size_t n = table.size();

        unsigned int num_threads = std::thread::hardware_concurrency();
        if (num_threads == 0) num_threads = 4;

        std::vector<std::thread> threads;
        std::vector<std::vector<size_t>> local_positions(num_threads);

        size_t chunk_size = n / num_threads;

        for (unsigned int t = 0; t < num_threads; ++t)
        {
            size_t start = t * chunk_size;
            size_t end = (t == num_threads - 1) ? n : start + chunk_size;

            threads.emplace_back(position_worker, years, start, end, std::ref(local_positions[t]));
        }

        for (auto &th : threads) th.join();

        size_t total_size = 0;
        for (auto &vec : local_positions) total_size += vec.size();

        std::vector<size_t> positions;
        positions.reserve(total_size);

        for (auto &vec : local_positions)
            positions.insert(positions.end(),
                             std::make_move_iterator(vec.begin()),
                             std::make_move_iterator(vec.end()));

        std::cout << "Titles in range 1970–1999 (MIMD selection): " << positions.size() << "\n";
    }
}
