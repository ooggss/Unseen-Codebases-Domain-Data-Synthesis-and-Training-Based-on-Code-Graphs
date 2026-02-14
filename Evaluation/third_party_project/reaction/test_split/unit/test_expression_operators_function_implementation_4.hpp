

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace expression_operators_impl {

using namespace reaction;

/**
 * Execute expressions involving operators with different data types and
 * return their evaluated results, including dynamic update behavior.
 */
struct DifferentTypesOperatorsResult {
    bool mixed_expr1_initial;
    bool mixed_expr2;
    bool mixed_expr3_initial;
    bool mixed_expr1_after_update;
    bool mixed_expr3_after_update;
};

DifferentTypesOperatorsResult run_operators_different_types_scenario() {
    auto int_var = var(5).setName("int_var");
    auto float_var = var(3.14).setName("float_var");
    auto bool_var = var(true).setName("bool_var");

    // Test mixed arithmetic and comparison
    auto mixed_expr1 = expr(int_var > float_var).setName("mixed_expr1");

    // Test boolean with arithmetic
    auto mixed_expr2 = expr(bool_var && (int_var > 0)).setName("mixed_expr2");

    // Test floating point division with comparison
    auto mixed_expr3 = expr((int_var / 2) > 2.0).setName("mixed_expr3");

    DifferentTypesOperatorsResult result{
        .mixed_expr1_initial = mixed_expr1.get(), // 5 > 3.14 is true
        .mixed_expr2 = mixed_expr2.get(),         // true && (5>0) is true
        .mixed_expr3_initial = mixed_expr3.get(), // 2.5 > 2.0 is true
        .mixed_expr1_after_update = false,
        .mixed_expr3_after_update = false
    };

    // Update values
    int_var.value(1);
    result.mixed_expr1_after_update = mixed_expr1.get(); // 1 > 3.14 is false
    result.mixed_expr3_after_update = mixed_expr3.get(); // 0.5 > 2.0 is false

    return result;
}

} // namespace expression_operators_impl

