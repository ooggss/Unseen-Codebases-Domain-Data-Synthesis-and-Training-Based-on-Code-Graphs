#pragma once

#include <reaction/concurrency/thread_manager.h>

namespace test_reaction {

struct SharedMutexResult {
    bool trySharedWithoutSafety;
    bool tryUniqueWhileSharedWithoutSafety;
    bool trySharedWithSafety;
    bool tryUniqueWhileSharedWithSafety;
};

/**
 * Function: Inspect ConditionalSharedMutex behavior across safety modes.
 *
 * @return SharedMutexResult Captures try_lock outcomes before/after enabling thread safety.
 */
inline SharedMutexResult test_conditional_shared_mutex() {
    using namespace reaction;

    auto &tm = ThreadManager::getInstance();
    tm.resetForTesting();

    ConditionalSharedMutex mutex;

    bool trySharedWithoutSafety = mutex.try_lock_shared();
    if (trySharedWithoutSafety) {
        mutex.unlock_shared();
    }

    bool tryUniqueWhileSharedWithoutSafety = false;
    {
        ConditionalSharedLockGuard<ConditionalSharedMutex> sharedGuard(mutex);
        tryUniqueWhileSharedWithoutSafety = mutex.try_lock();
        if (tryUniqueWhileSharedWithoutSafety) {
            mutex.unlock();
        }
    }

    tm.enableThreadSafety();

    bool trySharedWithSafety = mutex.try_lock_shared();
    if (trySharedWithSafety) {
        mutex.unlock_shared();
    }

    bool tryUniqueWhileSharedWithSafety = false;
    {
        ConditionalSharedLockGuard<ConditionalSharedMutex> sharedGuard(mutex);
        tryUniqueWhileSharedWithSafety = mutex.try_lock();
        if (tryUniqueWhileSharedWithSafety) {
            mutex.unlock();
        }
    }

    return SharedMutexResult{
        .trySharedWithoutSafety = trySharedWithoutSafety,
        .tryUniqueWhileSharedWithoutSafety = tryUniqueWhileSharedWithoutSafety,
        .trySharedWithSafety = trySharedWithSafety,
        .tryUniqueWhileSharedWithSafety = tryUniqueWhileSharedWithSafety,
    };
}

}  // namespace test_reaction

