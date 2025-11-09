#include "keyword.hpp"
#include <fstream>
#include <iostream>

std::expected<keyword, csv::err_t> keyword::load_from_file(std::string_view filepath, char delim) {
    std::ifstream file{std::string(filepath)};
    if (!file.is_open()) {
        return std::unexpected("Failed to open file: " + std::string(filepath));
    }

    keyword k;
    std::string line;
    size_t line_number = 1;

    while (std::getline(file, line)) {
        auto fields_exp = csv::split_line(line, 3, delim);
        if (!fields_exp) {
            return std::unexpected("Error parsing line " + std::to_string(line_number) + ": " + fields_exp.error());
        }
        auto& f = *fields_exp;

        auto id = csv::from_field<int64_t>(f[0]);
        if (!id) {
            return std::unexpected("Invalid id at line " + std::to_string(line_number));
        }

        k.id.push_back(*id);
        k.keyword_name.push_back(f[1]);
        k.phonetic_code.push_back(f[2]);

        ++line_number;
    }

    return k;
}
