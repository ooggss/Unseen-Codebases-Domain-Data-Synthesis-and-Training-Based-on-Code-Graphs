#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

// ============================================
// Function implementations
// ============================================

/**
 * Function: Test resetting a calculation node with new dependencies
 *
 * @param a First input value
 * @param b Second input value
 * @param c Third input value
 * @return int The result after resetting calculation to use different dependencies
 */
int test_calculation_reset(int a, int b, int c) {
    using namespace reaction;

    // Create reactive variables
    auto varA = var(a);
    auto varB = var(b);
    auto varC = var(c);

    // Create initial calculation: result = a + b
    auto calculation = calc([](int x, int y) {
        return x + y;
    }, varA, varB);

    // Reset calculation to use different dependencies: result = b + c
    calculation.reset([](int y, int z) {
        return y + z;
    }, varB, varC);

    // Return the result after reset
    return calculation.get();
}

}  // namespace test_reaction

