

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <gtest/gtest.h>

// In actual projects, this would be included via a header.
#include "test_advanced_features_function_implementation_1.hpp"

// Test field-based reactivity with objects
TEST(AdvancedFeaturesTest, TestField) {
    // ============ Call Function to Get Return Value ============
    auto [before, after] = compute_reactive_person_name_string();

    // ============ Assert to Verify Return Value ============
    EXPECT_EQ(before, "1lummy");
    EXPECT_EQ(after, "1lummy-new");
}

