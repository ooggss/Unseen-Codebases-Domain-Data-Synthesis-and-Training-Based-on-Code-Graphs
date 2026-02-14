

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_batch_operations_function_implementation_3.hpp"

using namespace batch_operations_impl;

// Test repeat nodes repeat dependented by others
TEST(BatchOperationsTest, TestRepeatDependency4) {
    const auto result = runRepeatDependencyScenario4();

    EXPECT_EQ(result.triggerCountA, 1);
    EXPECT_EQ(result.ds_a_value, 12);
    EXPECT_EQ(result.triggerCountB, 1);
    EXPECT_EQ(result.ds_b_value, 12);
    EXPECT_EQ(result.triggerCountC, 1);
    EXPECT_EQ(result.ds_c_value, 24);
}

