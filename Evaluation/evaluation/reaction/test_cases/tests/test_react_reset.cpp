#include <gtest/gtest.h>

#include "test_react_reset.hpp"

namespace test_reaction {

/**
 * Test Case: Ensure React::reset replaces the calculation logic under thread safety.
 *
 * Test Scenario:
 * - Create a calc that adds 10 to the source value
 * - Enable thread safety and call reset with a multiplier lambda
 * - Update the source variable and confirm the new logic applies
 */
TEST(reaction, test_react_reset_behavior) {
  const int initialValue = 5;
  const int multiplier = 3;

  const auto snapshot = test_react_reset_behavior(initialValue, multiplier);

  EXPECT_EQ(snapshot.beforeResetValue, initialValue + 10);
  EXPECT_TRUE(snapshot.safetyEnabledDuringReset);
  EXPECT_EQ(snapshot.afterResetValue, (initialValue + multiplier) * multiplier);
}

}  // namespace test_reaction

