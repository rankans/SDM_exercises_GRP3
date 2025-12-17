#include <iostream>
#include <chrono>
#include "company_name.hpp"
#include "title.hpp"
#include "keyword.hpp"
#include "queries.hpp"
#include "titleaos.hpp"
#include "avx2_simd_filter.hpp"
#include "neon_simd_filter.hpp"
#include "mimd_ash.hpp"

#include <set>

using namespace std;

int main()
{
    auto title_table = title_space::title_record::load_from_file("/exercise/imdb/csv/title.csv");
    auto title_table_aos = titleaos::load_from_file("/exercise/imdb/csv/title.csv");
    auto keyword_table = keyword_space::keyword_record::load_from_file("/exercise/imdb/csv/keyword.csv");
    auto keyword_aos = keyword_aos::load_from_file("/exercise/imdb/csv/keyword.csv");
    auto company_table = company_name::load_from_file("/exercise/imdb/csv/company_name.csv");
    auto cn_soa = company_name_soa_record::load_from_file("/exercise/imdb/csv/company_name.csv");

    if (!title_table || !keyword_table || !company_table)
    {
        cerr << "Error loading tables: " << "\n";
        return 1;
    }

    auto &title_val = *title_table;
    auto &keyword_val = *keyword_table;
    auto &company_val = *company_table;
    auto &title_aos_val = *title_table_aos;
    auto &keyword_aos_val = *keyword_aos;
    auto &cn_soa_val = *cn_soa;

    cout << "Loaded " << title_val.size() << " records title table.";
    cout << "\nLoaded " << keyword_val.size() << " records keyword table.";
    cout << "\nLoaded " << company_val.records().size() << " records company table.\n\n\n";

    // title_val.print_record(1);
    // keyword_val.print_record(1);
    // cout<< company_val.records()[1];

    // Lab 2 class calls
    // queries_blueprint query_tables(title_val, keyword_val, company_val, keyword_aos_val, title_aos_val, cn_soa_val);

    // {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto titles = query_tables.title_in_production_range(1970, 2000);
    //     auto end = std::chrono::high_resolution_clock::now();
    //     cout << "Titles in the range are (Linear access): " << titles.size();
    //     cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " ms]\n";
    //     // for(const auto& t : titles){
    //     //     cout<<t << "\n";
    //     // }
    // }

    // // {
    // //     auto start = std::chrono::high_resolution_clock::now();
    // //     auto distinct_country_codes = query_tables.dictinct_country_code();
    // //     auto end = std::chrono::high_resolution_clock::now();
    // //     cout<< "Number of distinct country codes are: " << distinct_country_codes.size();
    // //     cout<<" [" << std::chrono::duration_cast<std::chrono::milliseconds>(end-start)<<" ms]\n";

    // //     // for(const auto& t : distinct_country_codes){
    // //     //     cout<<t << "\n";
    // //     // }
    // // }

    // {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto end = std::chrono::high_resolution_clock::now();
    //     int count_distinct_keyword = query_tables.count_distinct_keyword();
    //     cout << "Distinct keywords in table keyword are(Linear access) " << count_distinct_keyword;
    //     cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " ms]\n";
    // }

    // //Lab 3
    // auto modified_keyword = query_tables.replace_keyword();
    // for(size_t i=0; i<modified_keyword.size(); ++i){
    //     if(modified_keyword.keyword()[i].find("fiftyisoldchangedisnew") != string::npos) modified_keyword.print_record(i);
    // }

    // auto modified_title = query_tables.replace_production_date();
    // for(size_t i=0; i<modified_title.size(); ++i){ //set it to a lower number of record for testing otherwise it just keeps showing everything
    //     if(modified_title.production_year()[i] == 2069) modified_title.print_record(i);
    // }

    // //Lab 4
    // //// SELECT title FROM title WHERE production_year = (SELECT max(production_year) FROM title)
    // {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto title_max_production_year = query_tables.max_production_year();
    //     auto end = std::chrono::high_resolution_clock::now();
    //     cout<< "SELECT title FROM title WHERE production_year = (SELECT max(production_year) FROM title) : " << title_max_production_year.size();
    //     cout<<" [" << std::chrono::duration_cast<std::chrono::milliseconds>(end-start)<<" ms]\n";
    //     // for(auto& rec : title_max_production_year){
    //     //     cout<<rec <<'\n';
    //     // }
    // }

    // //SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970

    // {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto title_aos_in_range = query_tables.title_aos_in_production_range(1970,2000);
    //     auto end = std::chrono::high_resolution_clock::now();
    //     cout<< "SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970: " << title_aos_in_range.size();
    //     cout<<" [" << std::chrono::duration_cast<std::chrono::milliseconds>(end-start)<<" ms]\n";
    //     // for(auto& rec : title_aos_in_range){
    //     //     cout<<rec <<'\n';
    //     // }
    // }

    // {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto name_not_like = query_tables.name_not_like();
    //     auto end = std::chrono::high_resolution_clock::now();
    //     cout<< "SELECT * FROM company_name WHERE name not like '%Group%': " << name_not_like.size();
    //     cout<<" [" << std::chrono::duration_cast<std::chrono::milliseconds>(end-start)<<" ms]\n";
    //     // for(const auto& t : name_not_like){
    //     //     cout<<t << "\n";
    //     // }
    // }

    // // SELECT DISTINCT KEYWORDS
    // int distinct_count = query_tables.count_distinct_keyword2();
    // cout << "Distinct keywords in keyword_table2: " << distinct_count << endl;

    // Lab 5 Batch model

    // {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto titles = query_tables.title_in_production_range_batch(1970, 2000);
    //     auto end = std::chrono::high_resolution_clock::now();
    //     cout << "Titles in the range are (Batch): " << titles.size();
    //     cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " ms]\n";
    //     // for(const auto& t : titles){
    //     //     cout<<t << "\n";
    //     // }
    // }

    // {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto end = std::chrono::high_resolution_clock::now();
    //     int count_distinct_keyword_batch = query_tables.count_distinct_keyword_batch();
    //     cout << "Distinct keywords in table keyword are (batch) " << count_distinct_keyword_batch;
    //     cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " ms]\n";
    // }

    // {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto end = std::chrono::high_resolution_clock::now();
    //     company_name_soa_record cn_soa_records = query_tables.name_not_like_in_batch();
    //     cout << "CN Querues result (batch)" << cn_soa_records;
    //     cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " ms]\n";
    // }

    // // Lab 5 Iterator MODEL
    // {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto iter = query_tables.title_in_production_range_iterator(1970, 2000);
    //     size_t count = 0;
    //     for (auto it = iter.begin(); it != iter.end(); ++it)
    //     {
    //         // cout << "Title: " << *it << "\n";
    //         ++count;
    //     }
    //     auto end = std::chrono::high_resolution_clock::now();
    //     cout << "Total titles in range (Iterator model): " << count << "\n";
    //     cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms]\n";
    // }

    // {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto iter = query_tables.keyword_iterator();
    //     std::set<std::string> distinct_keywords;
    //     for (auto it = iter.begin(); it != iter.end(); ++it)
    //     {
    //         // cout << "Keyword: " << *it << "\n"; // optional debug print
    //         distinct_keywords.insert(*it);
    //     }
    //     auto end = std::chrono::high_resolution_clock::now();
    //     cout << "Total distinct keywords (Iterator model): " << distinct_keywords.size() << "\n";
    //     cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms]\n";
    // }

    // {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto iter = query_tables.name_not_like_iterator();
    //     size_t count = 0;
    //     for (auto it = iter.begin(); it != iter.end(); ++it)
    //     {
    //         // cout << "Company Name: " << it->name() << "\n"; // optional debug print
    //         ++count;
    //     }
    //     auto end = std::chrono::high_resolution_clock::now();
    //     cout << "Total companies without 'Group' (Iterator model): " << count << "\n";
    //     cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms]\n";
    // }

    // {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     auto iter = query_tables.distinct_country_iterator();
    //     size_t count = 0;
    //     for (auto it = iter.begin(); it != iter.end(); ++it)
    //     {
    //         // cout << "Country Code: " << *it << "\n"; // optional debug print
    //         ++count;
    //     }
    //     auto end = std::chrono::high_resolution_clock::now();
    //     cout << "Total distinct country codes (Iterator model): " << count << "\n";
    //     cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms]\n";
    // }

    // Lab 7: SIMD Intel AVX2
    //avx2_simd_filter::avx2_simd_filter_and_print_titles(title_val); // Only works with SIMD in Intel AVX2 ; with scalar builds disabled
    // neon_simd_filter::

    // Lab 7: SIMD Mac Neon
    // auto results = neon_simd_filter::neon_filter_positions(title_val, 1970, 2000);
    // neon_simd_filter::print_titles_from_positions(title_val, results);
    // std::cout << "Titles in range 1970 – 1999 (using SIMD Mac ARM_Neon): " << results.size() << "\n";

    // Lab 8 : MIMD(Thread Parallelism) Intel
    // Task 1: Filter + Aggregation
    mimd_ash::mimd_filter_and_count_titles(title_val);
    // Task 2: Filter + Selection
    mimd_ash::mimd_filter_and_print_titles(title_val);


    return 0;
};