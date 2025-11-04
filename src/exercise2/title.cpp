#include <iostream>
#include <fstream>
#include <stdexcept>

#include "title.hpp"
#include "utils.hpp"

using namespace std;
std::expected<title, csv::err_t> title::load_from_file(std::string_view filepath, char delim) {
    std::ifstream file{std::string(filepath)};
    if (!file.is_open()) {
        return std::unexpected("Failed to open file");
    }
    title cn;
    auto & records = cn._records;
    std::string line;
    std::size_t line_number = 1;
    while (std::getline(file, line)) {
        auto record_exp = record_type::from_csv_row(line, delim);
        if (!record_exp) {
            return std::unexpected("Error parsing line " + std::to_string(line_number) + ": " + record_exp.error());
        }
        records.push_back(*record_exp);
        ++line_number;
    }

    return cn;
}