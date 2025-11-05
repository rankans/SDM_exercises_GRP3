#include <iostream>
#include "company_name.hpp"
#include "title.hpp"

#include <set>

using namespace std;

int main() {
    auto cn = title_space::title_record::load_from_file("/exercise/imdb/csv/title.csv");
    if (!cn) {
        cerr << "Error loading title.csv: " << cn.error() << "\n";
        return 1;
    }

    auto& cn_val = *cn;
    std::cout << "Loaded " << cn_val.size() << " records from title.csv\n";

    // SELECT * from titile;
    // int count = 0;
    for(size_t i =0; i<cn_val.size(); ++i){
        cn_val.print_record(i);
    }   
    return 0;
}