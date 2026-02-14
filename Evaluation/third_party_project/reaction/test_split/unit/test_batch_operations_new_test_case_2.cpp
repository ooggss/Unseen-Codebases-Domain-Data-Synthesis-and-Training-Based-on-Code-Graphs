

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_batch_operations_function_implementation_2.hpp"

using namespace batch_operations_impl;

// Test deep nested dependency scenarios
TEST(BatchOperationsTest, TestRepeatDependency3) {
    const auto result = runRepeatDependencyScenario3();

    EXPECT_EQ(result.triggerCount_after_batch, 1);
    EXPECT_EQ(result.ds_after_batch, 6);
    EXPECT_EQ(result.ds_after_resetA1, 2);
}

