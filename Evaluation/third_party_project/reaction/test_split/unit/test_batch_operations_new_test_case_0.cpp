

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_batch_operations_function_implementation_0.hpp"

using namespace batch_operations_impl;

// Test handling of repeated dependencies in the graph
TEST(BatchOperationsTest, TestRepeatDependency) {
    const auto result = runRepeatDependencyScenario();

    EXPECT_EQ(result.triggerCount, 1);
    EXPECT_EQ(result.dsB_value, 6);
}

