#pragma once

#include <reaction/concurrency/thread_manager.h>
#include <thread>

namespace test_reaction {

/**
 * Struct: ForceRegisterSnapshot
 *
 * Collects observable state around calls to ThreadManager registration APIs.
 */
struct ForceRegisterSnapshot {
    bool safetyBeforeForce;
    bool safetyAfterMainForce;
    bool safetyAfterWorkerForce;
};

/**
 * Function: test_thread_manager_force_register
 *
 * Demonstrates how registering multiple distinct threads causes
 * ThreadManager to enable thread safety.
 *
 * - We start from a clean ThreadManager state.
 * - The main thread registers itself and remains the sole thread.
 * - A worker thread then also registers, which should trigger
 *   multi-thread detection and enable thread safety.
 *
 * @return ForceRegisterSnapshot
 *         A snapshot of the thread-safety flag before any registration,
 *         after the main-thread registration, and after the worker-thread registration.
 */
inline ForceRegisterSnapshot test_thread_manager_force_register() {
    using namespace reaction;

    auto &tm = ThreadManager::getInstance();
    tm.resetForTesting();

    const bool safetyBefore = tm.isThreadSafetyEnabled();

    tm.registerThread();
    const bool safetyAfterMainForce = tm.isThreadSafetyEnabled();

    std::thread worker([] {
        ThreadManager::getInstance().registerThread();
    });
    worker.join();

    const bool safetyAfterWorkerForce = tm.isThreadSafetyEnabled();

    return ForceRegisterSnapshot{
        .safetyBeforeForce = safetyBefore,
        .safetyAfterMainForce = safetyAfterMainForce,
        .safetyAfterWorkerForce = safetyAfterWorkerForce,
    };
}

}  // namespace test_reaction


