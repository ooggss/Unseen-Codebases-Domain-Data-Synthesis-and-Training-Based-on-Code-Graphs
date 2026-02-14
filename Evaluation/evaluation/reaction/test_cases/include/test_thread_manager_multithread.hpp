#pragma once

#include <reaction/concurrency/thread_manager.h>
#include <thread>

namespace test_reaction {

struct ThreadSafetyStatus {
    bool safetyBefore;
    bool safetyAfter;
    std::size_t threadCountBefore;
    std::size_t threadCountAfter;
};

/**
 * Function: Detect multi-thread registration enabling thread safety
 *
 * @return ThreadSafetyStatus Snapshots of thread manager state
 */
ThreadSafetyStatus test_thread_manager_multithread() {
    using namespace reaction;

    auto &tm = ThreadManager::getInstance();
    tm.resetForTesting();

    tm.registerThread();
    const std::size_t countBefore = tm.getThreadCount();
    const bool safetyBefore = tm.isThreadSafetyEnabled();

    std::thread worker([]() {
        ThreadManager::getInstance().registerThread();
    });
    worker.join();

    const std::size_t countAfter = tm.getThreadCount();
    const bool safetyAfter = tm.isThreadSafetyEnabled();

    return ThreadSafetyStatus{
        .safetyBefore = safetyBefore,
        .safetyAfter = safetyAfter,
        .threadCountBefore = countBefore,
        .threadCountAfter = countAfter,
    };
}

}  // namespace test_reaction


