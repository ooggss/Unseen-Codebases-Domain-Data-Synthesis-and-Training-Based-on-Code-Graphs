

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

/**
 * Scenario: SuccessfulResetAfterFailedReset
 *
 * A reset that introduces an invalid dependency fails and is rolled back,
 * and a subsequent valid reset succeeds and remains consistent.
 *
 * @return final calc value and final a/b values
 */
struct SuccessfulResetAfterFailedResetResult {
    int final_calc_value;
    int final_a_value;
    int final_b_value;
};

SuccessfulResetAfterFailedResetResult
run_SuccessfulResetAfterFailedReset_scenario() {
    auto a = reaction::var(1);
    auto b = reaction::var(2);

    // Create a valid calculation
    auto calc = reaction::calc([](int x, int y) { return x + y; }, a, b);
    int v1 = calc.get(); // 3

    // Attempt a failed reset
    bool threw = false;
    try {
        calc.reset([&]() { return calc() + a(); });
    } catch (const std::runtime_error&) {
        threw = true;
    }

    // Verify still consistent
    int v2 = calc.get(); // 3

    // Now do a successful reset
    calc.reset([&]() { return a() * b(); });
    int v3 = calc.get(); // 2

    // Verify new calculation works
    a.value(3);
    int v4 = calc.get(); // 6
    b.value(4);
    int v5 = calc.get(); // 12

    (void)v1;
    (void)v2;
    (void)v3;
    (void)v4;
    (void)threw;

    return SuccessfulResetAfterFailedResetResult{
        .final_calc_value = v5,
        .final_a_value = a(),
        .final_b_value = b(),
    };
}

