

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
#include "test_invalidation_function_implementation_0.hpp"

using namespace invalidation_test_impl;

// Test close handle for reactive graph cleanup
TEST(InvalidationTest, TestCloseHandle) {
    // Execute the encapsulated logic and obtain the result
    auto result = runCloseHandleScenario();

    // Assertions corresponding to the original EXPECTs
    EXPECT_FALSE(result.dsB_valid);
    EXPECT_FALSE(result.dsC_valid);
    EXPECT_FALSE(result.dsD_valid);
    EXPECT_FALSE(result.dsE_valid);
    EXPECT_TRUE(result.dsF_valid);
    EXPECT_FALSE(result.dsG_valid);
}

