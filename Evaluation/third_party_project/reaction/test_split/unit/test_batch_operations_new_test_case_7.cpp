

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_batch_operations_function_implementation_7.hpp"

using namespace batch_operations_impl;

/**
 * @brief Test complex dependency scenario with batch reset protection
 */
TEST(BatchOperationsTest, TestComplexDependencyBatchResetProtection) {
    const auto r = runComplexDependencyBatchResetProtectionScenario();

    // Initial values check
    EXPECT_EQ(r.calc1_initial, 3);
    EXPECT_EQ(r.calc2_initial, 6);
    EXPECT_EQ(r.calc3_initial, 7);
    EXPECT_EQ(r.calc4_initial, 5);
    EXPECT_EQ(r.calc5_initial, 15);
    EXPECT_EQ(r.calc6_initial, 7);
    EXPECT_EQ(r.calc7_initial, 28);
    EXPECT_EQ(r.calc8_initial, 8);
    EXPECT_EQ(r.calc9_initial, 13);
    EXPECT_EQ(r.calc10_initial, 26);

    // Resets must throw during active batch
    EXPECT_TRUE(r.resetsThrowWhileActive);

    // Values unchanged before execute
    EXPECT_EQ(r.calc1_before_execute, 3);
    EXPECT_EQ(r.calc2_before_execute, 6);
    EXPECT_EQ(r.calc3_before_execute, 7);

    // After batch execute, values updated
    EXPECT_EQ(r.var1_after, 10);
    EXPECT_EQ(r.var2_after, 20);
    EXPECT_EQ(r.var3_after, 30);
    EXPECT_EQ(r.var4_after, 40);

    EXPECT_EQ(r.calc1_after, 30);
    EXPECT_EQ(r.calc2_after, 60);
    EXPECT_EQ(r.calc3_after, 61);
    EXPECT_EQ(r.calc4_after, 50);
    EXPECT_EQ(r.calc5_after, 150);
    EXPECT_EQ(r.calc6_after, 70);
    EXPECT_EQ(r.calc7_after, 280);
    EXPECT_EQ(r.calc8_after, 80);
    EXPECT_EQ(r.calc9_after, 85);
    EXPECT_EQ(r.calc10_after, 170);

    // Still protected after execute, before close
    EXPECT_TRUE(r.resetStillThrowsAfterExecute);

    // After manual batch close, resets work and propagate
    EXPECT_EQ(r.calc1_after_reset, 20); // 10 * 2
    EXPECT_EQ(r.calc2_after_reset, 40); // 20 * 2
    EXPECT_EQ(r.calc3_after_reset, 41); // 40 + 1

    EXPECT_EQ(r.calc5_after_reset, 1050); // 50 + 1000
    EXPECT_TRUE(r.batch_is_closed);
}

