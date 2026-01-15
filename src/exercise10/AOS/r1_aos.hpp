#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include <random>

// Relation R1 with two columns:
// Column A: Random integers between 1 and Y  
// Column B: Random string data

using namespace std;

class r1_aos;

class r1_aos_record
{
private:
    int64_t _column_a;      // Random integer between 1 and Y
    string _column_b;       // Random string data

public:
    r1_aos_record(int64_t column_a, string column_b)
        : _column_a(column_a), _column_b(move(column_b))
    {
    }
    
    const int64_t &column_a() const noexcept { return _column_a; }
    const string &column_b() const noexcept { return _column_b; }
    
    friend class r1_aos;
};

class r1_aos
{
    using record_type = r1_aos_record;
    
private:
    vector<record_type> _records;
    
    r1_aos() = default;
    
public:
    static r1_aos generate_relation(size_t X, int64_t Y)
    {
        r1_aos relation;
        relation._records.reserve(X);
        
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int64_t> int_dist(1, Y);
        uniform_int_distribution<int> char_dist('A', 'Z');
        uniform_int_distribution<int> len_dist(5, 15);  // Random string length
        
        for (size_t i = 0; i < X; ++i)
        {
            int64_t random_int = int_dist(gen);
            
            // Generate random string 
            int str_len = len_dist(gen);
            string random_str;
            random_str.reserve(str_len);
            
            for (int j = 0; j < str_len; ++j)
            {
                random_str += static_cast<char>(char_dist(gen));
            }
            
            relation._records.emplace_back(random_int, move(random_str));
        }
        
        return relation;
    }
    
    // Accessor
    const vector<record_type> &records() const noexcept
    {
        return _records;
    }
    
    // Size accessor
    size_t size() const noexcept
    {
        return _records.size();
    }
};