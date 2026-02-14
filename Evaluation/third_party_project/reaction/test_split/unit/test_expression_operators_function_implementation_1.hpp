

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace expression_operators_impl {

using namespace reaction;

/**
 * Execute logical operator expressions and return their evaluated results,
 * including dynamic update behavior.
 */
struct LogicalOperatorsResult {
    bool and_expr1;
    bool and_expr2_initial;
    bool or_expr1;
    bool or_expr2_initial;
    bool complex_expr;
    bool and_expr2_after_update;
    bool or_expr2_after_update;
};

LogicalOperatorsResult run_logical_operators_scenario() {
    auto a = var(true).setName("a");
    auto b = var(false).setName("b");
    auto c = var(true).setName("c");

    // Test logical AND
    auto and_expr1 = expr(a && c).setName("and_expr1");
    auto and_expr2 = expr(a && b).setName("and_expr2");

    // Test logical OR
    auto or_expr1 = expr(a || b).setName("or_expr1");
    auto or_expr2 = expr(b || b).setName("or_expr2");

    // Test complex logical expressions
    auto complex_expr = expr((a && c) || b).setName("complex_expr");

    LogicalOperatorsResult result{
        .and_expr1 = and_expr1.get(),
        .and_expr2_initial = and_expr2.get(),
        .or_expr1 = or_expr1.get(),
        .or_expr2_initial = or_expr2.get(),
        .complex_expr = complex_expr.get(),
        .and_expr2_after_update = false, // to be filled after update
        .or_expr2_after_update = false   // to be filled after update
    };

    // Test dynamic updates
    b.value(true);
    result.and_expr2_after_update = and_expr2.get(); // true && true is true
    result.or_expr2_after_update = or_expr2.get();   // true || true is true

    return result;
}

} // namespace expression_operators_impl

