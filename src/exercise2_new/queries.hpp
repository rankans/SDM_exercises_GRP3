#pragma once
#include <vector>
#include <set>
#include "../aos_table_defs/titleaos.hpp"
#include "../aos_table_defs/keywordaos.hpp"
#include "../aos_table_defs/company_name.hpp"
#include "../commons/utils.hpp"

using namespace std;

class queries_blueprint {
private:
    const titleaos &title_table;
    const keyword_aos &keyword_table;
    const company_name &company_table;

public:
    queries_blueprint(
        const titleaos &t,
        const keyword_aos &k,
        const company_name &c)
        : title_table(t), keyword_table(k), company_table(c) {}

    // Lab 2 queries
    std::vector<std::string> title_in_production_range(int year_start, int year_end) const;
    std::set<std::string> distinct_country_code() const;
    int count_distinct_keyword() const;
    std::vector<company_name_record> name_not_like() const;
};
