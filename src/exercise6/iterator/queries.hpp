#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "iterator_structs.hpp"

using namespace std;

class exercise6_iterator_queries
{

private:
    title_ex6_updated_record title_table;
    keyword_ex6_updated_record keyword_table;
    company_name_ex6_updated_record const &company_name_soa_table;

public:
    exercise6_iterator_queries(
        const title_ex6_updated_record &t,
        const keyword_ex6_updated_record &k,
        const company_name_ex6_updated_record &cn_soa)
        : title_table(t),
          keyword_table(k),
          company_name_soa_table(cn_soa)
    {
    }

    // SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970
    TitleInRangeIter title_in_production_range_iterator(int year_start, int year_end) const
    {
        return TitleInRangeIter(title_table, year_start, year_end);
    }

    // SELECT count(distinct keyword) FROM keyword
    KeywordIter keyword_iterator() const { return KeywordIter(keyword_table); }

    // SELECT * FROM company_name WHERE name not like '%Group%'
    NameNotLikeIter name_not_like_iterator() const { return NameNotLikeIter(company_name_soa_table); }

    // SELECT distinct country_code FROM company_name
    DistinctCountryIter distinct_country_iterator() const { return DistinctCountryIter(company_name_soa_table); }
};