

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_batch_operations_function_implementation_6.hpp"

using namespace batch_operations_impl;

/**
 * @brief Test manual batch close functionality
 */
TEST(BatchOperationsTest, TestManualBatchClose) {
    const auto result = runManualBatchCloseScenario();

    // Batch should be active initially
    EXPECT_FALSE(result.batchInitiallyClosed);

    // Batch should now be closed
    EXPECT_TRUE(result.batchAfterClose);

    // After manual close, reset should work
    EXPECT_EQ(result.calc1_value_after_reset, 105); // 5 + 100

    // Calling close multiple times should be safe
    EXPECT_FALSE(result.closeSecondTimeThrows);
    EXPECT_TRUE(result.batchAfterClose);
}

