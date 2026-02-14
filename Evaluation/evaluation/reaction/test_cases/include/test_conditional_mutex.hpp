#pragma once

#include <reaction/concurrency/thread_manager.h>

namespace test_reaction {

struct ConditionalMutexResult {
    bool tryLockWithoutSafety;
    bool tryLockWithSafety;
};

/**
 * Function: Compare ConditionalMutex try_lock behavior before and after enabling safety.
 *
 * @return ConditionalMutexResult Snapshot indicating whether try_lock succeeds under different modes.
 */
inline ConditionalMutexResult test_conditional_mutex_behavior() {
    using namespace reaction;

    auto &tm = ThreadManager::getInstance();
    tm.resetForTesting();

    ConditionalMutex mutex;

    bool tryLockWithoutSafety = false;
    {
        ConditionalLockGuard<ConditionalMutex> guard(mutex);
        tryLockWithoutSafety = mutex.try_lock();
    }

    tm.enableThreadSafety();

    bool tryLockWithSafety = false;
    {
        ConditionalLockGuard<ConditionalMutex> guard(mutex);
        tryLockWithSafety = mutex.try_lock();
    }

    return ConditionalMutexResult{
        .tryLockWithoutSafety = tryLockWithoutSafety,
        .tryLockWithSafety = tryLockWithSafety,
    };
}

}  // namespace test_reaction

