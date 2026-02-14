#include <gtest/gtest.h>

#include "test_always_trigger.hpp"

namespace test_reaction {

/**
 * Test Case: Verify calc<AlwaysTrig> recomputes on duplicate assignments
 *
 * Test Scenario:
 * - Create a reactive variable and an AlwaysTrig calculation
 * - Write the same value again
 * - Ensure recompute count increments despite no value change
 */
TEST(reaction, test_always_trigger) {
  const int initialValue = 7;

  const auto result = test_always_trigger(initialValue);

  EXPECT_EQ(result.recomputeCountAfterInit, 1);
  EXPECT_EQ(result.recomputeCountAfterDuplicateWrite, 2);
}

}  // namespace test_reaction


