#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <cstdint>
#include <expected>
#include <vector>
#include "utils.hpp"

// imdb=# \d keyword
//                         Table "public.keyword"
//     Column     |         Type         | Collation | Nullable | Default 
// ---------------+----------------------+-----------+----------+---------
//  id            | integer              |           | not null | 
//  keyword       | text                 |           | not null | 
//  phonetic_code | character varying(5) |           |          | 
// Indexes:
//     "keyword_pkey" PRIMARY KEY, btree (id)

using namespace std;

namespace keyword_space{
    class keyword_record{

        private:
            vector<int64_t> _id;
            vector<string> _keyword;
            vector<string> _phonetic_code;
            static const size_t batch_size = 1024;
            
            keyword_record() = default;
        public:
            struct batch{
                    size_t start_index;
                    size_t end_index;
                    };
            static expected<keyword_record, csv::err_t> load_from_file(string_view filePath, char delim='|');

            //getters
            const vector<int64_t>& id()                   const noexcept {return _id;}         
            const vector<string>& keyword()  const noexcept {return _keyword;}
            const vector<string>& phonetic_code()  const noexcept {return _phonetic_code;}

            // For lab 5 batch operations
            batch next_batch(size_t& pointer) const{
                if(pointer >= _id.size()) return{pointer, pointer};

                size_t batch_end = min(pointer+batch_size, _id.size());
                batch b{pointer, batch_end};
                pointer = batch_end;
                return b;
            }

            //setter
            void set_keyword(size_t i, const string& modified_value){_keyword[i] = modified_value;}

            size_t size() const {return _id.size();}

            void print_record(size_t i) const{
                cout<< "Keyword_record { "
                << "id: " << _id[i] << ", "
                << "keyword: " << _keyword[i] << ", "
                << "phonetic_code: " << _phonetic_code[i] << "}\n ";
            }

    };

}