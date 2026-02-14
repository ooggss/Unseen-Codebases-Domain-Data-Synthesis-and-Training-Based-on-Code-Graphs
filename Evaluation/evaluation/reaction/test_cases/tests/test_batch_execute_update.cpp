#include <gtest/gtest.h>

#include "test_batch_execute_update.hpp"

namespace test_reaction {

/**
 * Test Case: Confirm batchExecute batches multiple value updates
 *
 * Test Scenario:
 * - Create a reactive value and dependent calculation
 * - Run two sequential updates inside batchExecute
 * - Ensure recompute count only increments once and final value matches last update
 */
TEST(reaction, test_batch_execute_update) {
  const int baseValue = 10;
  const int deltaA = 3;
  const int deltaB = 7;

  const auto result = test_batch_execute_update(baseValue, deltaA, deltaB);

  EXPECT_EQ(result.recomputeCountBeforeBatch, 1);
  EXPECT_EQ(result.recomputeCountAfterBatch, 2);
  EXPECT_EQ(result.finalValue, (baseValue + deltaA + deltaB) * 2);
}

}  // namespace test_reaction


