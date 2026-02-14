

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_batch_operations_function_implementation_4.hpp"

using namespace batch_operations_impl;

// Test complex dependency scenarios with multiple assignments in a single batch
TEST(BatchOperationsTest, TestComplexDependenciesWithMultipleAssignments) {
    const auto result = runComplexDependenciesWithMultipleAssignments();

    // After first batch: verify trigger counts (each once)
    EXPECT_EQ(result.triggerCountA1, 1);
    EXPECT_EQ(result.triggerCountB1, 1);
    EXPECT_EQ(result.triggerCountC1, 1);
    EXPECT_EQ(result.triggerCountSum1, 1);
    EXPECT_EQ(result.triggerCountProduct1, 1);
    EXPECT_EQ(result.triggerCountCombined1, 1);
    EXPECT_EQ(result.triggerCountFinal1, 1);

    // Verify final values after first batch
    EXPECT_EQ(result.A1, 30);            // 10+20
    EXPECT_EQ(result.B1, 600);           // 20*30
    EXPECT_EQ(result.C1, 70);            // 30+40
    EXPECT_EQ(result.Sum1, 700);         // 30+600+70
    EXPECT_EQ(result.Product1, 18000);   // 30*600
    EXPECT_EQ(result.Combined1, -17300); // 700-18000
    EXPECT_EQ(result.Final1, -17300 * 70);

    // After second batch: only d changes
    EXPECT_EQ(result.triggerCountA2, 0);
    EXPECT_EQ(result.triggerCountB2, 0);
    EXPECT_EQ(result.triggerCountC2, 1);
    EXPECT_EQ(result.triggerCountSum2, 1);
    EXPECT_EQ(result.triggerCountProduct2, 0);
    EXPECT_EQ(result.triggerCountCombined2, 1);
    EXPECT_EQ(result.triggerCountFinal2, 1);

    EXPECT_EQ(result.C2, 80);    // 30+50
    EXPECT_EQ(result.Sum2, 710); // 30+600+80
    EXPECT_EQ(result.Combined2, 710 - 18000);
    EXPECT_EQ(result.Final2, (710 - 18000) * 80);
}

