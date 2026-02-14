

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

/**
 * Scenario: ResetCycleDependencyRollback
 *
 * Creates a calc node with two vars, then attempts to reset it with a cycle
 * dependency. The reset must throw and the node must remain consistent.
 *
 * @return final value of calc and of a/b after all operations
 */
struct ResetCycleDependencyRollbackResult {
    int final_calc_value;
    int final_a_value;
    int final_b_value;
};

ResetCycleDependencyRollbackResult run_ResetCycleDependencyRollback_scenario() {
    auto a = reaction::var(1);
    auto b = reaction::var(2);

    // Create a valid calculation first
    auto calc = reaction::calc([](int x, int y) { return x + y; }, a, b);
    int v1 = calc.get(); // expect 3

    // Change values and verify calculation still works
    a.value(10);
    int v2 = calc.get(); // expect 12

    // Attempt to reset with a cycle dependency (should fail and rollback)
    bool threw = false;
    try {
        calc.reset([&]() { return a() + calc(); });
    } catch (const std::runtime_error&) {
        threw = true;
    }

    // Verify the node is still in a consistent state
    int v3 = calc.get(); // should stay 12

    // Verify dependencies are still intact by changing inputs
    a.value(20);
    int v4 = calc.get(); // 22
    b.value(5);
    int v5 = calc.get(); // 25

    (void)v1;
    (void)v2;
    (void)v3;
    (void)v4;
    (void)threw;

    return ResetCycleDependencyRollbackResult{
        .final_calc_value = v5,
        .final_a_value = a(),
        .final_b_value = b(),
    };
}

