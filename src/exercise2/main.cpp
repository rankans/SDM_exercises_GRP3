#include <iostream>
#include "company_name.hpp"
#include "title.hpp"

#include <set>

using namespace std;

int main() {
    auto cn = title::load_from_file("/exercise/imdb/csv/title.csv");
    if (!cn) {
        std::cerr << "Error loading title.csv: " << cn.error() << "\n";
        return 1;
    }

    std::cout << "Loaded " << (*cn).records().size() << " records from title.csv\n";

    // SELECT * from titile;
    int count = 0;
    for (auto const& record: (*cn).records()) {
        cout<< record;
    }    
    return 0;
}