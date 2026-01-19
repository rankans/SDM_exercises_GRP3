#pragma once
#include <cstdint>
#include <string>
#include <vector>

class r2_soa
{
private:
    std::vector<std::int64_t> _column_a;
    std::vector<std::string> _column_b;

    r2_soa() = default;

public:
    static r2_soa generate_relation(std::size_t X, std::int64_t Y);

    const std::vector<std::int64_t> &column_a() const noexcept { return _column_a; }
    const std::vector<std::string> &column_b() const noexcept { return _column_b; }

    std::size_t size() const noexcept { return _column_a.size(); }
};