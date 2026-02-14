

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
 * Function: run_basic_calc
 *
 * Purpose:
 *   Encapsulate the basic calculation flow using reaction::var and reaction::calc.
 *
 * Behavior:
 *   - Creates two reactive variables: a = 1 (int), b = 3.14 (double).
 *   - Creates three derived reactive values:
 *       ds   = a + b
 *       dds  = to_string(a) + to_string(ds)
 *       ddds = 1 (constant)
 *
 * Returns:
 *   A tuple of:
 *     - int                  a_value
 *     - double               b_value
 *     - double               ds_value
 *     - std::string          dds_value
 *     - int                  ddds_value
 */
inline std::tuple<int, double, double, std::string, int> run_basic_calc() {
    auto a = reaction::var(1);
    auto b = reaction::var(3.14);

    auto ds = reaction::calc([](int aa, double bb) { return aa + bb; }, a, b);
    auto dds = reaction::calc(
        [](int aa, double dsds) { return std::to_string(aa) + std::to_string(dsds); },
        a,
        ds
    );
    auto ddds = reaction::calc([]() { return 1; });

    return std::make_tuple(a.get(), b.get(), ds.get(), dds.get(), ddds.get());
}

}  // namespace basic_operations_test

