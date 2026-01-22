#pragma once
#include <string>
#include <cstdint>
#include <vector>

// Relation R2 with two columns:
// Column A: Random integers between 1 and Y
// Column B: Random string data

class r2_aos;

class r2_aos_record
{
private:
    std::int64_t _column_a; // Random integer between 1 and Y
    std::string _column_b;  // Random string data

public:
    r2_aos_record(std::int64_t column_a, std::string column_b);

    const std::int64_t &column_a() const noexcept { return _column_a; }
    const std::string &column_b() const noexcept { return _column_b; }

    friend class r2_aos;
};

class r2_aos
{
    using record_type = r2_aos_record;

private:
    r2_aos() = default;
    std::vector<record_type> _records;

public:
    static r2_aos generate_relation(std::size_t X, std::int64_t Y);

    // Accessor
    const std::vector<record_type> &records() const noexcept;

    // Size accessor
    std::size_t size() const noexcept;
};
