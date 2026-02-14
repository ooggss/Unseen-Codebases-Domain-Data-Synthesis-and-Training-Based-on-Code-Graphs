#pragma once

#include <reaction/concurrency/thread_manager.h>
#include <thread>

namespace test_reaction {

struct ThreadGuardState {
    bool safetyBeforeGuard;
    bool safetyAfterGuard;
    std::size_t threadCountBeforeGuard;
    std::size_t threadCountAfterGuard;
};

/**
 * Function: Use ThreadRegistrationGuard in a worker thread to enable safety
 *
 * @return ThreadGuardState Safety flags and thread counts before/after guard usage
 */
ThreadGuardState test_thread_guard() {
    using namespace reaction;

    auto &tm = ThreadManager::getInstance();
    tm.resetForTesting();

    const bool safetyBefore = tm.isThreadSafetyEnabled();
    const std::size_t countBefore = tm.getThreadCount();

    std::thread worker([]() {
        ThreadRegistrationGuard guard;
        (void)guard;
    });
    worker.join();

    const bool safetyAfter = tm.isThreadSafetyEnabled();
    const std::size_t countAfter = tm.getThreadCount();

    return ThreadGuardState{
        .safetyBeforeGuard = safetyBefore,
        .safetyAfterGuard = safetyAfter,
        .threadCountBeforeGuard = countBefore,
        .threadCountAfterGuard = countAfter,
    };
}

}  // namespace test_reaction


