#include <thread>
#include <iostream>
#include <vector>
#include "../soa_table_defs/keyword.hpp"

using namespace std;

class thread_for_array
{
private:
    vector<int64_t> _sampleArray;
    int64_t _threadCount;

    void loadSampleArray(const keyword_space::keyword_record &keyword_table);
    void processArray();
    void processSubArray(int64_t start, int64_t end, int64_t *result);

public:
    thread_for_array(
        int64_t threadCount = 4) : _threadCount(threadCount)
    {
    }

    void run(const keyword_space::keyword_record &keyword_table);
};