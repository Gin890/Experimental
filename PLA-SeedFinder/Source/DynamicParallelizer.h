/*  Dynamic Parallelizer
 *
 *  From: https://github.com/PokemonAutomation/
 *
 */

#ifndef PokemonAutomation_DynamicParallelizer_H
#define PokemonAutomation_DynamicParallelizer_H

#include <stdint.h>
#include <functional>
#include <vector>
#include <mutex>
#include <thread>

namespace PokemonAutomation{



class DynamicParallelizer{
public:
    DynamicParallelizer(
        std::function<void(uint64_t start, uint64_t length)>&& function,
        uint64_t block_alignment,
        uint64_t total, size_t threads = 0
    );
    ~DynamicParallelizer();

private:
    void thread_loop();

private:
    std::function<void(uint64_t start, uint64_t length)> m_function;
    size_t m_thread_count;
    uint64_t m_total;
    uint64_t m_block_size;

    std::mutex m_lock;
//    std::condition_variable m_cv;
    std::vector<std::thread> m_threads;

    uint64_t m_next;
    uint64_t m_completed;
};




}
#endif
