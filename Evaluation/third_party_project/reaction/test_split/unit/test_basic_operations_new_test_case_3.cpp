

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Include function implementation (in practice, via header)
#include "test_basic_operations_function_implementation_3.hpp"

namespace basic_operations_test {

// Test constant reactive variables
TEST(BasicOperationsTest, TestConst) {
    auto [initial_ds, updated_ds] = run_const_flow();

    ASSERT_FLOAT_EQ(initial_ds, 4.14);
    ASSERT_FLOAT_EQ(updated_ds, 5.14);
    // b.value(4.14); // compile error; constVar cannot be modified
}

}  // namespace basic_operations_test

