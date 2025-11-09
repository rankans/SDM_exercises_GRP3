#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "queries.hpp"
#include "utils.hpp"



// SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970
vector<string> queries_blueprint::title_in_production_range(int year_start, int year_end) const{
    vector<string> titles;
    for(size_t i=0; i< title_table.size(); ++i){
        if(title_table.production_year()[i] < year_end && title_table.production_year()[i] >= year_start){
            titles.push_back(title_table.title()[i]);
        }
    }
    return titles;
}

// SELECT distinct country_code FROM company_name
set<string> queries_blueprint::dictinct_country_code() const{
    set<string> country_codes;
    for(size_t i=0; i<company_table.records().size(); ++i){
        country_codes.insert(company_table.records()[i].country_code());
    }
    return country_codes;
}

// SELECT count(distinct keyword) FROM keyword
int queries_blueprint::count_distinct_keyword() const{
    set<string> distinct_keyword;
    for(size_t i=0; i<keyword_table.size(); ++i){
        distinct_keyword.insert(keyword_table.keyword()[i]);
    }
    return distinct_keyword.size();
}

// SELECT * FROM company_name WHERE name not like '%Group%'
vector<company_name_record> queries_blueprint::name_not_like() const{
    vector<company_name_record> company_name_records;
    for(size_t i=0; i<company_table.records().size(); ++i){
        if(company_table.records()[i].name().find("Group") == string::npos){
            company_name_records.push_back(company_table.records()[i]);
        }
    }
    return company_name_records;
}

//Lab 3
// Find entries in the keyword table, where the keyword starts with a specific sequence
// of letters of your choice. Modify the found records in-place by replacing the keyword
// entry with a predefned value.

keyword_space::keyword_record& queries_blueprint::replace_keyword(){
    for(size_t i=0; i<keyword_table.size(); ++i){
        if(keyword_table.keyword()[i].find("fifty") != string::npos){
            keyword_table.set_keyword(i, "fiftyisoldchangedisnew");
        }
    }
    return keyword_table;
}

title_space::title_record& queries_blueprint::replace_production_date(){
    for(size_t i=0; i<title_table.size(); ++i){
        if(title_table.production_year()[i] == 1996 
        || title_table.production_year()[i] == 1967
        || title_table.production_year()[i] == 1990
        || title_table.production_year()[i] == 2000 ){
            title_table.set_production_year(i,2069);
        }
    }
    return title_table;
}
