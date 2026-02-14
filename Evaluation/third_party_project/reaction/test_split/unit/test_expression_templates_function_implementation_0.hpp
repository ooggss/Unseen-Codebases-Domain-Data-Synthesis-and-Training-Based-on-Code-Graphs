

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace expression_templates_test {

/**
 * Function: compute_expr_result
 *
 * Functional logic extracted from the original test:
 * - Create reactive variables a, b, c
 * - Create a derived signal ds = a() + b()
 * - Create an expression expr_ds = c + a / b - ds * 2
 * - Mutate a to 2
 * - Return the final values of ds and expr_ds
 *
 * @return std::pair<int, double> where:
 *         first  = ds.get()
 *         second = expr_ds.get()
 */
std::pair<int, double> compute_expr_result() {
    auto a = reaction::var(1);
    auto b = reaction::var(2);
    auto c = reaction::var(3.14);
    auto ds = reaction::calc([&]() { return a() + b(); });
    auto expr_ds = reaction::expr(c + a / b - ds * 2);

    a.value(2);

    int ds_val = ds.get();
    double expr_val = expr_ds.get();
    return {ds_val, expr_val};
}

}  // namespace expression_templates_test

