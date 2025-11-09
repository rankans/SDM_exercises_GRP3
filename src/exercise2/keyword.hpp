#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <expected>
#include <cstdint>
#include "utils.hpp"

// Structure of Arrays (SoA) representation for 'keyword' table
/*
    Column     |         Type         | Collation | Nullable | Default
---------------+----------------------+-----------+----------+---------
 id            | integer              |           | not null |
 keyword       | text                 |           | not null |
 phonetic_code | character varying(5) |           |          |
Indexes:
    "keyword_pkey" PRIMARY KEY, btree (id)
*/
class keyword
{
public:
    // Columns as separate vectors (SoA layout)
    std::vector<int64_t> id;
    std::vector<std::string> keyword_name;
    std::vector<std::string> phonetic_code;

    // Load data from CSV
    static std::expected<keyword, csv::err_t> load_from_file(std::string_view filepath, char delim = '|');

    // Utility
    size_t size() const noexcept { return id.size(); }
};