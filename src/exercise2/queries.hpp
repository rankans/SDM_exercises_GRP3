#pragma once
#include <vector>
#include <unordered_set> // faster for DISTINCT
#include <string>
#include "company_name.hpp"
#include "title.hpp"
#include "keyword.hpp"

// 1. Titles from production_year 1970 <= year < 2000
std::vector<std::string> select_titles_in_year_range(title const &t, int start_year, int end_year);

// 2. Distinct country codes from company_name
std::unordered_set<std::string> distinct_country_codes(company_name const &c);

// 3. Count distinct keywords from keyword table
std::size_t count_distinct_keywords(keyword const &k);

// 4. All company_name records where name NOT LIKE '%Group%'
std::vector<company_name_record> companies_not_like_group(company_name const &c);