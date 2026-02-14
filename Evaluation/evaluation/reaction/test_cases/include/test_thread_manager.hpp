#pragma once

#include <reaction/concurrency/thread_manager.h>

namespace test_reaction {

// ============================================
// Function implementations
// ============================================

/**
 * Function: Test thread manager registration and safety check
 *
 * @param enableSafety Whether to enable thread safety
 * @return bool Whether thread safety is enabled after operations
 */
bool test_thread_manager_registration(bool enableSafety) {
    using namespace reaction;

    // Get thread manager instance
    auto& tm = ThreadManager::getInstance();

    // Register current thread
    tm.registerThread();

    // Enable thread safety if requested
    if (enableSafety) {
        tm.enableThreadSafety();
    }

    // Return current thread safety status
    return tm.isThreadSafetyEnabled();
}

}  // namespace test_reaction