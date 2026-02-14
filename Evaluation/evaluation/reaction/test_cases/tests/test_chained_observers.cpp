#include <gtest/gtest.h>

#include "test_chained_observers.hpp"

namespace test_reaction {

/**
 * Test Case: Test chained observer relationships
 *
 * Test Scenario:
 * - Create a target node and two observer nodes
 * - Set up chain: observer1 watches target, observer2 watches observer1
 * - Notify target and verify both observers are called in chain
 */
TEST(reaction, test_chained_observers) {
  // ============ Construct Function Inputs ============

  // Input: Names for nodes
  const std::string targetName = "TargetNode";
  const std::string observer1Name = "Observer1";
  const std::string observer2Name = "Observer2";

  // ============ Call Function to Get Return Value ============
  const auto [totalCallCount, chainWorked] = test_chained_observers(targetName, observer1Name, observer2Name);

  // ============ Assert to Verify Return Value ============

  EXPECT_EQ(totalCallCount, 2);  // Both observers should be called once
  EXPECT_TRUE(chainWorked);      // Chain notification should work correctly
}

}  // namespace test_reaction

