#include <iostream>
#include <fstream>
#include <stdexcept>
#include "keywordaos.hpp"

using namespace std;

expected<keyword_aos, csv::err_t> keyword_aos::load_from_file(string_view filepath, char delim)
{
    ifstream file{string(filepath)};
    if (!file.is_open())
    {
        return unexpected("Failed to open file");
    }
    keyword_aos cn;
    auto &records = cn._records;
    string line;
    size_t line_number = 1;
    while (getline(file, line))
    {
        auto record_exp = record_type::from_csv_row(line, delim);
        if (!record_exp)
        {
            return unexpected("Error parsing line " + to_string(line_number) + ": " + record_exp.error());
        }
        records.push_back(*record_exp);
        ++line_number;
    }

    return cn;
}

ostream &operator<<(ostream &os, const keyword_aos &table)
{
    if (!table.records().empty())
    {
        const auto &first = table.records().front();
        os << "keyword_aos first record { "
           << "id: " << first.id() << ", "
           << "keyword: " << first.keyword() << ", "
           << "phonetic_code: " << first.phonetic_code() << " }";
    }
    else
    {
        os << "keyword_aos (empty)";
    }
    return os;
}