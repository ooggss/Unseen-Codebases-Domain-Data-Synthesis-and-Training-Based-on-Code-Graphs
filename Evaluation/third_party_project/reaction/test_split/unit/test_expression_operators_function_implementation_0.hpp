

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace expression_operators_impl {

using namespace reaction;

/**
 * Execute comparison operator expressions and return their evaluated results,
 * including dynamic update behavior.
 */
struct ComparisonOperatorsResult {
    bool eq_expr;
    bool neq_expr;
    bool ne_expr;
    bool ne_expr2;
    bool lt_expr_initial;
    bool lt_expr2_initial;
    bool gt_expr_initial;
    bool gt_expr2_initial;
    bool le_expr;
    bool le_expr2;
    bool ge_expr;
    bool ge_expr2;
    bool lt_expr_after_update;
    bool gt_expr2_after_update;
};

ComparisonOperatorsResult run_comparison_operators_scenario() {
    auto a = var(5).setName("a");
    auto b = var(3).setName("b");
    auto c = var(5).setName("c");

    // Test equality
    auto eq_expr = expr(a == c).setName("eq_expr");
    auto neq_expr = expr(a == b).setName("neq_expr");

    // Test inequality
    auto ne_expr = expr(a != b).setName("ne_expr");
    auto ne_expr2 = expr(a != c).setName("ne_expr2");

    // Test less than
    auto lt_expr = expr(b < a).setName("lt_expr");
    auto lt_expr2 = expr(a < b).setName("lt_expr2");

    // Test greater than
    auto gt_expr = expr(a > b).setName("gt_expr");
    auto gt_expr2 = expr(b > a).setName("gt_expr2");

    // Test less than or equal
    auto le_expr = expr(b <= a).setName("le_expr");
    auto le_expr2 = expr(a <= c).setName("le_expr2");

    // Test greater than or equal
    auto ge_expr = expr(a >= b).setName("ge_expr");
    auto ge_expr2 = expr(a >= c).setName("ge_expr2");

    ComparisonOperatorsResult result{
        .eq_expr = eq_expr.get(),
        .neq_expr = neq_expr.get(),
        .ne_expr = ne_expr.get(),
        .ne_expr2 = ne_expr2.get(),
        .lt_expr_initial = lt_expr.get(),
        .lt_expr2_initial = lt_expr2.get(),
        .gt_expr_initial = gt_expr.get(),
        .gt_expr2_initial = gt_expr2.get(),
        .le_expr = le_expr.get(),
        .le_expr2 = le_expr2.get(),
        .ge_expr = ge_expr.get(),
        .ge_expr2 = ge_expr2.get(),
        .lt_expr_after_update = false,   // to be filled after update
        .gt_expr2_after_update = false   // to be filled after update
    };

    // Test dynamic updates
    b.value(7);
    result.lt_expr_after_update = lt_expr.get();   // 7 < 5 is false
    result.gt_expr2_after_update = gt_expr2.get(); // 7 > 5 is true

    return result;
}

} // namespace expression_operators_impl

