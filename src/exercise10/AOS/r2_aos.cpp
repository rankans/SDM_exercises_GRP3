#include "r2_aos.hpp"

#include <random>
#include <stdexcept>

r2_aos_record::r2_aos_record(std::int64_t column_a, std::string column_b)
    : _column_a(column_a), _column_b(std::move(column_b))
{
}

r2_aos r2_aos::generate_relation(std::size_t X, std::int64_t Y)
{
    if (Y <= 0)
        throw std::invalid_argument("Y must be > 0");

    r2_aos relation;
    relation._records.reserve(X);

    std::random_device rd;
    std::mt19937_64 gen(rd());

    std::uniform_int_distribution<std::int64_t> dist_a(1, Y);
    std::uniform_int_distribution<int> dist_len(5, 15);
    std::uniform_int_distribution<int> dist_char(0, 25);

    for (std::size_t i = 0; i < X; ++i)
    {
        const std::int64_t a = dist_a(gen);

        const int len = dist_len(gen);
        std::string s;
        s.resize(static_cast<std::size_t>(len));
        for (int j = 0; j < len; ++j)
            s[static_cast<std::size_t>(j)] = static_cast<char>('A' + dist_char(gen));

        relation._records.emplace_back(a, std::move(s));
    }

    return relation;
}

const std::vector<r2_aos::record_type> &r2_aos::records() const noexcept
{
    return _records;
}

std::size_t r2_aos::size() const noexcept
{
    return _records.size();
}
