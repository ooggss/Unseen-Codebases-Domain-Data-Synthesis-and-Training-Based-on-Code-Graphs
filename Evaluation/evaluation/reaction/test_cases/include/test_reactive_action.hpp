#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

// ============================================
// Function implementations
// ============================================

/**
 * Function: Test reactive action with side effects
 *
 * @param initialValue Initial value for the reactive variable
 * @param newValue New value to set
 * @return int The value captured by the action (should be newValue after update)
 */
int test_reactive_action(int initialValue, int newValue) {
    using namespace reaction;

    // Create a reactive variable
    auto reactiveVar = var(initialValue);

    // Create a variable to capture side effect
    int capturedValue = 0;

    // Create a reactive action that captures the value when reactiveVar changes
    // Using parameter binding style for high performance
    auto sideEffect = action([&capturedValue](int value) {
        capturedValue = value;
    }, reactiveVar);

    // Update the reactive variable - this should trigger the action
    reactiveVar.value(newValue);

    // Return the captured value
    return capturedValue;
}

}  // namespace test_reaction

