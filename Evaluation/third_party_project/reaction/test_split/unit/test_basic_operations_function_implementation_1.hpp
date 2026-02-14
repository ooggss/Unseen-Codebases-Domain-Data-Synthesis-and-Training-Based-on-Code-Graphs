

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
 * Function: run_trigger_flow
 *
 * Purpose:
 *   Encapsulate reactive value updates and triggering behavior.
 *
 * Behavior:
 *   - Creates reactive vars:
 *       a = 1, b = 3.14
 *   - ds  = a + b
 *   - dds = to_string(a) + to_string(ds)
 *   - Then updates a to 2.
 *
 * Returns:
 *   A tuple of:
 *     - int         initial_a
 *     - double      initial_b
 *     - double      initial_ds
 *     - std::string initial_dds
 *     - double      updated_ds
 *     - std::string updated_dds
 */
inline std::tuple<int, double, double, std::string, double, std::string>
run_trigger_flow() {
    auto a = reaction::var(1);
    auto b = reaction::var(3.14);

    auto ds = reaction::calc([](int aa, double bb) { return aa + bb; }, a, b);
    auto dds = reaction::calc(
        [](auto aa, auto dsds) { return std::to_string(aa) + std::to_string(dsds); },
        a,
        ds
    );

    int initial_a = a.get();
    double initial_b = b.get();
    double initial_ds = ds.get();
    std::string initial_dds = dds.get();

    a.value(2);

    double updated_ds = ds.get();
    std::string updated_dds = dds.get();

    return std::make_tuple(
        initial_a,
        initial_b,
        initial_ds,
        initial_dds,
        updated_ds,
        updated_dds
    );
}

}  // namespace basic_operations_test

