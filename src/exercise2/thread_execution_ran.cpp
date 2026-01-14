#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>
#include "thread_execution_ran.hpp"


void thread_for_array::run(const keyword_space::keyword_record& keyword_table){
    loadSampleArray(keyword_table);
    processArray();
}

void thread_for_array::loadSampleArray(const keyword_space::keyword_record& keyword_table){

    _sampleArray.clear();
    _sampleArray.reserve(keyword_table.size());
    for (size_t i = 0; i < keyword_table.size(); ++i)
    {
        _sampleArray.push_back(keyword_table.id()[i]);
    }
}

void thread_for_array::processArray() {
    if (_sampleArray.empty()) return;

    _threadCount = std::min(_threadCount, (int64_t)_sampleArray.size());

    int64_t arr_size = _sampleArray.size();
    int64_t chunk_size = arr_size / _threadCount;

    std::vector<std::thread> threads;
    std::vector<int64_t> thread_results(_threadCount, 0);

    for (int64_t i = 0; i < _threadCount; ++i) {
        int64_t start = i * chunk_size;
        int64_t end = (i == _threadCount - 1) ? arr_size : start + chunk_size;

        threads.emplace_back(
            &thread_for_array::processSubArray,
            this,
            start,
            end,
            &thread_results[i]
        );
    }

    for (auto& th : threads) {
        th.join();
    }

    int64_t grandTotal = 0;
    for (int64_t i = 0; i < _threadCount; ++i) {
        std::cout << "Thread " << i << " sum: " << thread_results[i] << "\n";
        grandTotal += thread_results[i];
    }

    std::cout << "Grand total: " << grandTotal << "\n";
}

void thread_for_array::processSubArray(int64_t start, int64_t end, int64_t* result){
    int64_t total = 0;

    for(int64_t i=start;i<end;++i){
        if (_sampleArray[i] % 2 == 0) {
            total = total + _sampleArray[i];
        }
    }

    *result = total;
}

