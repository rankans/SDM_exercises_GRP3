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
namespace title_space{
    class title_record{
        private:
            vector<int64_t> _id;
            vector<string> _title;
            vector<string> _imdb_index;
            vector<int64_t> _kind_id;
            vector<int64_t> _production_year;
            vector<int64_t> _imdb_id;
            vector<string> _phonetic_code;
            vector<int64_t> _episode_of_id;
            vector<int64_t> _season_nr;
            vector<int64_t> _episode_nr;
            vector<string> _series_years;
            vector<string> _md5sum;


            title_record() = default;
        public:
            static expected<title_record, csv::err_t> load_from_file(string_view filePath, char delim='|'); //definition of load from file function

            //getters
            const vector<int64_t>& id()                   const noexcept {return _id;}         
            const vector<string>& title()  const noexcept {return _title;}
            const vector<string>& imdb_index()  const noexcept {return _imdb_index;}
            const vector<int64_t>& kind_id()  const noexcept {return _kind_id;}
            const vector<int64_t>& production_year()  const noexcept {return _production_year;}
            const vector<int64_t>& imdb_id()  const noexcept {return _imdb_id;}
            const vector<string>& phonetic_code()  const noexcept {return _phonetic_code;}
            const vector<int64_t>& episode_of_id()  const noexcept {return _episode_of_id;}
            const vector<int64_t>& season_nr()  const noexcept {return _season_nr;}
            const vector<int64_t>& episode_nr()  const noexcept {return _episode_nr;}
            const vector<string>& series_years()  const noexcept {return _series_years;}
            const vector<string>& md5sum()  const noexcept {return _md5sum;}

            //setter
            void set_production_year(size_t i, int64_t modified_year)  {_production_year[i] = modified_year;}

            size_t size() const {return(_id.size());}

            void print_record(size_t i) const {
                cout << "title_record { "
                        << "id: " << _id[i] << ", "
                        << "title: " << _title[i] << ", "
                        << "imdb_index: " << _imdb_index[i] << ", "
                        << "kind_id: " << _kind_id[i] << ", "
                        << "production_year: " << _production_year[i] << ", "
                        << "imdb_id: " << _imdb_id[i] << ", "
                        << "phonetic_code: " << _phonetic_code[i] << ", "
                        << "episode_of_id: " << _episode_of_id[i] << ", "
                        << "season_nr: " << _season_nr[i] << ", "
                        << "episode_nr: " << _episode_nr[i] << ", "
                        << "series_years: " << _series_years[i] << ", "
                        << "md5sum: " << _md5sum[i]
                        << " }\n";
    }

    };
}