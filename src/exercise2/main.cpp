#include <iostream>
#include <chrono>
#include "company_name.hpp"
#include "title.hpp"
#include "keyword.hpp"
#include "queries.hpp"
#include "company_name_SoA.hpp"
#include <set>

using namespace std;

int main()
{
    auto title_table = title_space::title_record::load_from_file("/exercise/imdb/csv/title.csv");
    auto keyword_table = keyword_space::keyword_record::load_from_file("/exercise/imdb/csv/keyword.csv");
    auto company_table = company_name::load_from_file("/exercise/imdb/csv/company_name.csv");
    // auto company_table = company_name_records::load_from_file("/exercise/imdb/csv/company_name.csv");
    if (!title_table || !keyword_table || !company_table)
    {
        cerr << "Error loading tables: " << "\n";
        return 1;
    }

    auto &title_val = *title_table;
    auto &keyword_val = *keyword_table;
    auto &company_val = *company_table;

    cout << "Loaded " << title_val.size() << " records title table.";
    cout << "\nLoaded " << keyword_val.size() << " records keyword table.";
    cout << "\nLoaded " << company_val.records().size() << " records company table.\n\n\n";

    // title_val.print_record(1);
    // keyword_val.print_record(1);
    // cout<< company_val.records()[1];

    // Lab 2 class calls
    queries_blueprint query_tables(title_val, keyword_val, company_val);
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto titles = query_tables.title_in_production_range(1970, 2000);
        auto end = std::chrono::high_resolution_clock::now();
        cout << "Titles in the range are: " << titles.size();
        cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " ms]\n";
        // for(const auto& t : titles){
        //     cout<<t << "\n";
        // }
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        auto distinct_country_codes = query_tables.dictinct_country_code();
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
        int count_distinct_keyword = query_tables.count_distinct_keyword();
        cout << "Distinct keywords in table keyword are " << count_distinct_keyword;
        cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " ms]\n";
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        auto name_not_like = query_tables.name_not_like();
        auto end = std::chrono::high_resolution_clock::now();
        cout << "Number of names not like group are: " << name_not_like.size();
        cout << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << " ms]\n";
        // for(const auto& t : name_not_like){
        //     cout<<t << "\n";
        // }
    }

    // Lab 3
    auto modified_keyword = query_tables.replace_keyword();
    for (size_t i = 0; i < modified_keyword.size(); ++i)
    {
        if (modified_keyword.keyword()[i].find("fiftyisoldchangedisnew") != string::npos)
            modified_keyword.print_record(i);
    }

    // auto modified_title = query_tables.replace_production_date();
    // for(size_t i=0; i<modified_title.size(); ++i){ //set it to a lower number of record for testing otherwise it just keeps showing everything
    //     if(modified_title.production_year()[i] == 2069) modified_title.print_record(i);
    // }

    // Lab 4

    return 0;
}