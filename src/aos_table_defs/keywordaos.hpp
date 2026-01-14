#pragma once
#include <string>
#include <string_view>
#include <cstdint>
#include <expected>
#include <vector>
#include <ostream>
#include "../commons/utils.hpp"

// imdb=# \d keyword d
//                         Table "public.keyword"
//     Column     |         Type         | Collation | Nullable | Default
// ---------------+----------------------+-----------+----------+---------
//  id            | integer              |           | not null |
//  keyword       | text                 |           | not null |
//  phonetic_code | character varying(5) |           |          |
// Indexes:
//     "keyword_pkey" PRIMARY KEY, btree (id)

using namespace std;

class keyword_aos;

class keyword_aos_record
{
private:
    int64_t _id;
    string _keyword;
    string _phonetic_code;

    keyword_aos_record(int64_t id,
                       string keyword,
                       string phonetic_code)
        : _id(id), _keyword(move(keyword)), _phonetic_code(move(phonetic_code))
    {
    }

    static inline expected<keyword_aos_record, csv::err_t>
    from_csv_row(string_view row, char delim = '|')
    {
        auto fields_exp = csv::split_line(row, 4, delim);
        if (!fields_exp)
        {
            return unexpected(fields_exp.error());
        }
        auto &f = *fields_exp;
        auto id = csv::from_field<int64_t>(f[0]);
        auto keyword = csv::from_field<string>(f[1]);
        if (!id)
        {
            return unexpected("Field 0 (id): " + id.error());
        }
        if (!keyword)
        {
            return unexpected("Field 3 (imdb): " + keyword.error());
        }

        return keyword_aos_record{
            *id,
            *keyword,
            f[2],
        };
    }

public:
    static expected<keyword_aos_record, csv::err_t> load_from_file(string_view filePath, char delim = '|');

    const int64_t &id() const noexcept { return _id; };
    const string &keyword() const noexcept { return _keyword; };
    const string &phonetic_code() const noexcept { return _phonetic_code; };

    friend class keyword_aos;
    friend ostream &operator<<(ostream &os, const keyword_aos &table);
};

class keyword_aos
{
    using record_type = keyword_aos_record;

private:
    vector<record_type> _records;

    keyword_aos() = default;

public:
    static expected<keyword_aos, csv::err_t> load_from_file(string_view filepath, char delim = '|');
    vector<record_type> const &records() const noexcept
    {
        return _records;
    }
};