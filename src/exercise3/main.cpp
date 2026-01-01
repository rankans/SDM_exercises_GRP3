#include <iostream>
#include <chrono>
#include "company_name.hpp"
#include "title.hpp"
#include "keyword.hpp"
#include "queries.hpp"

using namespace std;

int main() {
    // Load tables
    auto title_table = title_space::title_record::load_from_file("/exercise/imdb/csv/title.csv");
    auto keyword_table = keyword_space::keyword_record::load_from_file("/exercise/imdb/csv/keyword.csv");
    auto company_table = company_name::load_from_file("/exercise/imdb/csv/company_name.csv");

    if (!title_table || !keyword_table || !company_table) {
        cerr << "Error loading one or more CSV files.\n";
        return 1;
    }

    auto &titles = *title_table;
    auto &keywords = *keyword_table;
    auto &companies = *company_table;

    cout << "Loaded " << titles.size() << " title records.\n";
    cout << "Loaded " << keywords.size() << " keyword records.\n";
    cout << "Loaded " << companies.records().size() << " company records.\n\n";

    // Lab 2 queries
    queries_blueprint query_tables(titles, keywords, companies);

    // 1. Titles produced between 1970 and 1999
    auto start = chrono::high_resolution_clock::now();
    auto titles_in_range = query_tables.title_in_production_range(1970, 2000);
    auto end = chrono::high_resolution_clock::now();
    cout << "Titles produced between 1970 and 1999: " << titles_in_range.size()
         << " [" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms]\n";

    // 2. Distinct country codes
    start = chrono::high_resolution_clock::now();
    auto distinct_countries = query_tables.distinct_country_code();
    end = chrono::high_resolution_clock::now();
    cout << "Distinct country codes in company_name: " << distinct_countries.size()
         << " [" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms]\n";

    // 3. Count distinct keywords
    start = chrono::high_resolution_clock::now();
    int distinct_keyword_count = query_tables.count_distinct_keyword();
    end = chrono::high_resolution_clock::now();
    cout << "Distinct keywords: " << distinct_keyword_count
         << " [" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms]\n";

    // 4. Companies without 'Group' in name
    start = chrono::high_resolution_clock::now();
    auto companies_not_group = query_tables.name_not_like();
    end = chrono::high_resolution_clock::now();
    cout << "Companies without 'Group' in name: " << companies_not_group.size()
         << " [" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms]\n";

    // --- Lab 3 updates ---
    auto &modified_keywords = query_tables.replace_keyword();
    auto &modified_titles = query_tables.replace_production_date();

    // --- Count total changes ---
    int keyword_updates = 0;
    for (const auto &kw : modified_keywords.keyword()) {
        if (kw == "fiftyisoldchangedisnew") keyword_updates++;
    }

    int title_updates = 0;
    for (size_t i = 0; i < modified_titles.size(); ++i) {
        if (modified_titles.production_year()[i] == 2069) title_updates++;
    }

    cout << "\nLab 3 verification:\n";
    cout << "Total keyword updates: " << keyword_updates << "\n";
    cout << "Total title updates:   " << title_updates << "\n";

    return 0;
}
