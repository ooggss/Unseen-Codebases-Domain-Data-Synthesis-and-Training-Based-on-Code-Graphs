#include <gtest/gtest.h>

#include "test_batch_manual_lifecycle.hpp"

namespace test_reaction {

/**
 * Test Case: Validate manual Batch lifecycle management
 *
 * Test Scenario:
 * - Create a Batch via reaction::batch
 * - Ensure object starts active, execute it, then close it
 * - Verify recompute count reflects constructor + execute runs
 */
TEST(reaction, test_batch_manual_lifecycle) {
  const int initialValue = 2;
  const int updatedValue = 11;

  const auto result = test_batch_manual_lifecycle(initialValue, updatedValue);

  EXPECT_FALSE(result.closedInitially);
  EXPECT_TRUE(result.closedAfterClose);
  EXPECT_EQ(result.recomputeCountAfterExecute, 2);
}

}  // namespace test_reaction


