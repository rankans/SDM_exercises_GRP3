#include <iostream>
#include <chrono>
#include "../aos_table_defs/company_name.hpp"
#include "../aos_table_defs/titleaos.hpp"
#include "../aos_table_defs/keywordaos.hpp"
#include "queries.hpp"

using namespace std;

int main() {
    auto title_table = titleaos::load_from_file("/exercise/imdb/csv/title.csv");
    auto keyword_table = keyword_aos::load_from_file("/exercise/imdb/csv/keyword.csv");
    auto company_table = company_name::load_from_file("/exercise/imdb/csv/company_name.csv");

    if (!title_table || !keyword_table || !company_table) {
        cerr << "Error loading CSV files\n";
        return 1;
    }

    queries_blueprint query_tables(*title_table, *keyword_table, *company_table);

    // --- Lab 2 ---
    auto titles_in_range = query_tables.title_in_production_range(1970, 2000);
    auto distinct_countries = query_tables.distinct_country_code();
    int distinct_keywords = query_tables.count_distinct_keyword();
    auto companies_not_group = query_tables.name_not_like();

    cout << "Titles in range: " << titles_in_range.size() << "\n";
    cout << "Distinct countries: " << distinct_countries.size() << "\n";
    cout << "Distinct keywords: " << distinct_keywords << "\n";
    cout << "Companies without 'Group': " << companies_not_group.size() << "\n";

    // --- Lab 3 ---
    auto &modified_keywords = query_tables.replace_keyword();
    auto &modified_titles = query_tables.replace_production_date();

    // verification
    int keyword_updates = 0;
    for (const auto &kw : modified_keywords.all_keywords()) {
        if (kw == "fiftyisoldchangedisnew") keyword_updates++;
    }

    int title_updates = 0;
    for (const auto &y : modified_titles.all_years()) {
        if (y == 2069) title_updates++;
    }

    cout << "Lab 3 keyword updates: " << keyword_updates << "\n";
    cout << "Lab 3 title updates: " << title_updates << "\n";

    return 0;
}
