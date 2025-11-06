#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <cstdint>
#include <expected>
#include <vector>
#include "utils.hpp"

class keyword;

using namespace std;
class keyword_record
{
private:
    keyword_record(
        int64_t id,
        string keyword,
        string phonetic_code) : _id(id), _keyword(move(keyword)), _phonetic_code(move(phonetic_code))
    {
    }

    static inline expected<keyword_record, csv::err_t>
    from_csv_row(string_view row, char delim = '|')
    {
        auto fields_exp = csv::split_line(row, 8, delim);
        if (!fields_exp)
        {
            return unexpected(fields_exp.error());
        }
        auto &f = *fields_exp;
        auto id = csv::from_field<int64_t>(f[0]);
        if (!id)
        {
            return unexpected("Field 0 (id): " + id.error());
        }

        return keyword_record{
            *id,
            f[1],
            f[2]};
    }

public:
    int64_t id() const noexcept { return _id; }
    string const &keyword() const noexcept { return _keyword; }
    string const &phonetic_code() const noexcept { return _phonetic_code; }

private:
    int64_t _id;
    string _keyword;
    string _phonetic_code;

    friend class keyword;
    friend std::ostream &operator<<(std::ostream &os, keyword_record const &record)
    {
        os << "keyword_record { "
           << "id: " << record.id() << ", "
           << "keyword: " << record.keyword() << ", "
           << "phonetic_code: " << record.phonetic_code() << "\n";
        return os;
    }
};

class keyword
{
    using record_type = keyword_record;

private:
    keyword() = default;

public:
    static expected<keyword, csv::err_t> load_from_file(string_view filepath, char delim = '|');
    vector<record_type> const &records() const noexcept
    {
        return _records;
    };

private:
    vector<record_type> _records;
};