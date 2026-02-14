

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Include function implementation (in practice, via header)
#include "test_basic_operations_function_implementation_1.hpp"

namespace basic_operations_test {

// Test reactive value updates and triggering
TEST(BasicOperationsTest, TestTrigger) {
    auto [initial_a,
          initial_b,
          initial_ds,
          initial_dds,
          updated_ds,
          updated_dds] = run_trigger_flow();

    EXPECT_EQ(initial_a, 1);
    EXPECT_EQ(initial_b, 3.14);
    ASSERT_FLOAT_EQ(initial_ds, 4.14);
    EXPECT_EQ(initial_dds, "14.140000");

    ASSERT_FLOAT_EQ(updated_ds, 5.14);
    EXPECT_EQ(updated_dds, "25.140000");
}

}  // namespace basic_operations_test

