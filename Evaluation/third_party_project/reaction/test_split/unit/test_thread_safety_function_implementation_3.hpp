

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <atomic>
#include <iostream>
#include <thread>

/**
 * Functional core for: ThreadSafetyTest.ThreadRegistrationMechanism
 *
 * @return tuple: (initialCount, afterOperationCount, threadCountAfterMulti,
 *                 initialSafetyState)
 */
std::tuple<size_t, size_t, size_t, bool>
runThreadRegistrationMechanismScenario() {
    auto &manager = reaction::ThreadManager::getInstance();
    manager.resetForTesting();

    // Test 1: verify thread count
    size_t initialCount = manager.getThreadCount();

    auto var = reaction::var(42);
    var.get(); // triggers registration

    size_t afterOperationCount = manager.getThreadCount();

    // Test 2: verify multi-thread registration
    std::atomic<size_t> threadCountAfterMulti{0};
    std::thread testThread([&]() {
        auto localVar = reaction::var(100);
        localVar.get();
        threadCountAfterMulti = manager.getThreadCount();
    });

    testThread.join();

    // Test 3: check state change
    bool initialSafetyState = manager.isThreadSafetyEnabled();

    return {initialCount,
            afterOperationCount,
            threadCountAfterMulti.load(),
            initialSafetyState};
}

