#include "r1_soa.hpp"
#include <random>
namespace exercise11
{
    r1_distributed_soa r1_distributed_soa::generate_relation(size_t X, std::int64_t Y)
    {
        r1_distributed_soa relation;
        relation._column_a.reserve(X);
        relation._column_b.reserve(X);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<std::int64_t> key_dist(1, Y);
        std::uniform_int_distribution<int> char_dist('A', 'Z');
        for (size_t i = 0; i < X; ++i)
        {
            // Generate random join key between 1 and Y
            std::int64_t key = key_dist(gen);
            relation._column_a.push_back(key);

            // Generate random string payload (8 characters)
            std::string payload;
            payload.reserve(8);
            for (int j = 0; j < 8; ++j)
            {
                payload += static_cast<char>(char_dist(gen));
            }
            relation._column_b.push_back(std::move(payload));
        }
        return relation;
    }
    std::vector<std::pair<std::vector<std::int64_t>, std::vector<std::string>>>
    r1_distributed_soa::local_partitioning_phase(size_t num_workers) const
    {
        // Create partitions for each worker
        std::vector<std::pair<std::vector<std::int64_t>, std::vector<std::string>>> partitions(num_workers);

        // Distribute records to partitions based on hash of join key
        for (size_t i = 0; i < _column_a.size(); ++i)
        {
            size_t partition_id = partition_hash(_column_a[i], num_workers);
            partitions[partition_id].first.push_back(_column_a[i]);  // keys
            partitions[partition_id].second.push_back(_column_b[i]); // values
        }

        return partitions;
    }
    void r1_distributed_soa::shuffle_phase_receive(const std::vector<std::int64_t> &keys,
                                                   const std::vector<std::string> &values)
    {
        // Append received partition data to local columns
        _column_a.insert(_column_a.end(), keys.begin(), keys.end());
        _column_b.insert(_column_b.end(), values.begin(), values.end());
    }
}