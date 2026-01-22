#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <functional>
namespace exercise11
{
    // Relation R1 with Structure of Arrays (columnar) layout and distributed partitioning
    // Schema: R1(A,B) where A=join key, B=payload
    class r1_distributed_soa
    {
    private:
        std::vector<std::int64_t> _column_a; // Join keys (column A)
        std::vector<std::string> _column_b;  // Payloads (column B)
        // Hash function for partitioning: partition_id = hash(key) % num_workers
        static size_t partition_hash(std::int64_t key, size_t num_workers)
        {
            return std::hash<std::int64_t>{}(key) % num_workers;
        }

    public:
        r1_distributed_soa() = default;
        // Generate initial relation data for worker
        static r1_distributed_soa generate_relation(size_t X, std::int64_t Y);
        // Phase 1: Local partitioning - split local data into partitions
        // Returns vector of partitions, each containing (keys, values) for that partition
        std::vector<std::pair<std::vector<std::int64_t>, std::vector<std::string>>>
        local_partitioning_phase(size_t num_workers) const;
        // Phase 2: Shuffle phase - receive partition data from all workers
        void shuffle_phase_receive(const std::vector<std::int64_t> &keys,
                                   const std::vector<std::string> &values);
        // Accessors
        const std::vector<std::int64_t> &column_a() const noexcept { return _column_a; }
        const std::vector<std::string> &column_b() const noexcept { return _column_b; }
        size_t size() const noexcept { return _column_a.size(); }
        // Clear current data (for receiving shuffled data)
        void clear()
        {
            _column_a.clear();
            _column_b.clear();
        }
    };
}