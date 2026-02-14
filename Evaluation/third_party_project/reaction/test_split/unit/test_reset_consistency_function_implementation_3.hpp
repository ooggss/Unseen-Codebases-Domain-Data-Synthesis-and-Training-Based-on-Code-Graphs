

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

/**
 * Scenario: ResetWithExceptionInEvaluationRollback
 *
 * A calc is reset with a function that may throw during evaluation. The
 * reset must roll back and the calc must remain consistent afterward.
 *
 * @return final calc value and final a value
 */
struct ResetWithExceptionInEvaluationRollbackResult {
    int final_calc_value;
    int final_a_value;
};

ResetWithExceptionInEvaluationRollbackResult
run_ResetWithExceptionInEvaluationRollback_scenario() {
    auto a = reaction::var(1);

    // Create a valid calculation
    auto calc = reaction::calc([](int x) { return x * 2; }, a);
    int v1 = calc.get(); // 2

    // Attempt to reset with a function that throws during evaluation
    bool threw = false;
    try {
        calc.reset([&]() {
            if (a() == 1) {
                throw std::runtime_error("Test exception during evaluation");
            }
            return a() * 3;
        });
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

    return ResetWithExceptionInEvaluationRollbackResult{
        .final_calc_value = v3,
        .final_a_value = a(),
    };
}

