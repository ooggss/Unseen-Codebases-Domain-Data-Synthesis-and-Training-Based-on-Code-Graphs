

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
#include "test_invalidation_function_implementation_2.hpp"

using namespace invalidation_test_impl;

// Test last handle for maintaining only the last value
TEST(InvalidationTest, TestLastHandle) {
    // Run the scenario and retrieve results
    auto result = runLastHandleScenario();

    // Original expectations mapped to struct fields
    EXPECT_EQ(result.dsB_initial, 2);
    EXPECT_EQ(result.dsC_initial, 4);

    EXPECT_EQ(result.dsB_after_a_change, 11);
    EXPECT_EQ(result.dsC_after_a_change, 22);
}

