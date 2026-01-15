#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "queries.hpp"
#include "commons/utils.hpp"

vector<string> exercise6_batch_queries::title_in_production_range_batch(int year_start, int year_end) const
{
    vector<string> titles;
    size_t cursor = 0;

    while (true)
    {
        title_ex6_updated_record::batch b = title_table.next_batch(cursor);
        if (b.start_index >= b.end_index)
            break; // No more batches to process

        // process the current batch
        for (size_t i = b.start_index; i < b.end_index; ++i)
        {
            if (title_table.production_year()[i] < year_end && title_table.production_year()[i] >= year_start)
            {
                titles.push_back(title_table.title()[i]);
            }
        }
    }
    return titles;
}

// SELECT distinct country_code FROM company_name
// set<string> distinct_country_code_batch(){

// }

// SELECT count(distinct keyword) FROM keyword
int exercise6_batch_queries::count_distinct_keyword_batch() const
{
    size_t cursor = 0;
    set<string> distinct_keywords;

    while (true)
    {
        keyword_ex6_updated_record::batch b = keyword_table.next_batch(cursor);
        if (b.start_index >= b.end_index)
            break; // No more batches to process

        // process the current batch
        for (size_t i = b.start_index; i < b.end_index; ++i)
        {
            distinct_keywords.insert(keyword_table.keyword()[i]);
        }
    }
    return distinct_keywords.size();
}

// // SELECT * FROM company_name WHERE name not like '%Group%'
company_name_ex6_updated_record exercise6_batch_queries::name_not_like_in_batch() const
{
    company_name_ex6_updated_record result; // new SOA table to store filtered rows
    size_t cursor = 0;

    while (true)
    {
        // Get next batch
        auto b = company_name_soa_table.next_batch(cursor);
        if (b.start_index >= b.end_index)
            break;

        // Scan this batch
        for (size_t i = b.start_index; i < b.end_index; ++i)
        {
            const auto &name = company_name_soa_table.name()[i];

            // name NOT LIKE '%Group%'
            if (name.find("Group") == std::string::npos)
            {
                // append the whole row to the new SOA result
                result.append_record(company_name_soa_table, i);
            }
        }
    }

    return result; // filtered SOA table
}
