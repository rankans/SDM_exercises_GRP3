#include <iostream>
#include "company_name.hpp"
#include "title.hpp"
#include "keyword.hpp"
#include "algorithm"

#include <set>

using namespace std;

int main()
{
    auto cn = company_name::load_from_file("/exercise/imdb/csv/company_name.csv");
    if (!cn)
    {
        std::cerr << "Error loading company_name.csv: " << cn.error() << "\n";
        return 1;
    }

    std::cout << "Loaded " << (*cn).records().size() << " records from company_name.csv\n";

    // SELECT COUNT(*) FROM company_name WHERE country_code LIKE '[us]'
    // int count = 0;
    // for (auto const &record : (*cn).records())
    // {
    //     if (record.country_code().compare("[us]") == 0)
    //     {
    //         ++count;
    //     }
    // }
    // std::cout << "Count of records with country_code LIKE '[us]': " << count << " (should be 138946)\n";

    // SELECT distinct country_code FROM company_name
    vector<string> country_codes{};
    for (auto const &record : (*cn).records())
    {
        country_codes.push_back(record.country_code());
    };

    sort(country_codes.begin(), country_codes.end());
    country_codes.erase(unique(country_codes.begin(), country_codes.end()), country_codes.end());

    for (auto const &c : country_codes)
    {
        std::cout << c << " ";
    }

    auto keyword = keyword::load_from_file("/exercise/imdb/csv/keyword.csv");
    if (!keyword)
    {
        std::cerr << "Error loading keyword.csv: " << keyword.error() << "\n";
        return 1;
    }

    std::cout << "Loaded " << (*keyword).records().size() << " records from keyword.csv\n";

    // SELECT COUNT(*) FROM company_name WHERE country_code LIKE '[us]'
    // int count = 0;
    vector<string> keywords{};

    // SELECT count(distinct keyword) FROM keyword
    for (auto const &record : (*keyword).records())
    {
        keywords.push_back(record.keyword());
    };

    // auto last = ;
    sort(keywords.begin(), keywords.end());
    int uniqueCount = distance(keywords.begin(), unique(keywords.begin(), keywords.end()));

    std::cout << "Count of records with unique keywords: " << uniqueCount << "\n";

    // auto cn = title_space::title_record::load_from_file("/exercise/imdb/csv/title.csv");
    // if (!cn)
    // {
    //     cerr << "Error loading title.csv: " << cn.error() << "\n";
    //     return 1;
    // }

    // auto &cn_val = *cn;
    // std::cout << "Loaded " << cn_val.size() << " records from title.csv\n";

    // // SELECT * from titile;
    // // int count = 0;
    // for (size_t i = 0; i < cn_val.size(); ++i)
    // {
    //     cn_val.print_record(i);
    // }
    return 0;
}

// void distince_company_name(company_name cn)
// {
//     vector<string> country_codes{};

//     // SELECT distinct country_code FROM company_name
//     for (auto const &record : cn.records())
//     {
//         country_codes.push_back(record.country_code());
//     };

//     country_codes.erase(unique(country_codes.begin(), country_codes.end()), country_codes.end());

//     // Print the vector
//     for (auto const &code : country_codes)
//         std::cout << code << " ";
// }