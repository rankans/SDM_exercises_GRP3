#include <iostream>
#include <chrono>
#include "thread_execution_ran.hpp"
#include "title_thread_exec.hpp"

#include <set>

using namespace std;

int main()
{
    auto title_table = title_record::load_from_file("/exercise/imdb/csv/title.csv");
    auto keyword_table = keyword_record::load_from_file("/exercise/imdb/csv/keyword.csv");

    auto &title_val = *title_table;
    auto &keyword_val = *keyword_table;

    // thread processing

    thread_for_array processor(4);
    processor.run(keyword_val);

    title_thread processor_title(4);
    processor_title.runQuery(title_val, 1970, 2000);

    return 0;
};