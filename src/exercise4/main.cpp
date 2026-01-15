#include <iostream>
#include <chrono>
#include <exercise4/queries.hpp>

#include <set>

using namespace std;

int main()
{
    auto title_table = title_record::load_from_file("/exercise/imdb/csv/title.csv");
    auto keyword_table = keyword_record::load_from_file("/exercise/imdb/csv/keyword.csv");
    auto cn_soa = company_name_soa_record::load_from_file("/exercise/imdb/csv/company_name.csv");

    auto &title_val = *title_table;
    auto &keyword_val = *keyword_table;
    auto &cn_soa_val = *cn_soa;

    exercise4_queries exercise4_query_table(title_val, keyword_val, cn_soa_val);

    // Lab 4
    //// SELECT title FROM title WHERE production_year = (SELECT max(production_year) FROM title)
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto title_max_production_year = exercise4_query_table.max_production_year();
        auto end = std::chrono::high_resolution_clock::now();
        cout << "SELECT title FROM title WHERE production_year = (SELECT max(production_year) FROM title) : " << title_max_production_year.size();
        cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " ms]\n";
        // for (auto &rec : title_max_production_year)
        // {
        //     cout << rec << '\n';
        // }
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        auto titles = exercise4_query_table.title_in_production_range(1970, 2000);
        auto end = std::chrono::high_resolution_clock::now();
        cout << "Titles in the range are (Linear access): " << titles.size();
        cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " ms]\n";
        // for(const auto& t : titles){
        //     cout<<t << "\n";
        // }
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        auto distinct_country_codes = exercise4_query_table.distinct_country_code();
        auto end = std::chrono::high_resolution_clock::now();
        cout << "Number of distinct country codes are: " << distinct_country_codes.size();
        cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " ms]\n";

        // for(const auto& t : distinct_country_codes){
        //     cout<<t << "\n";
        // }
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        int count_distinct_keyword = exercise4_query_table.count_distinct_keyword();
        cout << "Distinct keywords in table keyword are(Linear access) " << count_distinct_keyword;
        cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " ms]\n";
    }

    return 0;
}