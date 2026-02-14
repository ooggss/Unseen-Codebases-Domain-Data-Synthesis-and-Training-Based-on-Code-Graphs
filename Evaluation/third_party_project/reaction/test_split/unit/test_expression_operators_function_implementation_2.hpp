

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace expression_operators_impl {

using namespace reaction;

/**
 * Execute unary operator expressions and return their evaluated results,
 * including dynamic update behavior.
 */
struct UnaryOperatorsResult {
    int neg_expr1_initial;
    int neg_expr2;
    bool not_expr1_initial;
    bool not_expr2;
    int bitnot_expr;
    int neg_expr1_after_update;
    bool not_expr1_after_update;
};

UnaryOperatorsResult run_unary_operators_scenario() {
    auto a = var(5).setName("a");
    auto b = var(-3).setName("b");
    auto bool_var = var(true).setName("bool_var");
    auto int_var = var(0b1010).setName("int_var"); // 10 in binary

    // Test unary negation
    auto neg_expr1 = expr(-a).setName("neg_expr1");
    auto neg_expr2 = expr(-b).setName("neg_expr2");

    // Test logical NOT
    auto not_expr1 = expr(!bool_var).setName("not_expr1");
    auto not_expr2 = expr(!(a == 5)).setName("not_expr2");

    // Test bitwise NOT
    auto bitnot_expr = expr(~int_var).setName("bitnot_expr");

    UnaryOperatorsResult result{
        .neg_expr1_initial = neg_expr1.get(),
        .neg_expr2 = neg_expr2.get(),
        .not_expr1_initial = not_expr1.get(),
        .not_expr2 = not_expr2.get(),
        .bitnot_expr = bitnot_expr.get(),
        .neg_expr1_after_update = 0,  // to be filled after update
        .not_expr1_after_update = false // to be filled after update
    };

    // Test dynamic updates
    a.value(-10);
    result.neg_expr1_after_update = neg_expr1.get();

    bool_var.value(false);
    result.not_expr1_after_update = not_expr1.get();

    return result;
}

} // namespace expression_operators_impl

