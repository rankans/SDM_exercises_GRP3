#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "title.hpp"
#include "keyword.hpp"
#include "company_name.hpp"

using namespace std;

class queries_blueprint {
private:
    title_space::title_record const &title_table;
    keyword_space::keyword_record const &keyword_table;
    company_name const &company_table;

public:
    queries_blueprint(
        const title_space::title_record &t,
        const keyword_space::keyword_record &k,
        const company_name &c)
        : title_table(t), keyword_table(k), company_table(c) {}

    // Lab 2 queries
    vector<string> title_in_production_range(int year_start, int year_end) const;
    set<string> distinct_country_code() const;
    int count_distinct_keyword() const;
    vector<company_name_record> name_not_like() const;
};
