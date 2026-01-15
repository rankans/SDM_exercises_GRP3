#include <iostream>
#include <chrono>
#include "iterator/queries.hpp"
#include "batch/queries.hpp"

#include <set>

using namespace std;

int main()
{
    auto title_table = title_ex6_updated_record::load_from_file("/exercise/imdb/csv/title.csv");
    // auto title_table_aos = titleaos::load_from_file("/exercise/imdb/csv/title.csv");
    auto keyword_table = keyword_ex6_updated_record::load_from_file("/exercise/imdb/csv/keyword.csv");
    // auto keyword_aos = keyword_aos::load_from_file("/exercise/imdb/csv/keyword.csv");
    auto cn_aos_table = company_name::load_from_file("/exercise/imdb/csv/company_name.csv");
    auto cn_soa_table = company_name_ex6_updated_record::load_from_file("/exercise/imdb/csv/company_name.csv");

    // if (!title_table || !keyword_table || !company_table)
    // {
    //     cerr << "Error loading tables: " << "\n";
    //     return 1;
    // }

    auto &title_val = *title_table;
    auto &keyword_val = *keyword_table;
    auto &company_val = *cn_soa_table;
    auto &company_aos = *cn_aos_table;

    exercise6_iterator_queries iterator_query_tables(title_val, keyword_val, company_aos);

    // Lab 6 Iterator MODEL
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto iter = iterator_query_tables.title_in_production_range_iterator(1970, 2000);
        size_t count = 0;
        for (auto it = iter.begin(); it != iter.end(); ++it)
        {
            // cout << "Title: " << *it << "\n";
            ++count;
        }
        auto end = std::chrono::high_resolution_clock::now();
        cout << "Total titles in range (Iterator model): " << count << "\n";
        cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms]\n";
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        auto iter = iterator_query_tables.keyword_iterator();
        std::set<std::string> distinct_keywords;
        for (auto it = iter.begin(); it != iter.end(); ++it)
        {
            // cout << "Keyword: " << *it << "\n"; // optional debug print
            distinct_keywords.insert(*it);
        }
        auto end = std::chrono::high_resolution_clock::now();
        cout << "Total distinct keywords (Iterator model): " << distinct_keywords.size() << "\n";
        cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms]\n";
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        auto iter = iterator_query_tables.name_not_like_iterator();
        size_t count = 0;
        for (auto it = iter.begin(); it != iter.end(); ++it)
        {
            // cout << "Company Name: " << it->name() << "\n"; // optional debug print
            ++count;
        }
        auto end = std::chrono::high_resolution_clock::now();
        cout << "Total companies without 'Group' (Iterator model): " << count << "\n";
        cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms]\n";
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        auto iter = iterator_query_tables.distinct_country_iterator();
        size_t count = 0;
        for (auto it = iter.begin(); it != iter.end(); ++it)
        {
            // cout << "Country Code: " << *it << "\n"; // optional debug print
            ++count;
        }
        auto end = std::chrono::high_resolution_clock::now();
        cout << "Total distinct country codes (Iterator model): " << count << "\n";
        cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms]\n";
    }

    exercise6_batch_queries batch_query_tables(title_val, keyword_val, company_val);

    // Lab 5 Batch model

    {
        auto start = std::chrono::high_resolution_clock::now();
        auto titles = batch_query_tables.title_in_production_range_batch(1970, 2000);
        auto end = std::chrono::high_resolution_clock::now();
        cout << "Titles in the range are (Batch): " << titles.size();
        cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " ms]\n";
        // for(const auto& t : titles){
        //     cout<<t << "\n";
        // }
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        int count_distinct_keyword_batch = batch_query_tables.count_distinct_keyword_batch();
        cout << "Distinct keywords in table keyword are (batch) " << count_distinct_keyword_batch;
        cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " ms]\n";
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        company_name_ex6_updated_record cn_soa_records = batch_query_tables.name_not_like_in_batch();
        // cout << "CN Querues result (batch)" << cn_soa_records;
        cout << "CN Querues result (batch)" << cn_soa_records.size();
        cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " ms]\n";
    }

    return 0;
};