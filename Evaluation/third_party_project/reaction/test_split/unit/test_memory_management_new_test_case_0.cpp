

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <gtest/gtest.h>

// In practice, declare this in a header and include that header here.
#include "test_memory_management_function_implementation_0.hpp"

// Test copy semantics of reactive variables
TEST(MemoryManagementTest, TestCopy) {
    // ============ Call function to get results ============
    const auto [initial_copy, initial_dds, updated_copy, updated_dds] =
        simulate_copy_memory_management();

    // ============ Assertions (original expectations) ============

    EXPECT_EQ(initial_copy, "113.140000");
    EXPECT_EQ(initial_dds,  "113.140000");

    EXPECT_EQ(updated_copy, "223.140000");
    EXPECT_EQ(updated_dds,  "223.140000");
}

