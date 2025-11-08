#include "title.hpp"
#include <fstream>
#include <iostream>

std::expected<title, csv::err_t> title::load_from_file(std::string_view filepath, char delim) {
    std::ifstream file{std::string(filepath)};
    if (!file.is_open()) {
        return std::unexpected("Failed to open file: " + std::string(filepath));
    }

    title t;
    std::string line;
    size_t line_number = 1;

    while (std::getline(file, line)) {
        auto fields_exp = csv::split_line(line, 12, delim);
        if (!fields_exp) {
            return std::unexpected("Error parsing line " + std::to_string(line_number) + ": " + fields_exp.error());
        }
        auto& f = *fields_exp;

        auto id = csv::from_field<int64_t>(f[0]);
        auto kind_id = csv::from_field<int64_t>(f[3]);
        auto production_year = csv::from_field<int64_t>(f[4]);
        auto imdb_id = csv::from_field<int64_t>(f[5]);
        auto episode_of_id = csv::from_field<int64_t>(f[7]);
        auto season_nr = csv::from_field<int64_t>(f[8]);
        auto episode_nr = csv::from_field<int64_t>(f[9]);

        if (!id) return std::unexpected("Invalid id at line " + std::to_string(line_number));
        if (!kind_id) kind_id = 0;
        if (!production_year) production_year = 0;
        if (!imdb_id) imdb_id = 0;
        if (!episode_of_id) episode_of_id = 0;
        if (!season_nr) season_nr = 0;
        if (!episode_nr) episode_nr = 0;

        t.id.push_back(*id);
        t.title_name.push_back(f[1]);
        t.imdb_index.push_back(f[2]);
        t.kind_id.push_back(*kind_id);
        t.production_year.push_back(*production_year);
        t.imdb_id.push_back(*imdb_id);
        t.phonetic_code.push_back(f[6]);
        t.episode_of_id.push_back(*episode_of_id);
        t.season_nr.push_back(*season_nr);
        t.episode_nr.push_back(*episode_nr);
        t.series_years.push_back(f[10]);
        t.md5sum.push_back(f[11]);

        ++line_number;
    }

    return t;
}
