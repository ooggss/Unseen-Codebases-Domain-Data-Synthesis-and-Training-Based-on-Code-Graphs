

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_batch_operations_function_implementation_8.hpp"

using namespace batch_operations_impl;

/**
 * @brief Test multiple batches with overlapping data sources and complex dependencies
 */
TEST(BatchOperationsTest, TestMultipleBatchesWithSharedDependencies) {
    const auto r = runMultipleBatchesWithSharedDependenciesScenario();

    // Precompute initial values
    EXPECT_EQ(r.X0, 3);     // 1+2
    EXPECT_EQ(r.Y0, 6);     // 2*3
    EXPECT_EQ(r.Z0, 9);     // 3+6
    EXPECT_EQ(r.obs10, 6);  // 3+3
    EXPECT_EQ(r.obs20, 7);  // 6+1
    EXPECT_EQ(r.obs30, 22); // 9+6+7
    EXPECT_EQ(r.obs40, 23); // 1+22
    EXPECT_EQ(r.obs50, 25); // 2+23
    EXPECT_EQ(r.obs60, 50); // 3+25+22

    // Verify state hasn't changed before executing batches
    EXPECT_EQ(r.a_before, 1);
    EXPECT_EQ(r.b_before, 2);
    EXPECT_EQ(r.c_before, 3);
    EXPECT_EQ(r.obs6_before, 50);
    EXPECT_EQ(r.triggerX_before, 0);
    EXPECT_EQ(r.triggerA_before, 0);

    // After batch1
    EXPECT_EQ(r.a1, 10);
    EXPECT_EQ(r.b1, 2);
    EXPECT_EQ(r.c1, 3);
    EXPECT_EQ(r.X1, 12);
    EXPECT_EQ(r.Y1, 6);
    EXPECT_EQ(r.Z1, 18);
    EXPECT_EQ(r.obs11, 15);
    EXPECT_EQ(r.obs21, 16);
    EXPECT_EQ(r.obs31, 49);
    EXPECT_EQ(r.obs41, 59);
    EXPECT_EQ(r.obs51, 61);
    EXPECT_EQ(r.obs61, 113);

    EXPECT_EQ(r.triggerX1, 1);
    EXPECT_EQ(r.triggerY1, 1);
    EXPECT_EQ(r.triggerZ1, 1);
    EXPECT_EQ(r.triggerA1, 1);
    EXPECT_EQ(r.triggerB1, 1);
    EXPECT_EQ(r.triggerC1, 1);

    // After batch2
    EXPECT_EQ(r.a2, 10);
    EXPECT_EQ(r.b2, 20);
    EXPECT_EQ(r.c2, 30);
    EXPECT_EQ(r.X2, 30);
    EXPECT_EQ(r.Y2, 600);
    EXPECT_EQ(r.Z2, 630);
    EXPECT_EQ(r.obs12, 60);
    EXPECT_EQ(r.obs22, 610);
    EXPECT_EQ(r.obs32, 1300);
    EXPECT_EQ(r.obs42, 1310);
    EXPECT_EQ(r.obs52, 1330);
    EXPECT_EQ(r.obs62, 2660);

    EXPECT_EQ(r.triggerX2, 1);
    EXPECT_EQ(r.triggerY2, 1);
    EXPECT_EQ(r.triggerZ2, 1);
    EXPECT_EQ(r.triggerA2, 1);
    EXPECT_EQ(r.triggerB2, 1);
    EXPECT_EQ(r.triggerC2, 1);

    // After batch3
    EXPECT_EQ(r.a3, 100);
    EXPECT_EQ(r.b3, 20);
    EXPECT_EQ(r.c3, 300);
    EXPECT_EQ(r.X3, 120);
    EXPECT_EQ(r.Y3, 6000);
    EXPECT_EQ(r.Z3, 6120);
    EXPECT_EQ(r.obs13, 420);
    EXPECT_EQ(r.obs23, 6100);
    EXPECT_EQ(r.obs33, 12640);
    EXPECT_EQ(r.obs43, 12740);
    EXPECT_EQ(r.obs53, 12760);
    EXPECT_EQ(r.obs63, 25700);

    EXPECT_EQ(r.triggerX3, 1);
    EXPECT_EQ(r.triggerY3, 1);
    EXPECT_EQ(r.triggerZ3, 1);
    EXPECT_EQ(r.triggerA3, 1);
    EXPECT_EQ(r.triggerB3, 1);
    EXPECT_EQ(r.triggerC3, 1);
}

