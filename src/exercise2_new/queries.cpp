#include "queries.hpp"

// SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970
vector<string> queries_blueprint::title_in_production_range(int year_start, int year_end) const {
    vector<string> titles;
    for (size_t i = 0; i < title_table.size(); ++i) {
        if (title_table.production_year()[i] < year_end && title_table.production_year()[i] >= year_start) {
            titles.push_back(title_table.title()[i]);
        }
    }
    return titles;
}

// SELECT distinct country_code FROM company_name
set<string> queries_blueprint::distinct_country_code() const {
    set<string> country_codes;
    for (size_t i = 0; i < company_table.records().size(); ++i) {
        country_codes.insert(company_table.records()[i].country_code());
    }
    return country_codes;
}

// SELECT count(distinct keyword) FROM keyword
int queries_blueprint::count_distinct_keyword() const {
    set<string> distinct_keywords;
    for (size_t i = 0; i < keyword_table.size(); ++i) {
        distinct_keywords.insert(keyword_table.keyword()[i]);
    }
    return distinct_keywords.size();
}

// SELECT * FROM company_name WHERE name not like '%Group%'
vector<company_name_record> queries_blueprint::name_not_like() const {
    vector<company_name_record> result;
    for (size_t i = 0; i < company_table.records().size(); ++i) {
        if (company_table.records()[i].name().find("Group") == string::npos) {
            result.push_back(company_table.records()[i]);
        }
    }
    return result;
}
