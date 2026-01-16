#include "queries.hpp"

// SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970
std::vector<std::string> queries_blueprint::title_in_production_range(int year_start, int year_end) const {
    std::vector<std::string> titles;
    for (const auto &record : title_table.records()) {
        if (record.production_year() < year_end && record.production_year() >= year_start) {
            titles.push_back(record.title());
        }
    }
    return titles;
}

// SELECT distinct country_code FROM company_name
std::set<std::string> queries_blueprint::distinct_country_code() const {
    std::set<std::string> country_codes;
    for (const auto &record : company_table.records()) {
        country_codes.insert(record.country_code());
    }
    return country_codes;
}

// SELECT count(distinct keyword) FROM keyword
int queries_blueprint::count_distinct_keyword() const {
    std::set<std::string> distinct_keywords;
    for (const auto &record : keyword_table.records()) {
        distinct_keywords.insert(record.keyword());
    }
    return distinct_keywords.size();
}

// SELECT * FROM company_name WHERE name not like '%Group%'
std::vector<company_name_record> queries_blueprint::name_not_like() const {
    std::vector<company_name_record> result;
    for (const auto &record : company_table.records()) {
        if (record.name().find("Group") == std::string::npos) {
            result.push_back(record);
        }
    }
    return result;
}
