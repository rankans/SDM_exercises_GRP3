#include <cstdint>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <chrono>

#include "r1_aos.hpp"
#include "r2_aos.hpp"

struct Timings
{
    double build_ms{};
    double probe_ms{};
    std::uint64_t matches{};
};

static double ms_since(const std::chrono::steady_clock::time_point &t0,
                       const std::chrono::steady_clock::time_point &t1)
{
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

// ========== AOS JOIN OPERATIONS ==========
static Timings join_build_r1_probe_r2_with_map_aos(const r1_aos &r1, const r2_aos &r2)
{
    Timings out{};
    std::map<std::int64_t, std::vector<std::size_t>> index;

    // Build phase: Create index on R1.column_a
    auto t0 = std::chrono::steady_clock::now();
    const auto &r1_records = r1.records();
    for (std::size_t i = 0; i < r1_records.size(); ++i)
    {
        index[r1_records[i].column_a()].push_back(i);
    }
    auto t1 = std::chrono::steady_clock::now();
    out.build_ms = ms_since(t0, t1);

    // Probe phase: Look up R2.column_a in R1 index
    t0 = std::chrono::steady_clock::now();
    const auto &r2_records = r2.records();
    for (std::size_t j = 0; j < r2_records.size(); ++j)
    {
        auto it = index.find(r2_records[j].column_a());
        if (it != index.end())
            out.matches += static_cast<std::uint64_t>(it->second.size());
    }
    t1 = std::chrono::steady_clock::now();
    out.probe_ms = ms_since(t0, t1);

    return out;
}

static Timings join_build_r1_probe_r2_with_unordered_map_aos(const r1_aos &r1, const r2_aos &r2)
{
    Timings out{};
    std::unordered_map<std::int64_t, std::vector<std::size_t>> index;
    index.reserve(r1.size());

    // Build phase: Create hash index on R1.column_a
    auto t0 = std::chrono::steady_clock::now();
    const auto &r1_records = r1.records();
    for (std::size_t i = 0; i < r1_records.size(); ++i)
    {
        index[r1_records[i].column_a()].push_back(i);
    }
    auto t1 = std::chrono::steady_clock::now();
    out.build_ms = ms_since(t0, t1);

    // Probe phase: Look up R2.column_a in R1 hash index
    t0 = std::chrono::steady_clock::now();
    const auto &r2_records = r2.records();
    for (std::size_t j = 0; j < r2_records.size(); ++j)
    {
        auto it = index.find(r2_records[j].column_a());
        if (it != index.end())
            out.matches += static_cast<std::uint64_t>(it->second.size());
    }
    t1 = std::chrono::steady_clock::now();
    out.probe_ms = ms_since(t0, t1);

    return out;
}

static Timings join_build_r2_probe_r1_with_map_aos(const r2_aos &r2, const r1_aos &r1)
{
    Timings out{};
    std::map<std::int64_t, std::vector<std::size_t>> index;

    // Build phase: Create index on R2.column_a
    auto t0 = std::chrono::steady_clock::now();
    const auto &r2_records = r2.records();
    for (std::size_t j = 0; j < r2_records.size(); ++j)
    {
        index[r2_records[j].column_a()].push_back(j);
    }
    auto t1 = std::chrono::steady_clock::now();
    out.build_ms = ms_since(t0, t1);

    // Probe phase: Look up R1.column_a in R2 index
    t0 = std::chrono::steady_clock::now();
    const auto &r1_records = r1.records();
    for (std::size_t i = 0; i < r1_records.size(); ++i)
    {
        auto it = index.find(r1_records[i].column_a());
        if (it != index.end())
            out.matches += static_cast<std::uint64_t>(it->second.size());
    }
    t1 = std::chrono::steady_clock::now();
    out.probe_ms = ms_since(t0, t1);

    return out;
}

static Timings join_build_r2_probe_r1_with_unordered_map_aos(const r2_aos &r2, const r1_aos &r1)
{
    Timings out{};
    std::unordered_map<std::int64_t, std::vector<std::size_t>> index;
    index.reserve(r2.size());

    // Build phase: Create hash index on R2.column_a
    auto t0 = std::chrono::steady_clock::now();
    const auto &r2_records = r2.records();
    for (std::size_t j = 0; j < r2_records.size(); ++j)
    {
        index[r2_records[j].column_a()].push_back(j);
    }
    auto t1 = std::chrono::steady_clock::now();
    out.build_ms = ms_since(t0, t1);

    // Probe phase: Look up R1.column_a in R2 hash index
    t0 = std::chrono::steady_clock::now();
    const auto &r1_records = r1.records();
    for (std::size_t i = 0; i < r1_records.size(); ++i)
    {
        auto it = index.find(r1_records[i].column_a());
        if (it != index.end())
            out.matches += static_cast<std::uint64_t>(it->second.size());
    }
    t1 = std::chrono::steady_clock::now();
    out.probe_ms = ms_since(t0, t1);

    return out;
}

static void print_result(const char *label, const Timings &t)
{
    std::cout << label
              << " | build: " << t.build_ms << " ms"
              << " | probe: " << t.probe_ms << " ms"
              << " | matches: " << t.matches
              << "\n";
}

int main()
{
    const std::int64_t Y = 100000;
    const std::size_t X = 10ULL * static_cast<std::size_t>(Y);

    std::cout << "=== ROW-STORE (AOS) JOIN PERFORMANCE TEST ===\n";
    std::cout << "Generating relations with X = " << X << " elements, Y = " << Y << " max value...\n\n";
    
    // Instantiate row-store (AOS) entities
    auto r1 = r1_aos::generate_relation(X, Y);
    auto r2 = r2_aos::generate_relation(X, Y);

    std::cout << "R1 (AoS) size: " << r1.size() << "\n";
    std::cout << "R2 (AoS) size: " << r2.size() << "\n\n";

    // Perform join operations R1.A = R2.A
    std::cout << "Join Operation: R1.column_a = R2.column_a\n\n";

    print_result("Build R1 (AoS) with std::map, probe R2 (AoS)",
                 join_build_r1_probe_r2_with_map_aos(r1, r2));

    print_result("Build R1 (AoS) with std::unordered_map, probe R2 (AoS)",
                 join_build_r1_probe_r2_with_unordered_map_aos(r1, r2));

    std::cout << "\n";

    print_result("Build R2 (AoS) with std::map, probe R1 (AoS)",
                 join_build_r2_probe_r1_with_map_aos(r2, r1));

    print_result("Build R2 (AoS) with std::unordered_map, probe R1 (AoS)",
                 join_build_r2_probe_r1_with_unordered_map_aos(r2, r1));

    std::cout << "\n=== AOS JOIN TEST COMPLETED ===\n";
    return 0;
}
