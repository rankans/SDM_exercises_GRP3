#include "r1_soa.hpp"

#include <random>
#include <stdexcept>

r1_soa r1_soa::generate_relation(std::size_t X, std::int64_t Y)
{
    if (Y <= 0)
        throw std::invalid_argument("Y must be > 0");

    r1_soa rel;
    rel._column_a.reserve(X);
    rel._column_b.reserve(X);

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

        rel._column_a.emplace_back(a);
        rel._column_b.emplace_back(std::move(s));
    }

    return rel;
}