#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "title.hpp"
#include "keyword.hpp"
#include "company_name.hpp"

using namespace std;

class queries_blueprint
{
private:
    // title_space::title_record const& title_table;
    title_space::title_record title_table; // title also needs to change
    // keyword_space::keyword_record const& keyword_table;
    keyword_space::keyword_record keyword_table; // for lab 3 we need to modify the original value
    company_name const &company_table;

public:
    queries_blueprint(
        // const title_space::title_record& t,
        title_space::title_record &t, // title also need to change
        // const keyword_space::keyword_record& k,
        keyword_space::keyword_record &k, // for lab 3 we need to modify the original table
        const company_name &c) : title_table(t),
                                 keyword_table(k),
                                 company_table(c)
    {
    }

    // // SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970
    // vector<string> title_in_production_range(int year_start, int year_end) const;

    // // SELECT distinct country_code FROM company_name
    // set<string> dictinct_country_code() const;

    // // SELECT count(distinct keyword) FROM keyword
    // int count_distinct_keyword() const;

    // // SELECT * FROM company_name WHERE name not like '%Group%'
    // vector<company_name_record> name_not_like() const;

    // Lab 3

    keyword_space::keyword_record &replace_keyword();

    title_space::title_record &replace_production_date();

    // Lab 4 (actually lab 2 as we flipped the implementations)

    // SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970
    vector<string> title_in_production_range(int year_start, int year_end) const;

    // SELECT distinct country_code FROM company_name
    set<string> dictinct_country_code() const;

    // SELECT count(distinct keyword) FROM keyword
    int count_distinct_keyword() const;

    // SELECT * FROM company_name WHERE name not like '%Group%'
    vector<company_name_record> name_not_like() const;
};