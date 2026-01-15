#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "../soa_tables_updated/title.hpp"
#include "../soa_tables_updated/keyword.hpp"
#include "../soa_tables_updated/company_name_soa.hpp"
#include "aos_table_defs/company_name.hpp"

struct TitleInRangeIter
{
    struct iterator
    {
        const title_ex6_updated_record &table;
        size_t idx;
        int start_year, end_year;

        iterator(const title_ex6_updated_record &t, size_t i, int start, int end)
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

    const title_ex6_updated_record &table;
    int start_year, end_year;

    TitleInRangeIter(const title_ex6_updated_record &t, int start, int end)
        : table(t), start_year(start), end_year(end) {}

    iterator begin() const { return iterator(table, 0, start_year, end_year); }
    iterator end() const { return iterator(table, table.size(), start_year, end_year); }
};

struct KeywordIter
{
    struct iterator
    {
        const keyword_ex6_updated_record &table;
        size_t idx;

        iterator(const keyword_ex6_updated_record &t, size_t start_idx)
            : table(t), idx(start_idx)
        {
        }

        const std::string &operator*() const { return table.keyword()[idx]; }

        iterator &operator++()
        {
            ++idx; // move to next (can be optimized evn more later)
            return *this;
        }

        bool operator!=(const iterator &other) const { return idx != other.idx; }
    };

    const keyword_ex6_updated_record &table;

    KeywordIter(const keyword_ex6_updated_record &t) : table(t) {}

    iterator begin() const { return iterator(table, 0); }
    iterator end() const { return iterator(table, table.size()); }
};

struct NameNotLikeIter
{
    struct iterator
    {
        const company_name &table;
        size_t idx;

        iterator(const company_name &t, size_t i) : table(t), idx(i) { advance(); }

        void advance()
        {
            while (idx < table.records().size() &&
                   table.records()[idx].name().find("Group") != std::string::npos)
            {
                ++idx;
            }
        }

        const company_name_record &operator*() const { return table.records()[idx]; }

        iterator &operator++()
        {
            ++idx;
            advance();
            return *this;
        }

        bool operator!=(const iterator &other) const { return idx != other.idx; }
    };

    const company_name &table;

    NameNotLikeIter(const company_name &t) : table(t) {}

    iterator begin() const { return iterator(table, 0); }
    iterator end() const { return iterator(table, table.records().size()); }
};

struct DistinctCountryIter
{
    struct iterator
    {
        const company_name &table;
        size_t idx;
        std::set<std::string> seen;

        iterator(const company_name &t, size_t i) : table(t), idx(i) { advance(); }

        void advance()
        {
            while (idx < table.records().size() &&
                   !seen.insert(table.records()[idx].country_code()).second)
            {
                ++idx; // skip duplicates
            }
        }

        const std::string &operator*() const { return table.records()[idx].country_code(); }

        iterator &operator++()
        {
            ++idx;
            advance();
            return *this;
        }

        bool operator!=(const iterator &other) const { return idx != other.idx; }
    };

    const company_name &table;

    DistinctCountryIter(const company_name &t) : table(t) {}

    iterator begin() const { return iterator(table, 0); }
    iterator end() const { return iterator(table, table.records().size()); }
};