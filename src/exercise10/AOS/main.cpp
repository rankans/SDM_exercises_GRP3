#include <iostream>
#include "r1_aos.hpp"

using namespace std;

int main()
{
    // Parameters: X = 10 * Y elements, Y = max value for column A
    const int64_t Y = 100;
    const size_t X = 10 * Y;
    
    // Generate relation R1 with specified parameters
    auto r1_relation = r1_aos::generate_relation(X, Y);
    
    cout << "Generated R1 relation with " << r1_relation.size() << " records\n";
    
    // // Quick verification - check first few records
    // const auto &records = r1_relation.records();
    // if (!records.empty()) {
    //     cout << "First record: A=" << records[0].column_a() 
    //          << ", B=\"" << records[0].column_b() << "\"\n";
        
    //     if (records.size() > 1) {
    //         cout << "Second record: A=" << records[1].column_a() 
    //              << ", B=\"" << records[1].column_b() << "\"\n";
    //     }
        
    //     // Verify column A values are in range 1-Y
    //     bool valid_range = true;
    //     for (size_t i = 0; i < min(size_t(10), records.size()); ++i) {
    //         int64_t val = records[i].column_a();
    //         if (val < 1 || val > Y) {
    //             valid_range = false;
    //             break;
    //         }
    //     }
    //     cout << "Column A values in range [1," << Y << "]: " << (valid_range ? "YES" : "NO") << "\n";
    // }

    return 0;
}