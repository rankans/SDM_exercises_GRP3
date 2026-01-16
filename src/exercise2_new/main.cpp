#include <iostream>
#include <chrono>
#include "queries.hpp"


int main() {
    // Load tables
    auto title_table = titleaos::load_from_file("/exercise/imdb/csv/title.csv");
    auto keyword_table = keyword_aos::load_from_file("/exercise/imdb/csv/keyword.csv");
    auto company_table = company_name::load_from_file("/exercise/imdb/csv/company_name.csv");

    if (!title_table || !keyword_table || !company_table) {
        std::cerr << "Error loading one or more CSV files.\n";
        return 1;
    }

    auto &titles = *title_table;
    auto &keywords = *keyword_table;
    auto &companies = *company_table;

    std::cout << "Loaded " << titles.records().size() << " title records.\n";
    std::cout << "Loaded " << keywords.records().size() << " keyword records.\n";
    std::cout << "Loaded " << companies.records().size() << " company records.\n\n";

    // Lab 2 queries
    queries_blueprint query_tables(titles, keywords, companies);

    // 1. Titles produced between 1970 and 1999
    auto start = std::chrono::high_resolution_clock::now();
    auto titles_in_range = query_tables.title_in_production_range(1970, 2000);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Titles produced between 1970 and 1999: " << titles_in_range.size()
              << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms]\n";

    // 2. Distinct country codes
    start = std::chrono::high_resolution_clock::now();
    auto distinct_countries = query_tables.distinct_country_code();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Distinct country codes in company_name: " << distinct_countries.size()
              << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms]\n";

    // 3. Count distinct keywords
    start = std::chrono::high_resolution_clock::now();
    int distinct_keyword_count = query_tables.count_distinct_keyword();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Distinct keywords: " << distinct_keyword_count
              << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms]\n";

    // 4. Companies without 'Group' in name
    start = std::chrono::high_resolution_clock::now();
    auto companies_not_group = query_tables.name_not_like();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Companies without 'Group' in name: " << companies_not_group.size()
              << " [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms]\n";

    return 0;
}
