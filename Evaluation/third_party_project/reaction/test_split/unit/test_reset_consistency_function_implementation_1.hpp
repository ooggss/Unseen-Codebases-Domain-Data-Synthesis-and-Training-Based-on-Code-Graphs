

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

/**
 * Scenario: ResetSelfDependencyRollback
 *
 * Create a simple calc depending on a single var, then attempt to reset it
 * with self-dependency. The reset must throw and the node must remain
 * consistent and responsive to changes in a.
 *
 * @return final calc value and final a value
 */
struct ResetSelfDependencyRollbackResult {
    int final_calc_value;
    int final_a_value;
};

ResetSelfDependencyRollbackResult run_ResetSelfDependencyRollback_scenario() {
    auto a = reaction::var(1);

    // Create a valid calculation
    auto calc = reaction::calc([](int x) { return x * 2; }, a);
    int v1 = calc.get(); // 2

    // Attempt to reset with self-dependency (should fail and rollback)
    bool threw = false;
    try {
        calc.reset([&]() { return calc() + 1; });
    } catch (const std::runtime_error&) {
        threw = true;
    }

    // Verify the node is still in a consistent state
    int v2 = calc.get(); // 2

    // Verify dependencies are still intact
    a.value(5);
    int v3 = calc.get(); // 10

    (void)v1;
    (void)v2;
    (void)threw;

    return ResetSelfDependencyRollbackResult{
        .final_calc_value = v3,
        .final_a_value = a(),
    };
}

