#include <iostream>
#include "company_name.hpp"
#include <set>

// --- Added for Lab 2 (SoA tables and queries) ---
#include "title.hpp"
#include "keyword.hpp"
#include "queries.hpp"
#include <chrono> // For performance measurement
// --- End of additions ---

int main()
{
    // ------------------------
    // Load company_name table
    // ------------------------
    auto cn = company_name::load_from_file("/exercise/imdb/csv/company_name.csv");
    if (!cn)
    {
        std::cerr << "Error loading company_name.csv: " << cn.error() << "\n";
        return 1;
    }
    std::cout << "Loaded " << (*cn).records().size() << " records from company_name.csv\n";

    // Existing Lab 1 query: COUNT(*) WHERE country_code LIKE '[us]'
    int count = 0;
    for (auto const &record : (*cn).records())
    {
        if (record.country_code().compare("[us]") == 0)
        {
            ++count;
        }
    }
    std::cout << "Count of records with country_code LIKE '[us]': " << count
              << " (should be 138946)\n";

    // ------------------------
    // Load title and keyword tables (SoA)
    // ------------------------
    auto title_table = title::load_from_file("/exercise/imdb/csv/title.csv");
    if (!title_table)
    {
        std::cerr << "Error loading title.csv: " << title_table.error() << "\n";
        return 1;
    }
    std::cout << "Loaded " << (*title_table).size() << " records from title.csv\n";

    auto keyword_table = keyword::load_from_file("/exercise/imdb/csv/keyword.csv");
    if (!keyword_table)
    {
        std::cerr << "Error loading keyword.csv: " << keyword_table.error() << "\n";
        return 1;
    }
    std::cout << "Loaded " << (*keyword_table).size() << " records from keyword.csv\n";

    // ------------------------
    // Part 2: Tuple-at-a-time queries
    // ------------------------

    // Query 1: Titles from 1970 <= production_year < 2000
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto titles_70_99 = select_titles_in_year_range(*title_table, 1970, 2000);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Query 1: Titles from 1970 to 1999: " << titles_70_99.size()
                  << " | Time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms\n";
    }

    // Query 2: Distinct country codes
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto countries = distinct_country_codes(*cn);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Query 2: Distinct country codes: " << countries.size()
                  << " | Time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms\n";
    }

    // Query 3: Count distinct keywords
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto keyword_count = count_distinct_keywords(*keyword_table);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Query 3: Distinct keywords: " << keyword_count
                  << " | Time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms\n";
    }

    // Query 4: Companies NOT containing 'Group'
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto companies_filtered = companies_not_like_group(*cn);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Query 4: Companies NOT containing 'Group': " << companies_filtered.size()
                  << " | Time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms\n";
    }

    return 0;
}