

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_batch_operations_function_implementation_1.hpp"

using namespace batch_operations_impl;

// Test more complex repeated dependency scenarios
TEST(BatchOperationsTest, TestRepeatDependency2) {
    const auto result = runRepeatDependencyScenario2();

    EXPECT_EQ(result.triggerCount_after_a3, 2);
    EXPECT_EQ(result.ds_after_a3, 14);

    EXPECT_EQ(result.triggerCount_after_batch, 1);
    EXPECT_EQ(result.ds_after_batch, 12);

    EXPECT_EQ(result.triggerCount_after_a1, 2);
    EXPECT_EQ(result.ds_after_a1, 10);
}

