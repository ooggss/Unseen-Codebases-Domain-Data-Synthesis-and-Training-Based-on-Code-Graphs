#include <gtest/gtest.h>

#include "test_batch_execution.hpp"

namespace test_reaction {

/**
 * Test Case: Test batch execution functionality
 *
 * Test Scenario:
 * - Create reactive variables and a calculation
 * - Perform non-batch updates and record recompute count
 * - Perform batched updates and verify recompute count increased by only 1
 */
TEST(reaction, test_batch_execution) {
  // ============ Construct Function Inputs ============
  const int initialA = 1;
  const int initialB = 2;
  const int nonBatchA = 5;
  const int nonBatchB = 6;
  const int batchA = 10;
  const int batchB = 20;

  // ============ Call Function ============
  const auto [finalSum, countAfterNonBatch, countAfterBatch] =
      test_batch_execution(initialA, initialB, nonBatchA, nonBatchB, batchA,
                           batchB);

  // Initial calc + two non-batch updates -> 3 recomputes
  EXPECT_EQ(countAfterNonBatch, 3);

  // Batch updates should only add one recompute
  EXPECT_EQ(countAfterBatch, countAfterNonBatch + 1);

  // Final sum reflects batched updates
  EXPECT_EQ(finalSum, batchA + batchB);
}

}  // namespace test_reaction

