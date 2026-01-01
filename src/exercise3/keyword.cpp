#include <iostream>
#include <fstream>
#include <stdexcept>

#include "keyword.hpp"
#include "utils.hpp"

using namespace std;
using namespace keyword_space;

expected<keyword_record, csv::err_t> keyword_record::load_from_file(string_view filePath, char delim){
    ifstream file{string(filePath)};
    if(!file.is_open()){
        return unexpected("Unexpected error while opening file");
    }

    keyword_record table;
    string row;

    while(getline(file,row)){
        auto field_exp = csv::split_line(row, 4, delim);
        if(!field_exp){
            return unexpected("could not split field");
        }

        auto& f = *field_exp;

        auto id = csv::from_field<int64_t>(f[0]);
        auto keyword = csv::from_field<string>(f[1]);
        auto phonetic_code = csv::from_field<string>(f[2]);

        table._id.push_back(*id);
        table._keyword.push_back(*keyword);
        table._phonetic_code.push_back(*keyword);
    }
    return table;

}