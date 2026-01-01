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
    // Remove 'const' so we can modify the tables in Lab 3
    title_space::title_record &title_table;
    keyword_space::keyword_record &keyword_table;
    company_name &company_table;

public:
    // Constructor must also take non-const references
    queries_blueprint(
        title_space::title_record &t,
        keyword_space::keyword_record &k,
        company_name &c)
        : title_table(t), keyword_table(k), company_table(c) {}

    // Lab 2 queries (can still use const-correct methods)
    vector<string> title_in_production_range(int year_start, int year_end) const;
    set<string> distinct_country_code() const;
    int count_distinct_keyword() const;
    vector<company_name_record> name_not_like() const;

    // Lab 3 updates
    keyword_space::keyword_record &replace_keyword();
    title_space::title_record &replace_production_date();
};
