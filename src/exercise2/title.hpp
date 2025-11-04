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
//  id              | integer               |           | not null | 
//  title           | text                  |           | not null | 
//  imdb_index      | character varying(12) |           |          | 
//  kind_id         | integer               |           | not null | 
//  production_year | integer               |           |          | 
//  imdb_id         | integer               |           |          | 
//  phonetic_code   | character varying(5)  |           |          | 
//  episode_of_id   | integer               |           |          | 
//  season_nr       | integer               |           |          | 
//  episode_nr      | integer               |           |          | 
//  series_years    | character varying(49) |           |          | 
//  md5sum          | character varying(32) |           |          | 
// Indexes:
//     "title_pkey" PRIMARY KEY, btree (id)


using namespace std;
class title;
// rule of 3 and rule of 5 in c++
class title_record {
    private:
        int _id;
        string _title;
        string _imdb_index;
        int _kind_id;
        int _production_year;
        int _imdb_id;
        string _phonetic_code;
        int _episode_of_id;
        int _season_nr;
        int _episode_nr;
        string _series_years;
        string _md5sum;


        title_record(
            int id,
            string title,
            string imdb_index,
            int kind_id,
            int production_year,
            int imdb_id,
            string phonetic_code,
            int episode_of_id,
            int season_nr,
            int episode_nr,
            string series_years,
            string md5sum
        )
        : _id(id),                                           //id[0](id[1]) ---> 0 is class member, 1 is constructor argument
        _title(move(title)),
        _imdb_index(move(imdb_index)),
        _kind_id(kind_id),
        _production_year(production_year),
        _imdb_id(imdb_id),
        _phonetic_code(move(phonetic_code)),
        _episode_of_id(episode_of_id),
        _episode_nr(episode_nr),
        _series_years(move(series_years)),
        _md5sum(move(md5sum))
        {}

        static inline expected<title_record, csv::err_t> from_csv_row(string_view row, char delim='|'){
            //string_view is pointer to first string + length; that means for "HELLO" its like pointer to H and 5 eg: struct string_view{const char* data, Uint size}; so H iterated 5 times in memory giving the entire word
            //its absolutely not required here in basic devs but important in deployments
            // expected is like saying either return title_record or csv err 
            auto field = csv::split_line(row, 13, delim);
            if(!field){
                return unexpected("Error while splitting: " + field.error());
            }

            auto f_copy = field.value(); //can also write *field (shorthand), have used field.value for explanation
            
            auto id = csv::from_field<int>(f_copy[0]);
            string title = csv::from_field<string>(f_copy[1]).value();
            string imdb_index = csv::from_field<string>(f_copy[2]).value();
            auto kind_id = csv::from_field<int>(f_copy[3]);
            auto production_year = csv::from_field<int>(f_copy[4]);
            auto imdb_id = csv::from_field<int>(f_copy[5]);
            string phonetic_code = csv::from_field<string>(f_copy[6]).value();
            auto episode_of_id = csv::from_field<int>(f_copy[7]);
            auto season_nr = csv::from_field<int>(f_copy[8]);
            auto episode_nr = csv::from_field<int>(f_copy[9]);
            string series_years = csv::from_field<string>(f_copy[10]).value();
            string md5sum = csv::from_field<string>(f_copy[11]).value();

            if(!id || !kind_id || !production_year || !imdb_id || !episode_of_id || !season_nr || !episode_nr){
                return (unexpected("Unknown error while parsing one of the fields!! PS. Didn't wanna type in that many if statements!"));
            }

            return title_record{
                *id, // again same as id.value()
                title,
                imdb_index,
                kind_id.value(), //just for example
                *production_year,
                *imdb_id,
                phonetic_code,
                *episode_of_id,
                *season_nr,
                *episode_nr,
                series_years,
                md5sum};
        }

    public:
        int id() const {return _id;} //just copying an integer is much faster than passing a reference
        string const& title() const {return _title;}
        string const& imdb_index() const {return _imdb_index;}
        int kind_id() const {return _kind_id;}
        int production_year() const {return _production_year;}
        int imdb_id() const {return _imdb_id;}
        string const& phonetic_code() const {return _phonetic_code;}
        int episode_of_id() const {return _episode_of_id;}
        int season_nr() const {return _season_nr;}
        int episode_nr() const {return _episode_nr;}
        string const& series_years() const {return _series_years;}
        string const& md5sum() const {return _md5sum;}

    friend class title; 
    friend std::ostream& operator<<(std::ostream& os, title_record const& record) { // didn't understand this properly ask next class
    os << "title_record { "
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
    return os;
}   
};

class title{
    using record_type = title_record;
    private:
        title() = default; //this makes a default and makes it such that no one can create a constructor
    public:
        static expected<title, csv::err_t> load_from_file(std::string_view filepath, char delim = '|');
        vector<record_type> const & records() const noexcept {
            return _records;
        }
    private:
        std::vector<record_type> _records;
};