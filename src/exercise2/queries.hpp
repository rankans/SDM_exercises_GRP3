#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "title.hpp"
#include "keyword.hpp"
#include "company_name.hpp"
#include "titleaos.hpp"
#include "keywordaos.hpp"

using namespace std;

class queries_blueprint
{

private:
    // title_space::title_record const& title_table;
    title_space::title_record title_table; // title also needs to change
    // keyword_space::keyword_record const& keyword_table;
    keyword_space::keyword_record keyword_table; // for lab 3 we need to modify the original value
    company_name const &company_table;
    keyword_aos keyword_table_aos;

    // Lab 4
    titleaos const &title_aos_table;

public:
    queries_blueprint(
        // const title_space::title_record& t,
        title_space::title_record &t, // title also need to change
        // const keyword_space::keyword_record& k,
        keyword_space::keyword_record &k, // for lab 3 we need to modify the original table
        const company_name &c,
        keyword_aos &k_aos,
        const titleaos &ta) : title_table(t),
                              keyword_table(k),
                              company_table(c),
                              keyword_table_aos(k_aos),
                              title_aos_table(ta)
    {
    }

    // SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970
    vector<string> title_in_production_range(int year_start, int year_end) const;

    // SELECT distinct country_code FROM company_name
    set<string> dictinct_country_code() const;

    // SELECT count(distinct keyword) FROM keyword
    int count_distinct_keyword() const;

    // SELECT * FROM company_name WHERE name not like '%Group%'
    vector<company_name_record> name_not_like() const;

    // Lab 3

    keyword_space::keyword_record &replace_keyword();

    title_space::title_record &replace_production_date();

    // Lab 4
    //  SELECT title FROM title WHERE production_year = (SELECT max(production_year) FROM title)
    vector<string> max_production_year() const;

    // SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970
    vector<string> title_aos_in_production_range(int year_start, int year_end) const;

    int count_distinct_keyword2() const;

    // Lab 5--- BATCH MODEL IMPLEMENTATION

    // SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970
    vector<string> title_in_production_range_batch(int year_start, int year_end) const;
    // SELECT distinct country_code FROM company_name
    set<string> distinct_country_code_batch() const;

    // SELECT count(distinct keyword) FROM keyword
    int count_distinct_keyword_batch() const;

    // SELECT * FROM company_name WHERE name not like '%Group%'
    vector<company_name_record> name_not_like_in_batch() const;

    // Lab 5--- Iterator MODEL IMPLEMENTATION

    // SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970
    struct TitleInRangeIter
    {
        struct iterator
        {
            const title_space::title_record &table;
            size_t idx;
            int start_year, end_year;

            iterator(const title_space::title_record &t, size_t i, int start, int end)
                : table(t), idx(i), start_year(start), end_year(end)
            {
                advance();
            }

            // move to next valid row
            void advance()
            {
                while (idx < table.size() &&
                       !(table.production_year()[idx] >= start_year &&
                         table.production_year()[idx] < end_year))
                {
                    ++idx;
                }
            }

            std::string operator*() const { return table.title()[idx]; } // get current title

            iterator &operator++() // move to next valid one
            {
                ++idx;
                advance();
                return *this;
            }

            bool operator!=(const iterator &other) const { return idx != other.idx; } // compare
        };

        const title_space::title_record &table;
        int start_year, end_year;

        TitleInRangeIter(const title_space::title_record &t, int start, int end)
            : table(t), start_year(start), end_year(end) {}

        iterator begin() const { return iterator(table, 0, start_year, end_year); }
        iterator end() const { return iterator(table, table.size(), start_year, end_year); }
    };
    TitleInRangeIter title_in_production_range_iterator(int year_start, int year_end) const
    {
        return TitleInRangeIter(title_table, year_start, year_end);
    }



};