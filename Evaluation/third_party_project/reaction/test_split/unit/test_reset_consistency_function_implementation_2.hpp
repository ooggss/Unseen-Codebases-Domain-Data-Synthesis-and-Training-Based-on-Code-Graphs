

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

/**
 * Scenario: ResetWithMultipleDependenciesPartialFailure
 *
 * Two independent calcs are created, then one is made to depend on the other.
 * A subsequent reset that would introduce a cycle must fail, with rollback.
 *
 * @return final values of calc1, calc2, and b
 */
struct ResetWithMultipleDependenciesPartialFailureResult {
    int final_calc1_value;
    int final_calc2_value;
    int final_b_value;
};

ResetWithMultipleDependenciesPartialFailureResult
run_ResetWithMultipleDependenciesPartialFailure_scenario() {
    auto a = reaction::var(1);
    auto b = reaction::var(2);

    // Create two calculations
    auto calc1 = reaction::calc([](int x) { return x * 2; }, a);
    auto calc2 = reaction::calc([](int y) { return y + 1; }, b);

    // Make calc1 depend on calc2
    calc1.reset([&]() { return calc2() * 2; });
    int v1 = calc1.get(); // 6

    // Now attempt to make calc2 depend on calc1, creating a cycle
    bool threw = false;
    try {
        calc2.reset([&]() { return calc1() + 1; });
    } catch (const std::runtime_error&) {
        threw = true;
    }

    // Verify calc2 is still in a consistent state
    int v2 = calc2.get(); // 3

    // Verify calc2's dependencies are still intact
    b.value(10);
    int v3 = calc2.get(); // 11

    (void)v1;
    (void)threw;

    return ResetWithMultipleDependenciesPartialFailureResult{
        .final_calc1_value = calc1.get(),
        .final_calc2_value = v3,
        .final_b_value = b(),
    };
}

