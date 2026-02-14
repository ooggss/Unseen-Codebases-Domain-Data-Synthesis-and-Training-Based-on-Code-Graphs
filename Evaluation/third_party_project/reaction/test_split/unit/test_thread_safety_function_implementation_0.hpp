

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

/**
 * Functional core for: ThreadSafetyTest.SingleThreadAutoDisable
 *
 * @return tuple: (initialState, value1, value2, afterSingleThread)
 */
std::tuple<bool, int, int, bool> runSingleThreadAutoDisableScenario() {
    // Reset thread safety manager state (for testing purpose)
    auto &manager = reaction::ThreadManager::getInstance();
    manager.resetForTesting();

    // Check initial state before creating variables
    bool initialState = manager.isThreadSafetyEnabled();

    // Create variable and perform operations
    auto var = reaction::var(42);
    int value1 = var.get(); // This triggers REACTION_REGISTER_THREAD
    var.value(100);
    int value2 = var.get();

    // Check thread safety state
    bool afterSingleThread = manager.isThreadSafetyEnabled();

    return {initialState, value1, value2, afterSingleThread};
}

