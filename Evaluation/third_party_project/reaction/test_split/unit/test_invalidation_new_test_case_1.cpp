

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// In real projects, the function declaration would be in a header file.
// Here we include the implementation directly for demonstration.
#include "test_invalidation_function_implementation_1.hpp"

using namespace invalidation_test_impl;

// Test keep handle for maintaining dependencies
TEST(InvalidationTest, TestKeepHandle) {
    // Run the scenario and retrieve results
    auto result = runKeepHandleScenario();

    // Original expectations mapped to struct fields
    EXPECT_EQ(result.dsB_initial, 2);
    EXPECT_EQ(result.dsC_initial, 4);

    EXPECT_EQ(result.dsB_after_a_change, 20);
    EXPECT_EQ(result.dsC_after_a_change, 40);
}

