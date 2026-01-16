#pragma once
#include "../aos_table_defs/titleaos.hpp"
#include "../aos_table_defs/keywordaos.hpp"
#include <vector>
#include <string>

// Wrapper class to modify keyword table safely
class mod_keyword_table {
private:
    std::vector<std::string> _keywords;

public:
    mod_keyword_table(const keyword_aos &orig) {
        for (const auto &rec : orig.records()) {
            _keywords.push_back(rec.keyword());
        }
    }

    size_t size() const { return _keywords.size(); }
    const std::string &keyword(size_t i) const { return _keywords[i]; }

    void set_keyword(size_t i, const std::string &val) { _keywords[i] = val; }
    const std::vector<std::string> &all_keywords() const { return _keywords; }
};

// Wrapper class to modify title table safely
class mod_title_table {
private:
    std::vector<int> _production_years;
    std::vector<std::string> _titles;

public:
    mod_title_table(const titleaos &orig) {
        for (const auto &rec : orig.records()) {
            _titles.push_back(rec.title());
            _production_years.push_back(rec.production_year());
        }
    }

    size_t size() const { return _titles.size(); }
    int production_year(size_t i) const { return _production_years[i]; }
    const std::string &title(size_t i) const { return _titles[i]; }

    void set_production_year(size_t i, int val) { _production_years[i] = val; }

    const std::vector<int> &all_years() const { return _production_years; }
    const std::vector<std::string> &all_titles() const { return _titles; }
};
