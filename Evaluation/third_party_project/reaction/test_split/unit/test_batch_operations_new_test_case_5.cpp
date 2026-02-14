

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_batch_operations_function_implementation_5.hpp"

using namespace batch_operations_impl;

/**
 * @brief Test batch reset protection mechanism
 */
TEST(BatchOperationsTest, TestBatchResetProtection) {
    const auto result = runBatchResetProtectionScenario();

    EXPECT_TRUE(result.exceptionThrown);
    EXPECT_EQ(result.var1_value, 5);  // value unchanged by batch constructor
    EXPECT_EQ(result.calc1_value, 10);
}

