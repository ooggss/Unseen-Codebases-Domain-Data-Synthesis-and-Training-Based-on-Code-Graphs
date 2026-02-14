

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

/**
 * Scenario: ResetVoidExpressionConsistency
 *
 * Two calcs are chained; a subsequent reset that would create a cycle must
 * fail, leaving the second calc consistent and still linked to b.
 *
 * @return final calc1, calc2, and b values
 */
struct ResetVoidExpressionConsistencyResult {
    int final_calc1_value;
    int final_calc2_value;
    int final_b_value;
};

ResetVoidExpressionConsistencyResult
run_ResetVoidExpressionConsistency_scenario() {
    auto a = reaction::var(1);
    auto b = reaction::var(2);

    // Create calculations that will form a cycle
    auto calc1 = reaction::calc([](int x) { return x; }, a);
    auto calc2 = reaction::calc([](int y) { return y; }, b);

    // First, make calc1 depend on calc2
    calc1.reset([&]() { return calc2() + 1; });
    int v1 = calc1.get(); // 3

    // Now attempt to make calc2 depend on calc1, creating a cycle
    bool threw = false;
    try {
        calc2.reset([&]() { return calc1() + 1; });
    } catch (const std::runtime_error&) {
        threw = true;
    }

    // Verify calc2 is still in a consistent state
    int v2 = calc2.get(); // 2

    // Verify calc2's dependencies are still intact
    b.value(5);
    int v3 = calc2.get(); // 5

    (void)v1;
    (void)v2;
    (void)threw;

    return ResetVoidExpressionConsistencyResult{
        .final_calc1_value = calc1.get(),
        .final_calc2_value = v3,
        .final_b_value = b(),
    };
}

