#pragma once
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <set>
#include "soa_table_defs/title.hpp"
#include "soa_table_defs/keyword.hpp"
#include "soa_table_defs/company_name_SoA.hpp"

#include "commons/utils.hpp"

using namespace std;

class exercise4_queries
{

private:
    title_record title_table;
    keyword_record const &keyword_table;
    company_name_soa_record const &company_name_soa_table;

public:
    exercise4_queries(
        const title_record &t,
        const keyword_record &k,
        const company_name_soa_record &cn_soa)
        : title_table(t),
          keyword_table(k),
          company_name_soa_table(cn_soa)
    {
    }

    // SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970
    vector<string> title_in_production_range(int year_start, int year_end) const;

    // SELECT distinct country_code FROM company_name
    set<string> distinct_country_code() const;

    // SELECT count(distinct keyword) FROM keyword
    int count_distinct_keyword() const;

    //  SELECT title FROM title WHERE production_year = (SELECT max(production_year) FROM title)
    vector<string> max_production_year() const;
};