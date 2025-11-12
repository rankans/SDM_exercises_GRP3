#include <iostream>
#include <fstream>
#include <stdexcept>

#include "company_name_SoA.hpp"
#include "utils.hpp"

using namespace std;
using namespace csv;

expected<company_name_records, err_t> company_name_records::load_from_file(string_view filePath, char delim)
{
    ifstream file{string(filePath)};
    if (!file.is_open())
    {
        return unexpected("Unexpected error while opening file");
    }

    company_name_records records;
    string row;

    while (getline(file, row))
    {
        auto field_exp = split_line(row, 8, delim);
        if (!field_exp)
        {
            return unexpected("could not split field");
        }

        auto &f = *field_exp;

        auto [id, name, country_code, imdb_id, name_pcode_nf, name_pcode_sf, md5sum] =
            tuple{
                from_field<int64_t>(f[0]),
                from_field<string>(f[1]),
                from_field<string>(f[2]),
                from_field<int64_t>(f[3]),
                from_field<string>(f[4]),
                from_field<string>(f[5]),
                from_field<string>(f[6])};
        records.append(*id, *name, *country_code, *imdb_id, *name_pcode_nf, *name_pcode_sf, *md5sum);
    }
    return records;
}