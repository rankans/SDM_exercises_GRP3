#include <cstdint>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <chrono>

#include "AOS/r1_aos.hpp"
#include "SOA/r2_soa.hpp"

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

static Timings join_build_r1_probe_r2_with_map(const r1_aos &r1, const r2_soa &r2)
{
    Timings out{};
    std::map<std::int64_t, std::vector<std::size_t>> index;

    // Build
    auto t0 = std::chrono::steady_clock::now();
    const auto &r1recs = r1.records();
    for (std::size_t i = 0; i < r1recs.size(); ++i)
    {
        index[r1recs[i].column_a()].push_back(i);
    }
    auto t1 = std::chrono::steady_clock::now();
    out.build_ms = ms_since(t0, t1);

    // Probe
    t0 = std::chrono::steady_clock::now();
    const auto &r2a = r2.column_a();
    for (std::size_t j = 0; j < r2a.size(); ++j)
    {
        auto it = index.find(r2a[j]);
        if (it != index.end())
            out.matches += static_cast<std::uint64_t>(it->second.size());
    }
    t1 = std::chrono::steady_clock::now();
    out.probe_ms = ms_since(t0, t1);

    return out;
}

static Timings join_build_r1_probe_r2_with_unordered_map(const r1_aos &r1, const r2_soa &r2)
{
    Timings out{};
    std::unordered_map<std::int64_t, std::vector<std::size_t>> index;
    index.reserve(r1.size());

    // Build
    auto t0 = std::chrono::steady_clock::now();
    const auto &r1recs = r1.records();
    for (std::size_t i = 0; i < r1recs.size(); ++i)
    {
        index[r1recs[i].column_a()].push_back(i);
    }
    auto t1 = std::chrono::steady_clock::now();
    out.build_ms = ms_since(t0, t1);

    // Probe
    t0 = std::chrono::steady_clock::now();
    const auto &r2a = r2.column_a();
    for (std::size_t j = 0; j < r2a.size(); ++j)
    {
        auto it = index.find(r2a[j]);
        if (it != index.end())
            out.matches += static_cast<std::uint64_t>(it->second.size());
    }
    t1 = std::chrono::steady_clock::now();
    out.probe_ms = ms_since(t0, t1);

    return out;
}

static Timings join_build_r2_probe_r1_with_map(const r2_soa &r2, const r1_aos &r1)
{
    Timings out{};
    std::map<std::int64_t, std::vector<std::size_t>> index;

    // Build
    auto t0 = std::chrono::steady_clock::now();
    const auto &r2a = r2.column_a();
    for (std::size_t j = 0; j < r2a.size(); ++j)
    {
        index[r2a[j]].push_back(j);
    }
    auto t1 = std::chrono::steady_clock::now();
    out.build_ms = ms_since(t0, t1);

    // Probe
    t0 = std::chrono::steady_clock::now();
    const auto &r1recs = r1.records();
    for (std::size_t i = 0; i < r1recs.size(); ++i)
    {
        auto it = index.find(r1recs[i].column_a());
        if (it != index.end())
            out.matches += static_cast<std::uint64_t>(it->second.size());
    }
    t1 = std::chrono::steady_clock::now();
    out.probe_ms = ms_since(t0, t1);

    return out;
}

static Timings join_build_r2_probe_r1_with_unordered_map(const r2_soa &r2, const r1_aos &r1)
{
    Timings out{};
    std::unordered_map<std::int64_t, std::vector<std::size_t>> index;
    index.reserve(r2.size());

    // Build
    auto t0 = std::chrono::steady_clock::now();
    const auto &r2a = r2.column_a();
    for (std::size_t j = 0; j < r2a.size(); ++j)
    {
        index[r2a[j]].push_back(j);
    }
    auto t1 = std::chrono::steady_clock::now();
    out.build_ms = ms_since(t0, t1);

    // Probe
    t0 = std::chrono::steady_clock::now();
    const auto &r1recs = r1.records();
    for (std::size_t i = 0; i < r1recs.size(); ++i)
    {
        auto it = index.find(r1recs[i].column_a());
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

    auto r1 = r1_aos::generate_relation(X, Y);
    auto r2 = r2_soa::generate_relation(X, Y);

    std::cout << "R1 (AoS) size: " << r1.size() << "\n";
    std::cout << "R2 (SoA) size: " << r2.size() << "\n\n";

    print_result("Build R1 (AoS) with std::map, probe R2 (SoA)",
                 join_build_r1_probe_r2_with_map(r1, r2));

    print_result("Build R1 (AoS) with std::unordered_map, probe R2 (SoA)",
                 join_build_r1_probe_r2_with_unordered_map(r1, r2));

    std::cout << "\n";

    print_result("Build R2 (SoA) with std::map, probe R1 (AoS)",
                 join_build_r2_probe_r1_with_map(r2, r1));

    print_result("Build R2 (SoA) with std::unordered_map, probe R1 (AoS)",
                 join_build_r2_probe_r1_with_unordered_map(r2, r1));

    return 0;
}