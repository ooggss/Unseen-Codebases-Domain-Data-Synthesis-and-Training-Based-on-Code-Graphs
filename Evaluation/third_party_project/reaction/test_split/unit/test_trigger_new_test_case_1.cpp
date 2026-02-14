

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Include function implementation (normally via header)
#include "test_trigger_function_implementation_1.hpp"

TEST(TriggerTest, TestFilterTrig) {
    using trigger_test_filter_trig::run_filter_trigger_scenario;

    // ============ Call Function to Get Return Value ============
    auto [ds_val, dds_val] = run_filter_trigger_scenario();

    // ============ Assert to Verify Return Value ============

    // Final expectations after all operations:
    // From original sequence:
    // - After a=2: ds=4, dds=7
    // - After filter and a=3: dds=8 (ds=5)
    // - After a=5 with filter blocking: dds remains 8, ds=7
    EXPECT_EQ(ds_val, 7);
    EXPECT_EQ(dds_val, 8);
}

