

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Include function implementation (in practice, via header)
#include "test_basic_operations_function_implementation_0.hpp"

namespace basic_operations_test {

// Test basic calculation functionality with different types
TEST(BasicOperationsTest, TestCalc) {
    auto [a_val, b_val, ds_val, dds_val, ddds_val] = run_basic_calc();

    EXPECT_EQ(a_val, 1);
    EXPECT_EQ(b_val, 3.14);
    ASSERT_FLOAT_EQ(ds_val, 4.14);
    EXPECT_EQ(dds_val, "14.140000");
    EXPECT_EQ(ddds_val, 1);
}

}  // namespace basic_operations_test

