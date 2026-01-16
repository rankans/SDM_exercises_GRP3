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
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int64_t> int_dist(1, Y);
    std::uniform_int_distribution<int> char_dist('A', 'Z');
    std::uniform_int_distribution<int> len_dist(5, 15);  // Random string length
    
    for (size_t i = 0; i < X; ++i)
    {
        std::int64_t random_int = int_dist(gen);
        
        // Generate random string 
        int str_len = len_dist(gen);
        std::string random_str;
        random_str.reserve(str_len);
        
        for (int j = 0; j < str_len; ++j)
        {
            random_str += static_cast<char>(char_dist(gen));
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