#include "queries.hpp"

vector<string> exercise4_queries::max_production_year() const
{
    vector<string> title;
    int64_t max_year = 0;
    for (const auto &production_year : title_table.production_year())
    {
        max_year = max(max_year, production_year);
    }

    for (size_t i = 0; i < title_table.size(); i++)
    {
        if (title_table.production_year()[i] == max_year)
        {
            title.push_back(title_table.title()[i]);
        }
    }
    return title;
}

// SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970
vector<string> exercise4_queries::title_in_production_range(int year_start, int year_end) const
{
    vector<string> titles;
    for (size_t i = 0; i < title_table.size(); ++i)
    {
        if (title_table.production_year()[i] < year_end && title_table.production_year()[i] >= year_start)
        {
            titles.push_back(title_table.title()[i]);
        }
    }
    return titles;
}

// SELECT distinct country_code FROM company_name
set<string> exercise4_queries::distinct_country_code() const
{
    set<string> country_codes;
    for (size_t i = 0; i < company_name_soa_table.size(); ++i)
    {
        country_codes.insert(company_name_soa_table.country_code()[i]);
    }
    return country_codes;
}

// SELECT count(distinct keyword) FROM keyword
int exercise4_queries::count_distinct_keyword() const
{
    set<string> distinct_keyword;
    for (size_t i = 0; i < keyword_table.size(); ++i)
    {
        distinct_keyword.insert(keyword_table.keyword()[i]);
    }
    return distinct_keyword.size();
}
