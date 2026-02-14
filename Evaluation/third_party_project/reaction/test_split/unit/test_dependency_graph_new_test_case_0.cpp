

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// In real projects, include via a header; here we include the implementation directly.
#include "test_dependency_graph_function_implementation_0.hpp"

namespace dependency_graph_test_reset {

// Test reset functionality of reactive calculations
TEST(DependencyGraphTest, TestReset) {
    // ============ Call Function to Get Return Value ============
    const auto result = test_reset_behavior();

    // ============ Assert to Verify Return Value ============
    EXPECT_EQ(result, 6);
}

}  // namespace dependency_graph_test_reset

