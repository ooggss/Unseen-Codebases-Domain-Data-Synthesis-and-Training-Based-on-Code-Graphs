

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace dependency_graph_test_reset {

/**
 * Function: test_reset_behavior
 *
 * Encapsulates the logic that was previously inside the
 * DependencyGraphTest.TestReset test body.
 *
 * @return The resulting value of dds.get() after reset logic and updates.
 */
int test_reset_behavior() {
    auto a = reaction::var(1);
    auto b = reaction::var(2);

    auto ds = reaction::calc([](auto aa, auto bb) { return aa + bb; }, a, b);

    auto dds = reaction::calc([](auto aa, auto bb) { return aa + bb; }, a, b);

    dds.reset([&]() { return a() + ds(); });
    a.value(2);
    return dds.get();
}

}  // namespace dependency_graph_test_reset

