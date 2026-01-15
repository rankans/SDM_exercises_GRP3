#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <cstdint>
#include <expected>
#include <vector>
#include "commons/utils.hpp"

// imdb=# \d keyword
//                         records "public.company_name"
//     Column       |         Type         | Collation | Nullable | Default
// ---------------+----------------------+-----------+----------+---------
//  id              | integer              |           | not null |
//  name            | text                 |           | not null |
//  country_code    | character varying(5) |           |          |
//  imdb_id         |
//  name_pcode_nf   |
//  name_pcode_sf   |
//  md5sum          |
// Indexes:
//     "keyword_pkey" PRIMARY KEY, btree (id)

using namespace std;

class company_name_ex6_updated_record
{
private:
    vector<int64_t> _id;
    vector<string> _name;
    vector<string> _country_code;
    vector<int64_t> _imdb_id;
    vector<string> _name_pcode_nf;
    vector<string> _name_pcode_sf;
    vector<string> _md5sum;

    static const size_t batch_size = 1024;

public:
    struct batch
    {
        size_t start_index;
        size_t end_index;
    };
    static expected<company_name_ex6_updated_record, csv::err_t> load_from_file(string_view filePath, char delim = '|');

    // getters
    const vector<int64_t> &id() const noexcept { return _id; };
    const vector<string> &name() const noexcept { return _name; };
    const vector<string> &country_code() const noexcept { return _country_code; };
    const vector<int64_t> &imdb_id() const noexcept { return _imdb_id; };
    const vector<string> &name_pcode_nf() const noexcept { return _name_pcode_nf; };
    const vector<string> &name_pcode_sf() const noexcept { return _name_pcode_sf; };
    const vector<string> &md5sum() const noexcept { return _md5sum; };
    company_name_ex6_updated_record() = default;

    batch next_batch(size_t &pointer) const
    {
        if (pointer >= _id.size())
            return {pointer, pointer};

        size_t batch_end = min(pointer + batch_size, _id.size());
        batch b{pointer, batch_end};
        pointer = batch_end;
        return b;
    }

    size_t size() const { return _id.size(); }

    // setter
    void append(int64_t id,
                string name,
                string country_code,
                int64_t imdb_id,
                string name_pcode_nf,
                string name_pcode_sf,
                string md5sum)
    {
        _id.push_back(id);
        _name.push_back(move(name));
        _country_code.push_back(move(country_code));
        _imdb_id.push_back(imdb_id);
        _name_pcode_nf.push_back(move(name_pcode_nf));
        _name_pcode_sf.push_back(move(name_pcode_sf));
        _md5sum.push_back(move(md5sum));
    }

    friend std::ostream &operator<<(std::ostream &os, company_name_ex6_updated_record const &records)
    {
        for (size_t i = 0; i < records.size(); ++i)
        {
            os << "company_name_record {\n  "
               << "id: " << records._id[i] << ",\n  "
               << "name: " << records._name[i] << ",\n "
               << "country_code: " << records._country_code[i] << ",\n  "
               << "imdb_id: " << records._imdb_id[i] << ",\n    "
               << "name_pcode_nf: " << records._name_pcode_nf[i] << ",\n    "
               << "name_pcode_sf: " << records._name_pcode_sf[i] << ",\n    "
               << "md5sum: " << records._md5sum[i] << "\n"
               << " }\n";
        }
        return os;
    }

    void append_record(const company_name_ex6_updated_record &src, size_t i)
    {
        append(
            src.id()[i],
            src.name()[i],
            src.country_code()[i],
            src.imdb_id()[i],
            src.name_pcode_nf()[i],
            src.name_pcode_sf()[i],
            src.md5sum()[i]);
    }

    void print_record(size_t i) const
    {
        cout << "company_name_record { "
             << "id: " << _id[i] << ", "
             << "name: " << _name[i] << ", "
             << "country_code: " << _country_code[i] << ", "
             << "imdb_id: " << _imdb_id[i] << ", "
             << "name_pcode_nf: " << _name_pcode_nf[i] << ", "
             << "name_pcode_sf: " << _name_pcode_sf[i] << ", "
             << "md5sum: " << _md5sum[i]
             << " }\n";
    }
};
