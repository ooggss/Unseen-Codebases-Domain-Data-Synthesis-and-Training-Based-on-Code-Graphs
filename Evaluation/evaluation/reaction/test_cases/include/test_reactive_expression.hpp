#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

// ============================================
// Function implementations
// ============================================

/**
 * Function: Test reactive expression using expr API
 *
 * @param a First input value
 * @param b Second input value
 * @return int The result of (a + b) * 2 using expr syntax
 */
int test_reactive_expression(int a, int b) {
    using namespace reaction;

    // Create reactive variables
    auto varA = var(a);
    auto varB = var(b);

    // Create a reactive expression using expr: (a + b) * 2
    // expr allows declarative syntax with operator overloads
    auto expression = expr((varA + varB) * 2);

    // Return the expression result
    return expression.get();
}

}  // namespace test_reaction

