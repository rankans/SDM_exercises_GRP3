#include <iostream>
#include <fstream>
#include <stdexcept>

#include "title.hpp"
#include "utils.hpp"

using namespace std;
using namespace title_space;

expected<title_record, csv::err_t> title_record::load_from_file(string_view filePath, char delim='|'){
    ifstream file{string(filePath)};
    if(!file.is_open()){
        return unexpected("Unexpected error while opening file");
    }

    title_record table;
    string row;
    size_t row_number = 1;

    while(getline(file, row)){
        auto field_exp = csv::split_line(row, 12, delim);
        if(!field_exp){
            return unexpected("could not load field");
        }

        auto& f = *field_exp;

        auto  id = csv::from_field<int64_t>(f[0]);
        auto title = csv::from_field<string>(f[1]);
        auto imdb_index = csv::from_field<string>(f[2]);
        auto  kind_id = csv::from_field<int64_t>(f[3]);
        auto  production_year = csv::from_field<int64_t>(f[4]);
        auto  imdb_id = csv::from_field<int>(f[5]);
        auto phonetic_code = csv::from_field<string>(f[6]);
        auto  episode_of_id = csv::from_field<int64_t>(f[7]);
        auto  season_nr = csv::from_field<int64_t>(f[8]);
        auto episode_nr = csv::from_field<int64_t>(f[9]);
        auto series_years = csv::from_field<string>(f[10]);
        auto md5sum = csv::from_field<string>(f[11]);

        table._id.push_back(*id);
        table._title.push_back(*title);
        table._imdb_index.push_back(*imdb_index);
        table._kind_id.push_back(*kind_id);
        table._production_year.push_back(*production_year);
        table._imdb_id.push_back(*imdb_id);
        table._phonetic_code.push_back(*phonetic_code);
        table._episode_of_id.push_back(*episode_of_id);
        table._season_nr.push_back(*season_nr);
        table._episode_nr.push_back(*episode_nr);
        table._series_years.push_back(*series_years);
        table._md5sum.push_back(*md5sum);
    }
    return table;

}