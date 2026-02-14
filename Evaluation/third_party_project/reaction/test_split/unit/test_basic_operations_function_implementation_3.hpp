

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace basic_operations_test {

/**
 * Function: run_const_flow
 *
 * Purpose:
 *   Encapsulate behavior of constant reactive variables.
 *
 * Behavior:
 *   - Creates reactive vars:
 *       a = 1 (var)
 *       b = 3.14 (constVar)
 *   - ds = a + b
 *   - Then updates a to 2.
 *
 * Returns:
 *   A tuple of:
 *     - double initial_ds
 *     - double updated_ds
 */
inline std::tuple<double, double> run_const_flow() {
    auto a = reaction::var(1);
    auto b = reaction::constVar(3.14);

    auto ds = reaction::calc([](int aa, double bb) { return aa + bb; }, a, b);

    double initial_ds = ds.get();

    a.value(2);

    double updated_ds = ds.get();

    return std::make_tuple(initial_ds, updated_ds);
}

}  // namespace basic_operations_test

