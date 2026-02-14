#pragma once

#include <reaction/reaction.h>
#include <reaction/expression/expression_builders.h>

namespace test_reaction {

struct UnaryExpressionSnapshot {
    int initialNegatedSum;
    int updatedNegatedSum;
    bool logicalNotAfterFlip;
    int bitwiseNotValue;
};

/**
 * Function: Demonstrate unary expression builders and operators on reactive values.
 *
 * This function showcases how low-level expression builder helpers (`make_binary_op`,
 * `make_unary_op`) and high-level unary operators (`-`, `!`, `~`) cooperate with the
 * `expr` factory to produce reactive expressions.
 *
 * @param a First input value participating in the sum expression
 * @param b Second input value participating in the sum expression
 * @return UnaryExpressionSnapshot Snapshot of expression outputs before/after updates
 */
inline UnaryExpressionSnapshot test_unary_expression_builders(int a, int b) {
    using namespace reaction;

    auto varA = var(a);
    auto varB = var(b);

    // Build negated sum directly as a prvalue expression so expr() sees a valid OpExpr
    auto negatedReact = expr(make_unary_op<NegOp>(make_binary_op<AddOp>(varA, varB)));

    auto flag = var(true);
    auto notReact = expr(!flag);

    auto bits = var(0x0F);
    auto bitNotReact = expr(~bits);

    const int initialNegated = negatedReact.get();

    varA.value(a + 1);
    flag.value(false);

    const int updatedNegated = negatedReact.get();
    const bool logicalNot = notReact.get();
    const int bitwiseNot = bitNotReact.get();

    return UnaryExpressionSnapshot{
        .initialNegatedSum = initialNegated,
        .updatedNegatedSum = updatedNegated,
        .logicalNotAfterFlip = logicalNot,
        .bitwiseNotValue = bitwiseNot,
    };
}

}  // namespace test_reaction


