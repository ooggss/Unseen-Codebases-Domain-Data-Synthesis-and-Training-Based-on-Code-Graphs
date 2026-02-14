#pragma once

#include <reaction/reaction.h>
#include <memory>
#include <string>

namespace test_reaction {

// ============================================
// Function implementations
// ============================================

/**
 * Function: Test atomic operations on reactive variables
 *
 * @param initialValue Initial value for the reactive variable
 * @param addValue Value to add atomically
 * @return int The final value after atomic addition
 */
int test_atomic_operations(int initialValue, int addValue) {
    using namespace reaction;

    // Create a reactive variable
    auto reactive_var = reaction::var(initialValue);

    // Perform atomic addition
    reactive_var += addValue;

    // Return the final value
    return reactive_var.get();
}

}  // namespace test_reaction