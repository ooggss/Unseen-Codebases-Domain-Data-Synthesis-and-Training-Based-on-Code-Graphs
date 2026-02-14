

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Include function implementation (normally via header)
#include "test_trigger_function_implementation_0.hpp"

TEST(TriggerTest, TestChangeTrig) {
    using trigger_test_change_trig::run_change_trigger_scenario;

    // ============ Call Function to Get Return Value ============
    auto [triggerCountA, triggerCountB] = run_change_trigger_scenario();

    // ============ Assert to Verify Return Value ============

    // Final expectations from the original test:
    EXPECT_EQ(triggerCountA, 3);
    EXPECT_EQ(triggerCountB, 2);
}

