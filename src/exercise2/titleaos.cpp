#include <iostream>
#include <fstream>
#include <stdexcept>
#include "utils.hpp"
#include "titleaos.hpp"

using namespace std;

title_aos_record::title_aos_record(
            int64_t id ,
            string title ,
            string imdb_index ,
            int64_t kind_id ,
            int64_t production_year ,
            int64_t imdb_id ,
            string phonetic_code ,
            int64_t episode_of_id ,
            int64_t season_nr ,
            int64_t episode_nr ,
            string series_years ,
            string md5sum
        ): _id(id),
        _title(move(title)),
        _imdb_index(move(imdb_index)),
        _kind_id(kind_id),
        _production_year(production_year),
        _imdb_id(imdb_id),
        _phonetic_code(move(phonetic_code)),
        _episode_of_id(episode_of_id),
        _season_nr(season_nr),
        _episode_nr(episode_nr),
        _series_years(move(series_years)),
        _md5sum(move(md5sum)){}

expected<title_aos_record, csv::err_t> title_aos_record::load_from_row(string_view row, char delim) {
    auto fields_exp = csv::split_line(row, 13, delim);
    if (!fields_exp) {
        return unexpected(fields_exp.error());
    }
    auto& f = *fields_exp;
    auto id     = csv::from_field<int64_t>(f[0]);
    auto kind_id = csv::from_field<int64_t>(f[3]);
    auto production_year = csv::from_field<int64_t>(f[4]);
    auto imdb_id   = csv::from_field<int64_t>(f[5]);
    auto episode_of_id = csv::from_field<int64_t>(f[7]);
    auto season_nr   = csv::from_field<int64_t>(f[8]);
    auto episode_nr   = csv::from_field<int64_t>(f[9]);

    if (!(id && kind_id && production_year && imdb_id && episode_of_id && season_nr && episode_nr )) {
        return unexpected("There is at least 1 error field");
    }

    return title_aos_record{
        *id,
        f[1],
        f[2],
        *kind_id,
        *production_year,
        *imdb_id,
        f[6],
        *episode_of_id,
        *season_nr,
        *episode_nr,
        f[10],
        f[11]
    };
}

expected<titleaos, csv::err_t> titleaos::load_from_file(string_view filePath, char delim) {
    ifstream file{string(filePath)};
    if(!file.is_open()){
        return unexpected("Unexpected error while opening file");
    }
    titleaos titleaos_record;
    auto& record = titleaos_record._records;
    string line;
    size_t line_number = 1;
    while (getline(file, line)) {
        auto record_exp = record_type::load_from_row(line, delim);
        if (!record_exp) {
            return unexpected("Error parsing line " + to_string(line_number) + ": " + record_exp.error());
        }
        record.push_back(*record_exp);
        ++line_number;
    }

    return titleaos_record;
}
