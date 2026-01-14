#include "title_thread_exec.hpp"

void title_thread::runQuery(const title_space::title_record &title_table,
                            int64_t year_start,
                            int64_t year_end)
{
    processQuery(title_table, year_start, year_end);
}

void title_thread::processQuery(const title_space::title_record &title_table,
                                int64_t year_start,
                                int64_t year_end)
{
    const size_t n = title_table.size();
    if (n == 0)
        return;

    _threadCount = std::max<int64_t>(1, std::min<int64_t>(_threadCount, (int64_t)n));

    const auto &years = title_table.production_year();
    // const auto &titles = title_table.title();

    const size_t chunk_size = n / (size_t)_threadCount;

    std::vector<std::thread> threads;
    threads.reserve((size_t)_threadCount);

    std::vector<std::vector<size_t>> thread_positions((size_t)_threadCount);

    for (int64_t t = 0; t < _threadCount; ++t)
    {
        const size_t start = (size_t)t * chunk_size;
        const size_t end = (t == _threadCount - 1) ? n : start + chunk_size;

        threads.emplace_back(
            &title_thread::processSubFilter,
            this,
            std::cref(years),
            start,
            end,
            year_start,
            year_end,
            &thread_positions[(size_t)t]);
    }

    for (auto &th : threads)
    {
        th.join();
    }

    size_t total_matches = 0;
    size_t i = 0;
    for (const auto &v : thread_positions)
    {
        total_matches += v.size();
        std::cout << "Thread " << i++ << " " << v.size() << " matches. \n";
    }

    std::vector<size_t> positions;
    positions.reserve(total_matches);

    for (auto &v : thread_positions)
    {
        positions.insert(positions.end(), v.begin(), v.end());
    }

    // for (size_t pos : positions) //print function disabled for now
    // {
    //     std::cout << titles[pos] << "\n";
    // }

    std::cout << "Total entries satisfying the conditions are: " << positions.size();
}

void title_thread::processSubFilter(const std::vector<int64_t> &years,
                                    size_t start, size_t end,
                                    int64_t year_start, int64_t year_end,
                                    std::vector<size_t> *out_positions)
{
    out_positions->clear();
    out_positions->reserve((end - start) / 8);

    for (size_t i = start; i < end; ++i)
    {
        int64_t y = years[i];

        if (y >= year_start && y < year_end)
        {
            out_positions->push_back(i);
        }
    }
}