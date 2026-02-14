#pragma once

#include <reaction/concurrency/thread_manager.h>

namespace test_reaction {

struct ThreadSafetyTransition {
    bool beforeEnable;
    bool afterEnable;
    bool afterReset;
    std::size_t threadCount;
};

/**
 * Function: Manually toggle thread safety mode and observe state transitions
 *
 * @return ThreadSafetyTransition Snapshot of safety flags around enable/reset
 */
ThreadSafetyTransition test_thread_manager_manual() {
    using namespace reaction;

    auto &tm = ThreadManager::getInstance();
    tm.resetForTesting();

    tm.registerThread();
    const std::size_t countAfterRegister = tm.getThreadCount();
    const bool safetyBeforeEnable = tm.isThreadSafetyEnabled();

    tm.enableThreadSafety();
    const bool safetyAfterEnable = tm.isThreadSafetyEnabled();

    tm.resetForTesting();
    const bool safetyAfterReset = tm.isThreadSafetyEnabled();

    return ThreadSafetyTransition{
        .beforeEnable = safetyBeforeEnable,
        .afterEnable = safetyAfterEnable,
        .afterReset = safetyAfterReset,
        .threadCount = countAfterRegister,
    };
}

}  // namespace test_reaction


