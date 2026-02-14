#include <gtest/gtest.h>

#include "test_filter_trigger.hpp"

namespace test_reaction {

/**
 * Test Case: Test filter trigger functionality
 *
 * Test Scenario:
 * - Create a reactive variable and filter-triggered calculation
 * - First update stays within threshold and should not trigger recompute
 * - Second update exceeds threshold and should trigger recompute once
 */
TEST(reaction, test_filter_trigger) {
  // ============ Construct Function Inputs ============

  const double initialValue = 25.0;
  const double firstUpdate = 27.0;   // delta 2 -> no trigger
  const double secondUpdate = 40.0;  // delta 13 -> trigger
  const double diffThreshold = 5.0;
  const double levelThreshold = 30.0;

  // ============ Call Function to Get Return Value ============
  const auto [finalStatus, countAfterFirst, countAfterSecond] =
      test_filter_trigger(initialValue, firstUpdate, secondUpdate,
                          diffThreshold, levelThreshold);

  // ============ Assert to Verify Return Value ============

  EXPECT_EQ(countAfterFirst, 1);       // initial computation only
  EXPECT_EQ(countAfterSecond, 2);      // triggered once more
  EXPECT_EQ(finalStatus, "HIGH");      // second update >= levelThreshold
}

}  // namespace test_reaction

