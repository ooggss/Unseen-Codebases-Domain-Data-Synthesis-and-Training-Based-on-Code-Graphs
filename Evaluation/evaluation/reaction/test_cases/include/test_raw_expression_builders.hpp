#pragma once

#include <reaction/reaction.h>
#include <reaction/expression/expression_builders.h>

namespace test_reaction {

/**
 * Struct: RawExpressionSnapshot
 *
 * Captures the values produced by raw expression builder helpers
 * (`make_binary_expr`, `make_unary_expr`) before and after updating
 * their reactive inputs.
 */
struct RawExpressionSnapshot {
    int initialSum;
    int initialNegatedSum;
    int initialChainedValue;

    int updatedSum;
    int updatedNegatedSum;
    int updatedChainedValue;
};

/**
 * Function: test_raw_expression_builders
 *
 * Demonstrates how low-level expression builder helpers
 * (`make_binary_expr`, `make_unary_expr`) can be combined with
 * `expr` to build reactive calculations without using the higher
 * level `make_binary_op` / `make_unary_op` shortcuts.
 *
 * The function:
 * - Creates three reactive integers A, B, C.
 * - Builds sum = A + B via make_binary_expr.
 * - Builds negated = -(A + B) via make_unary_expr(make_binary_expr(...)).
 * - Builds chained = -(A + B) * C via nested make_* calls.
 * - Updates A and C and records all expression values before and after.
 *
 * @param a Initial value for the first input
 * @param b Initial value for the second input
 * @param c Initial value for the chaining multiplier
 * @return RawExpressionSnapshot
 *         Snapshot of sum / negated / chained values before and after updates.
 */
inline RawExpressionSnapshot test_raw_expression_builders(int a, int b, int c) {
    using namespace reaction;

    auto varA = var(a);
    auto varB = var(b);
    auto varC = var(c);

    // Build (A + B) using the raw binary expression helper.
    auto sumReact = expr(make_binary_expr<AddOp>(varA, varB));

    // Build -(A + B) using a nested unary expression helper.
    auto negatedReact =
        expr(make_unary_expr<NegOp>(make_binary_expr<AddOp>(varA, varB)));

    // Build chained = -(A + B) * C using nested builders only.
    auto chainedReact = expr(make_binary_expr<MulOp>(
        make_unary_expr<NegOp>(make_binary_expr<AddOp>(varA, varB)), varC));

    const int initialSum = sumReact.get();
    const int initialNegated = negatedReact.get();
    const int initialChained = chainedReact.get();

    // Update inputs to re-trigger the expression graph.
    varA.value(a + 1);
    varC.value(c + 1);

    const int updatedSum = sumReact.get();
    const int updatedNegated = negatedReact.get();
    const int updatedChained = chainedReact.get();

    return RawExpressionSnapshot{
        .initialSum = initialSum,
        .initialNegatedSum = initialNegated,
        .initialChainedValue = initialChained,
        .updatedSum = updatedSum,
        .updatedNegatedSum = updatedNegated,
        .updatedChainedValue = updatedChained,
    };
}

}  // namespace test_reaction


