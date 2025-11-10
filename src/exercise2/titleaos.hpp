#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <cstdint>
#include <expected>
#include <vector>
#include "utils.hpp"


// mdb=# \d title
//                            Table "public.title"
//      Column      |         Type          | Collation | Nullable | Default 
// -----------------+-----------------------+-----------+----------+---------
//  id              | int64_teger               |           | not null | 
//  title           | text                  |           | not null | 
//  imdb_index      | character varying(12) |           |          | 
//  kind_id         | int64_teger               |           | not null | 
//  production_year | int64_teger               |           |          | 
//  imdb_id         | int64_teger               |           |          | 
//  phonetic_code   | character varying(5)  |           |          | 
//  episode_of_id   | int64_teger               |           |          | 
//  season_nr       | int64_teger               |           |          | 
//  episode_nr      | int64_teger               |           |          | 
//  series_years    | character varying(49) |           |          | 
//  md5sum          | character varying(32) |           |          | 
// Indexes:
//     "title_pkey" PRIMARY KEY, btree (id)
// rule of 3 and rule of 5 in c++

using namespace std;

class title_aos_record{
    private:
        int64_t _id;
        string _title;
        string _imdb_index;
        int64_t _kind_id;
        int64_t _production_year;
        int64_t _imdb_id;
        string _phonetic_code;
        int64_t _episode_of_id;
        int64_t _season_nr;
        int64_t _episode_nr;
        string _series_years;
        string _md5sum;
    friend class titleaos;

        title_aos_record(
            int64_t id ,
            string title ,
            string imdb_index ,
            int64_t kind_id ,
            int64_t production_year ,
            int64_t imdb_id ,
            string phonetic_code ,
            int64_t episode_of_id ,
            int64_t season_nr ,
            int64_t episode_nr ,
            string series_years ,
            string md5sum
        );
        
        static expected<title_aos_record, csv::err_t> load_from_row(string_view row, char delim = '|');

    public:
        //getters
        int64_t id()                   const noexcept {return _id;}         
        string const& title()  const noexcept {return _title;}
        string const& imdb_index()  const noexcept {return _imdb_index;}
        int64_t kind_id()  const noexcept {return _kind_id;}
        int64_t production_year()  const noexcept {return _production_year;}
        int64_t imdb_id()  const noexcept {return _imdb_id;}
        string const& phonetic_code()  const noexcept {return _phonetic_code;}
        int64_t episode_of_id()  const noexcept {return _episode_of_id;}
        int64_t season_nr()  const noexcept {return _season_nr;}
        int64_t episode_nr()  const noexcept {return _episode_nr;}
        string const& series_years()  const noexcept {return _series_years;}
        string const& md5sum()  const noexcept {return _md5sum;}
        
        void print_record(title_aos_record record) {
            cout << "title_record { "
            << "id: " << record.id() << ", "
            << "title: " << record.title() << ", "
            << "imdb_index: " << record.imdb_index() << ", "
            << "kind_id: " << record.kind_id() << ", "
            << "production_year: " << record.production_year() << ", "
            << "imdb_id: " << record.imdb_id() << ", "
            << "phonetic_code: " << record.phonetic_code() << ", "
            << "episode_of_id: " << record.episode_of_id() << ", "
            << "season_nr: " << record.season_nr() << ", "
            << "episode_nr: " << record.episode_nr() << ", "
            << "series_years: " << record.series_years() << ", "
            << "md5sum: " << record.md5sum()
            << " }";
        }
        
};

class titleaos {
    using record_type = title_aos_record;
    private:
        titleaos() = default;
        vector<record_type> _records;
    public:
        static std::expected<titleaos, csv::err_t> load_from_file(std::string_view filepath, char delim = '|');
        vector<record_type> const & records() const noexcept {return _records;}      
};
