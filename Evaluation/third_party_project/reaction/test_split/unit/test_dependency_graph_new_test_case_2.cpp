

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
#include "test_dependency_graph_function_implementation_2.hpp"

namespace dependency_graph_test_cycle_dependency {

// Test detection of circular dependencies
TEST(DependencyGraphTest, TestCycleDependency) {
    // ============ Call Function to Get Return Value ============
    const auto threw_expected = test_cycle_dependency_throws();

    // ============ Assert to Verify Return Value ============
    EXPECT_TRUE(threw_expected);
}

}  // namespace dependency_graph_test_cycle_dependency

