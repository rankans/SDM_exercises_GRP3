#include "r1_aos.hpp"

#include <random>

using namespace std;

r1_aos_record::r1_aos_record(std::int64_t column_a, std::string column_b)
    : _column_a(column_a), _column_b(std::move(column_b))
{
}

r1_aos r1_aos::generate_relation(size_t X, std::int64_t Y)
{
   r1_aos relation;
    relation._records.reserve(X);
    
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));
    
    for (size_t i = 0; i < X; ++i)
    {
        // Generate random integer between 1 and Y
        std::int64_t random_int = (rand() % Y) + 1;
        
        // Generate random string length between 5 and 15
        int str_len = (rand() % 11) + 5;  // 11 = (15-5+1), +5 for minimum
        std::string random_str;
        random_str.reserve(str_len);
        
        // Generate random uppercase letters A-Z
        for (int j = 0; j < str_len; ++j)
        {
            char random_char = 'A' + (rand() % 26);  // 26 letters A-Z
            random_str += random_char;
        }
        
        relation._records.emplace_back(random_int, std::move(random_str));
    }
    
    return relation;
}

const std::vector<r1_aos::record_type> &r1_aos::records() const noexcept
{
    return _records;
}

size_t r1_aos::size() const noexcept
{
    return _records.size();
}
