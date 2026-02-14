

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

/**
 * Function: simulate_copy_memory_management
 *
 * Purpose:
 *   Construct some reactive variables, perform a copy operation,
 *   then return their observable string values before and after
 *   changing the source variable.
 *
 * Returns:
 *   A tuple of four strings:
 *     0: initial value of dds_copy.get()
 *     1: initial value of dds.get()
 *     2: value of dds_copy.get() after a.value(2)
 *     3: value of dds.get() after a.value(2)
 */
std::tuple<std::string, std::string, std::string, std::string>
simulate_copy_memory_management() {
    auto a = reaction::var(1);
    auto b = reaction::var(3.14);
    auto ds = reaction::calc(
        [](int aa, double bb) {
            return std::to_string(aa) + std::to_string(bb);
        },
        a, b);
    auto dds = reaction::calc(
        [](auto aa, auto dsds) {
            return std::to_string(aa) + dsds;
        },
        a, ds);

    auto dds_copy = dds;

    // Initial observed values
    const auto initial_copy = dds_copy.get();
    const auto initial_dds  = dds.get();

    // Mutate source variable
    a.value(2);

    // Observed values after mutation
    const auto updated_copy = dds_copy.get();
    const auto updated_dds  = dds.get();

    return {initial_copy, initial_dds, updated_copy, updated_dds};
}

