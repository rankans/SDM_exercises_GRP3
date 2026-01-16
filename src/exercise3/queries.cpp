#include "queries.hpp"

// Lab 2 queries
vector<string> queries_blueprint::title_in_production_range(int year_start, int year_end) const {
    vector<string> titles;
    for (size_t i = 0; i < title_table.size(); ++i) {
        if (title_table.production_year(i) < year_end && title_table.production_year(i) >= year_start) {
            titles.push_back(title_table.title(i));
        }
    }
    return titles;
}

set<string> queries_blueprint::distinct_country_code() const {
    set<string> country_codes;
    for (const auto &record : company_table.records()) {
        country_codes.insert(record.country_code());
    }
    return country_codes;
}

int queries_blueprint::count_distinct_keyword() const {
    set<string> distinct_keywords;
    for (size_t i = 0; i < keyword_table.size(); ++i) {
        distinct_keywords.insert(keyword_table.keyword(i));
    }
    return distinct_keywords.size();
}

vector<company_name_record> queries_blueprint::name_not_like() const {
    vector<company_name_record> result;
    for (const auto &record : company_table.records()) {
        if (record.name().find("Group") == string::npos) result.push_back(record);
    }
    return result;
}

// Lab 3 updates
mod_keyword_table &queries_blueprint::replace_keyword() {
    for (size_t i = 0; i < keyword_table.size(); ++i) {
        if (keyword_table.keyword(i).find("fifty") != string::npos) {
            keyword_table.set_keyword(i, "fiftyisoldchangedisnew");
        }
    }
    return keyword_table;
}

mod_title_table &queries_blueprint::replace_production_date() {
    for (size_t i = 0; i < title_table.size(); ++i) {
        int year = title_table.production_year(i);
        if (year == 1996 || year == 1967 || year == 1990 || year == 2000) {
            title_table.set_production_year(i, 2069);
        }
    }
    return title_table;
}
