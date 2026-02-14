

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace trigger_test_change_trig {

/**
 * Function: run_change_trigger_scenario
 *
 * Scenario extracted from TriggerTest.TestChangeTrig:
 * - Create three reactive variables a, b, c
 * - Create two calculations:
 *   * ds uses AlwaysTrig and increments triggerCountA on each evaluation
 *   * dds uses default trigger and increments triggerCountB on each evaluation
 * - Apply a sequence of updates to a and observe trigger counts.
 *
 * @return std::pair<int,int> Final values of (triggerCountA, triggerCountB)
 */
std::pair<int, int> run_change_trigger_scenario() {
    auto a = reaction::var(1);
    auto b = reaction::var(2);
    auto c = reaction::var(3);
    int triggerCountA = 0;
    int triggerCountB = 0;

    auto ds = reaction::calc<reaction::AlwaysTrig>(
        [&triggerCountA](int aa, double bb) {
            ++triggerCountA;
            return aa + bb;
        },
        a, b
    );

    auto dds = reaction::calc(
        [&triggerCountB](auto aa, auto cc) {
            ++triggerCountB;
            return aa + cc;
        },
        a, c
    );

    // Initial state assertions in the original test:
    // EXPECT_EQ(triggerCountA, 1);
    // EXPECT_EQ(triggerCountB, 1);

    a.value(1);
    // EXPECT_EQ(triggerCountA, 2);
    // EXPECT_EQ(triggerCountB, 1);

    a.value(2);
    // EXPECT_EQ(triggerCountA, 3);
    // EXPECT_EQ(triggerCountB, 2);

    return {triggerCountA, triggerCountB};
}

}  // namespace trigger_test_change_trig

