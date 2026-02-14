#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

// ============================================
// Function implementations
// ============================================

/**
 * Function: Test reactive calculation with dependencies
 *
 * @param a First input value
 * @param b Second input value
 * @return int The result of (a + b) * 2
 */
int test_reactive_calculation(int a, int b) {
    using namespace reaction;

    // Create reactive variables
    auto varA = var(a);
    auto varB = var(b);

    // Create a reactive calculation: (a + b) * 2
    auto calculation = calc([] (int x, int y) {
        return (x + y) * 2;
    }, varA, varB);

    // Return the calculated result
    return calculation.get();
}

}  // namespace test_reaction