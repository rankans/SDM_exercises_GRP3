#pragma once
#include <vector>
#include <set>
#include "mod_tables.hpp"
#include "../aos_table_defs/company_name.hpp"

using namespace std;

class queries_blueprint {
private:
    mod_title_table title_table;
    mod_keyword_table keyword_table;
    const company_name &company_table; // still const, not modified

public:
    queries_blueprint(const titleaos &t, const keyword_aos &k, const company_name &c)
        : title_table(t), keyword_table(k), company_table(c) {}

    // Lab 2 queries
    vector<string> title_in_production_range(int year_start, int year_end) const;
    set<string> distinct_country_code() const;
    int count_distinct_keyword() const;
    vector<company_name_record> name_not_like() const;

    // Lab 3 updates
    mod_keyword_table &replace_keyword();
    mod_title_table &replace_production_date();
};
