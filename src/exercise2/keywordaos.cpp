#include <iostream>
#include <fstream>
#include <stdexcept>
#include "keywordaos.hpp"
#include "utils.hpp"

using namespace std;

expected<keyword_aos, csv::err_t> keyword_aos::load_from_file(string_view filepath, char delim) {
    ifstream file{string(filepath)};
    if (!file.is_open()) {
        return unexpected("Failed to open file");
    }
    keyword_aos cn;
    auto & records = cn._records;
    string line;
    size_t line_number = 1;
    while (getline(file, line)) {
        auto record_exp = record_type::from_csv_row(line, delim);
        if (!record_exp) {
            return unexpected("Error parsing line " + std::to_string(line_number) + ": " + record_exp.error());
        }
        records.push_back(*record_exp);
        ++line_number;
    }

    return cn;
}