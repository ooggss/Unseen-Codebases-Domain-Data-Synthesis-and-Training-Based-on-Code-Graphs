#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

// ============================================
// Function implementations
// ============================================

/**
 * Function: Test reactive update chain with multiple dependent calculations
 *
 * @param a First input value
 * @param b Second input value
 * @param newA New value for a
 * @return int The result of the final calculation after updating a
 */
int test_reactive_update_chain(int a, int b, int newA) {
    using namespace reaction;

    // Create reactive variables
    auto varA = var(a);
    auto varB = var(b);

    // Create first calculation: sum = a + b
    auto sum = calc([](int x, int y) {
        return x + y;
    }, varA, varB);

    // Create second calculation that depends on first: product = sum * 2
    auto product = calc([](int s) {
        return s * 2;
    }, sum);

    // Update varA - this should trigger updates in both sum and product
    varA.value(newA);

    // Return the final product value (should reflect the update)
    return product.get();
}

}  // namespace test_reaction

