#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <expected>
#include <cstdint>
#include "utils.hpp"

// Structure of Arrays (SoA) representation for 'title' table
/*
     Column      |         Type          | Collation | Nullable | Default
-----------------+-----------------------+-----------+----------+---------
 id              | integer               |           | not null |
 title           | text                  |           | not null |
 imdb_index      | character varying(12) |           |          |
 kind_id         | integer               |           | not null |
 production_year | integer               |           |          |
 imdb_id         | integer               |           |          |
 phonetic_code   | character varying(5)  |           |          |
 episode_of_id   | integer               |           |          |
 season_nr       | integer               |           |          |
 episode_nr      | integer               |           |          |
 series_years    | character varying(49) |           |          |
 md5sum          | character varying(32) |           |          |
Indexes:
    "title_pkey" PRIMARY KEY, btree (id)
*/
class title
{
public:
    // Columns as separate vectors (SoA layout)
    std::vector<int64_t> id;
    std::vector<std::string> title_name;
    std::vector<std::string> imdb_index;
    std::vector<int64_t> kind_id;
    std::vector<int64_t> production_year;
    std::vector<int64_t> imdb_id;
    std::vector<std::string> phonetic_code;
    std::vector<int64_t> episode_of_id;
    std::vector<int64_t> season_nr;
    std::vector<int64_t> episode_nr;
    std::vector<std::string> series_years;
    std::vector<std::string> md5sum;

    // Load data from CSV
    static std::expected<title, csv::err_t> load_from_file(std::string_view filepath, char delim = '|');

    // Utility
    size_t size() const noexcept { return id.size(); }
};