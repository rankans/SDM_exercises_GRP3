#include "queries.hpp"

// Query 1: Titles from 1970 <= year < 2000
std::vector<std::string> select_titles_in_year_range(title const& t, int start_year, int end_year) {
    std::vector<std::string> result;
    for (size_t i = 0; i < t.size(); ++i) {
        if (t.production_year[i] >= start_year && t.production_year[i] < end_year) {
            result.push_back(t.title_name[i]);
        }
    }
    return result;
}

// Query 2: Distinct country codes
std::unordered_set<std::string> distinct_country_codes(company_name const& c) {
    std::unordered_set<std::string> codes;
    for (auto const& record : c.records()) {
        codes.insert(record.country_code());
    }
    return codes;
}

// Query 3: Count distinct keywords
std::size_t count_distinct_keywords(keyword const& k) {
    std::unordered_set<std::string> unique_keywords;
    for (size_t i = 0; i < k.size(); ++i) {
        unique_keywords.insert(k.keyword_name[i]);
    }
    return unique_keywords.size();
}

// Query 4: Companies NOT containing 'Group'
std::vector<company_name_record> companies_not_like_group(company_name const& c) {
    std::vector<company_name_record> result;
    for (auto const& record : c.records()) {
        if (record.name().find("Group") == std::string::npos) {
            result.push_back(record);
        }
    }
    return result;
}
