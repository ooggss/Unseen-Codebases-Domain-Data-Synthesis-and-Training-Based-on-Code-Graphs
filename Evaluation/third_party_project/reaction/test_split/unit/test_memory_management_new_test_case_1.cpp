

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <gtest/gtest.h>

// In practice, declare these in a header and include that header here.
#include "test_memory_management_function_implementation_1.hpp"

// Test move semantics of reactive variables
TEST(MemoryManagementTest, TestMove) {
    // ============ Call function to get results ============
    const auto result = simulate_move_memory_management();

    // ============ Assertions (original expectations) ============

    EXPECT_EQ(result.initial_value_after_move, "113.140000");
    EXPECT_FALSE(result.dds_bool_after_move);
    EXPECT_TRUE(result.throws_after_move);

    EXPECT_EQ(result.value_after_update, "223.140000");
    EXPECT_FALSE(result.dds_bool_after_update);
}

