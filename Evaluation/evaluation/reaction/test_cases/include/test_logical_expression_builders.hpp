#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

struct LogicalExpressionSnapshot {
    bool initialAnd;
    bool initialOr;
    bool updatedAnd;
    bool updatedOr;
};

/**
 * Function: Demonstrate logical expression builders and operators on reactive values.
 *
 * This function shows how high-level logical operators (`&&`, `||`) compose reactive
 * expressions that are then lifted into `expr` calculations.
 *
 * @param a Initial value for the first boolean input
 * @param b Initial value for the second boolean input
 * @param c Initial value for the fallback boolean input
 * @return LogicalExpressionSnapshot Snapshot of AND/OR results before and after updates
 */
inline LogicalExpressionSnapshot test_logical_expression_builders(bool a, bool b, bool c) {
    using namespace reaction;

    auto varA = var(a);
    auto varB = var(b);
    auto varC = var(c);

    // Build logical expressions using overloaded operators:
    // andReact  := (A && B)
    // orReact   := (A && B) || C
    auto andReact = expr(varA && varB);
    auto orReact = expr((varA && varB) || varC);

    const bool initialAnd = andReact.get();
    const bool initialOr = orReact.get();

    // Flip inputs to change only B while C stays false
    varB.value(true);
    varC.value(false);

    const bool updatedAnd = andReact.get();
    const bool updatedOr = orReact.get();

    return LogicalExpressionSnapshot{
        .initialAnd = initialAnd,
        .initialOr = initialOr,
        .updatedAnd = updatedAnd,
        .updatedOr = updatedOr,
    };
}

}  // namespace test_reaction


