#include "r2_aos.hpp"
#include <random>
#include <sstream>
namespace exercise11
{
    r2_distributed_aos_record::r2_distributed_aos_record(std::int64_t column_a, std::string column_b)
        : _column_a(column_a), _column_b(std::move(column_b)) {}
    r2_distributed_aos r2_distributed_aos::generate_relation(size_t X, std::int64_t Y)
    {
        r2_distributed_aos relation;
        relation._records.reserve(X);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<std::int64_t> key_dist(1, Y);
        std::uniform_int_distribution<int> char_dist('A', 'Z');
        for (size_t i = 0; i < X; ++i)
        {
            // Generate random join key between 1 and Y
            std::int64_t key = key_dist(gen);

            // Generate random string payload (8 characters)
            std::string payload;
            payload.reserve(8);
            for (int j = 0; j < 8; ++j)
            {
                payload += static_cast<char>(char_dist(gen));
            }
            relation._records.emplace_back(key, std::move(payload));
        }
        return relation;
    }
    std::vector<std::vector<r2_distributed_aos_record>>
    r2_distributed_aos::local_partitioning_phase(size_t num_workers) const
    {
        // Create partitions for each worker
        std::vector<std::vector<record_type>> partitions(num_workers);

        // Distribute records to partitions based on hash of join key
        for (const auto &record : _records)
        {
            size_t partition_id = partition_hash(record.column_a(), num_workers);
            partitions[partition_id].push_back(record);
        }

        return partitions;
    }
    void r2_distributed_aos::shuffle_phase_receive(const std::vector<record_type> &partition_data)
    {
        // Append received partition data to local records
        _records.insert(_records.end(), partition_data.begin(), partition_data.end());
    }
}