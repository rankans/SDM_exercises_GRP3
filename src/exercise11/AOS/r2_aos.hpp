#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include <functional>
namespace exercise11
{
    // Relation R2 with distributed partitioning capabilities
    // Schema: R2(A,B) where A=join key, B=payload
    class r2_distributed_aos;
    class r2_distributed_aos_record
    {
    private:
        std::int64_t _column_a; // Join key (column A)
        std::string _column_b;  // Payload (column B)
    public:
        r2_distributed_aos_record(std::int64_t column_a, std::string column_b);
        const std::int64_t &column_a() const noexcept { return _column_a; }
        const std::string &column_b() const noexcept { return _column_b; }
        friend class r2_distributed_aos;
    };
    class r2_distributed_aos
    {
    public:
        using record_type = r2_distributed_aos_record;

    private:
        std::vector<record_type> _records;
        // Hash function for partitioning: partition_id = hash(key) % num_workers
        static size_t partition_hash(std::int64_t key, size_t num_workers)
        {
            return std::hash<std::int64_t>{}(key) % num_workers;
        }

    public:
        r2_distributed_aos() = default;
        // Generate initial relation data for worker
        static r2_distributed_aos generate_relation(size_t X, std::int64_t Y);
        // Phase 1: Local partitioning - split local data into partitions
        std::vector<std::vector<record_type>> local_partitioning_phase(size_t num_workers) const;
        // Phase 2: Shuffle phase - receive partition data from all workers
        void shuffle_phase_receive(const std::vector<record_type> &partition_data);
        // Accessors
        const std::vector<record_type> &records() const noexcept { return _records; }
        size_t size() const noexcept { return _records.size(); }
        // Clear current data (for receiving shuffled data)
        void clear() { _records.clear(); }
    };
}