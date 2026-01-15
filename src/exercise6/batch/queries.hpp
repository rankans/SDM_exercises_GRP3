#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "../soa_tables_updated/title.hpp"
#include "../soa_tables_updated/keyword.hpp"
#include "../soa_tables_updated/company_name_soa.hpp"

using namespace std;

class exercise6_batch_queries
{

private:
    title_ex6_updated_record title_table;
    keyword_ex6_updated_record keyword_table;
    company_name_ex6_updated_record const &company_name_soa_table;

public:
    exercise6_batch_queries(
        const title_ex6_updated_record &t,
        const keyword_ex6_updated_record &k,
        const company_name_ex6_updated_record &cn_soa)
        : title_table(t),
          keyword_table(k),
          company_name_soa_table(cn_soa)
    {
    }

    // SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970
    vector<string> title_in_production_range_batch(int year_start, int year_end) const;
    // SELECT distinct country_code FROM company_name
    set<string> distinct_country_code_batch() const;

    // SELECT count(distinct keyword) FROM keyword
    int count_distinct_keyword_batch() const;

    // SELECT * FROM company_name WHERE name not like '%Group%'
    company_name_ex6_updated_record name_not_like_in_batch() const;
};