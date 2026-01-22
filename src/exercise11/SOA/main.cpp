#include "r1_soa.hpp"
#include "r2_soa.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace exercise11;
// Distributed Worker for SOA Partitioning and Shuffle
class DistributedWorkerSOA
{
public:
    int worker_id;
    r1_distributed_soa r1_local;
    r2_distributed_soa r2_local;
    DistributedWorkerSOA(int id) : worker_id(id) {}
    void generate_local_data(size_t records_per_worker, std::int64_t key_range)
    {
        std::cout << "Worker " << worker_id << ": Generating local data...\n";
        r1_local = r1_distributed_soa::generate_relation(records_per_worker, key_range);
        r2_local = r2_distributed_soa::generate_relation(records_per_worker, key_range);
        std::cout << "Worker " << worker_id << ": Generated R1(" << r1_local.size()
                  << ") R2(" << r2_local.size() << ")\n";
    }
};
// Correctness verification for SOA: Check that all tuples with same join key end up on same worker
void verify_correctness_soa(const std::vector<DistributedWorkerSOA> &workers)
{
    std::cout << "\n=== Correctness Verification (SOA) ===\n";

    // Track which worker each join key is assigned to
    std::unordered_map<std::int64_t, int> key_to_worker_r1;
    std::unordered_map<std::int64_t, int> key_to_worker_r2;

    bool correctness_passed = true;

    // Check R1 key distribution (columnar access)
    for (size_t worker_i = 0; worker_i < workers.size(); ++worker_i)
    {
        std::unordered_set<std::int64_t> worker_keys;
        const auto &r1_keys = workers[worker_i].r1_local.column_a();

        for (std::int64_t key : r1_keys)
        {
            worker_keys.insert(key);

            // Check if this key was already seen on a different worker
            if (key_to_worker_r1.find(key) != key_to_worker_r1.end())
            {
                if (key_to_worker_r1[key] != static_cast<int>(worker_i))
                {
                    std::cout << "CORRECTNESS VIOLATION: R1 key " << key
                              << " found on both worker " << key_to_worker_r1[key]
                              << " and worker " << worker_i << "\n";
                    correctness_passed = false;
                }
            }
            else
            {
                key_to_worker_r1[key] = static_cast<int>(worker_i);
            }
        }
        std::cout << "Worker " << worker_i << " R1: " << worker_keys.size() << " distinct keys\n";
    }

    // Check R2 key distribution (columnar access)
    for (size_t worker_i = 0; worker_i < workers.size(); ++worker_i)
    {
        std::unordered_set<std::int64_t> worker_keys;
        const auto &r2_keys = workers[worker_i].r2_local.column_a();

        for (std::int64_t key : r2_keys)
        {
            worker_keys.insert(key);

            // Check if this key was already seen on a different worker
            if (key_to_worker_r2.find(key) != key_to_worker_r2.end())
            {
                if (key_to_worker_r2[key] != static_cast<int>(worker_i))
                {
                    std::cout << "CORRECTNESS VIOLATION: R2 key " << key
                              << " found on both worker " << key_to_worker_r2[key]
                              << " and worker " << worker_i << "\n";
                    correctness_passed = false;
                }
            }
            else
            {
                key_to_worker_r2[key] = static_cast<int>(worker_i);
            }
        }
        std::cout << "Worker " << worker_i << " R2: " << worker_keys.size() << " distinct keys\n";
    }

    // Verify R1 and R2 key assignments match
    for (const auto &[key, worker_r1] : key_to_worker_r1)
    {
        if (key_to_worker_r2.find(key) != key_to_worker_r2.end())
        {
            int worker_r2 = key_to_worker_r2[key];
            if (worker_r1 != worker_r2)
            {
                std::cout << "CORRECTNESS VIOLATION: Key " << key
                          << " on different workers - R1: worker " << worker_r1
                          << ", R2: worker " << worker_r2 << "\n";
                correctness_passed = false;
            }
        }
    }

    if (correctness_passed)
    {
        std::cout << "CORRECTNESS VERIFIED: All tuples with same join key on same worker (SOA)\n";
    }
    else
    {
        std::cout << "CORRECTNESS FAILED: Key distribution violations found (SOA)\n";
    }
}
// Simulate distributed partitioning and shuffle for SOA
void simulate_distributed_partitioning_shuffle_soa(std::vector<DistributedWorkerSOA> &workers)
{
    size_t num_workers = workers.size();
    std::cout << "\n=== Phase 1: Local Partitioning (SOA) ===\n";
    // Store all partitions from all workers
    using SOAPartition = std::pair<std::vector<std::int64_t>, std::vector<std::string>>;
    std::vector<std::vector<SOAPartition>> r1_all_partitions(num_workers);
    std::vector<std::vector<SOAPartition>> r2_all_partitions(num_workers);
    // Each worker partitions its local data
    for (size_t worker_i = 0; worker_i < num_workers; ++worker_i)
    {
        std::cout << "Worker " << worker_i << ": Partitioning local data using hash(join_key) % " << num_workers << "...\n";
        r1_all_partitions[worker_i] = workers[worker_i].r1_local.local_partitioning_phase(num_workers);
        r2_all_partitions[worker_i] = workers[worker_i].r2_local.local_partitioning_phase(num_workers);
        // Show partition sizes
        std::cout << "Worker " << worker_i << " R1 partitions: ";
        for (size_t p = 0; p < num_workers; ++p)
        {
            std::cout << "P" << p << "(" << r1_all_partitions[worker_i][p].first.size() << ") ";
        }
        std::cout << "\n";
        std::cout << "Worker " << worker_i << " R2 partitions: ";
        for (size_t p = 0; p < num_workers; ++p)
        {
            std::cout << "P" << p << "(" << r2_all_partitions[worker_i][p].first.size() << ") ";
        }
        std::cout << "\n";
    }
    std::cout << "\n=== Phase 2: Shuffle (All-to-All Exchange) ===\n";
    // Clear workers' local data to receive shuffled data
    for (auto &worker : workers)
    {
        worker.r1_local.clear();
        worker.r2_local.clear();
    }
    // Each worker receives its designated partition from all other workers
    for (size_t receiver_worker = 0; receiver_worker < num_workers; ++receiver_worker)
    {
        std::cout << "Worker " << receiver_worker << ": Receiving partition " << receiver_worker << " from all workers...\n";
        size_t total_r1_received = 0;
        size_t total_r2_received = 0;
        // Receive partition data from all workers (including self)
        for (size_t sender_worker = 0; sender_worker < num_workers; ++sender_worker)
        {
            const auto &r1_partition = r1_all_partitions[sender_worker][receiver_worker];
            const auto &r2_partition = r2_all_partitions[sender_worker][receiver_worker];
            workers[receiver_worker].r1_local.shuffle_phase_receive(r1_partition.first, r1_partition.second);
            workers[receiver_worker].r2_local.shuffle_phase_receive(r2_partition.first, r2_partition.second);
            total_r1_received += r1_partition.first.size();
            total_r2_received += r2_partition.first.size();
        }
        std::cout << "Worker " << receiver_worker << ": Received R1(" << total_r1_received
                  << ") R2(" << total_r2_received << ") total records\n";
    }
    std::cout << "\n=== Distributed Partitioning and Shuffle Complete ===\n";
    for (size_t worker_i = 0; worker_i < num_workers; ++worker_i)
    {
        std::cout << "Worker " << worker_i << ": Final partitioned data - R1("
                  << workers[worker_i].r1_local.size() << ") R2("
                  << workers[worker_i].r2_local.size() << ")\n";
    }
}
int main()
{
    std::cout << "=== Exercise 11: Distributed Partitioning and Shuffle (SOA) ===\n\n";
    // Test with N ∈ {2, 4, 8} workers as required
    std::vector<size_t> worker_counts = {2, 4, 8};
    for (size_t num_workers : worker_counts)
    {
        std::cout << "\n"
                  << std::string(60, '=') << "\n";
        std::cout << "TESTING WITH " << num_workers << " WORKERS (SOA)\n";
        std::cout << std::string(60, '=') << "\n";
        // Create distributed workers
        std::vector<DistributedWorkerSOA> workers;
        workers.reserve(num_workers);
        for (size_t i = 0; i < num_workers; ++i)
        {
            workers.emplace_back(static_cast<int>(i));
        }
        // Each worker generates local data
        size_t records_per_worker = 1000; // 1K records per worker initially
        std::int64_t key_range = 100;     // Keys range from 1 to 100
        std::cout << "\n=== Initial Data Generation (SOA) ===\n";
        for (auto &worker : workers)
        {
            worker.generate_local_data(records_per_worker, key_range);
        }
        // Perform distributed partitioning and shuffle
        simulate_distributed_partitioning_shuffle_soa(workers);

        // Verify correctness
        verify_correctness_soa(workers);
    }
    std::cout << "\n=== Summary (SOA Layout) ===\n";
    std::cout << "Demonstrated distributed partitioning and shuffle with columnar storage:\n";
    std::cout << "1. Local Partitioning: Each worker partitions data by hash(join_key) % num_workers\n";
    std::cout << "2. Shuffle Phase: All-to-all exchange where worker i gets partition i from everyone\n";
    std::cout << "3. Correctness Verification: Ensures all tuples with same join key end up on same worker\n";
    std::cout << "4. Schema: R1(A,B) and R2(A,B) where A=join key, B=payload (columnar layout)\n";
    std::cout << "5. Tested with N ∈ {2, 4, 8} distributed worker nodes\n";
    return 0;
}