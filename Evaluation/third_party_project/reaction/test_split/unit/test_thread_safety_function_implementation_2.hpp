

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <atomic>
#include <iostream>
#include <thread>

/**
 * Functional core for: ThreadSafetyTest.SingleToMultiThreadTransition
 *
 * @return tuple: (initialState, valueSingle, multiThreadOperations,
 *                 threadValue, finalState, finalValue)
 */
std::tuple<bool, int, bool, int, bool, int>
runSingleToMultiThreadTransitionScenario() {
    auto &manager = reaction::ThreadManager::getInstance();
    manager.resetForTesting();

    auto sharedVar = reaction::var(0);

    bool initialState = manager.isThreadSafetyEnabled();

    // Step 2: single-thread operation
    sharedVar.value(42);
    int valueSingle = sharedVar.get();

    // Step 3: multi-thread operation
    std::atomic<bool> multiThreadOperations{false};
    std::atomic<int> threadValue{0};

    std::thread multiThread([&]() {
        sharedVar.value(100);
        threadValue = sharedVar.get();
        multiThreadOperations = true;
    });

    multiThread.join();

    bool finalState = manager.isThreadSafetyEnabled();
    int finalValue = sharedVar.get();

    return {initialState,
            valueSingle,
            multiThreadOperations.load(),
            threadValue.load(),
            finalState,
            finalValue};
}

