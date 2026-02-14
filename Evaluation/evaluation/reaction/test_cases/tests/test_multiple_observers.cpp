#include <gtest/gtest.h>

#include "test_multiple_observers.hpp"

namespace test_reaction {

/**
 * Test Case: Test multiple observers watching a single target
 *
 * Test Scenario:
 * - Create a target node and multiple observer nodes
 * - Set up observer relationships (all observers watch the target)
 * - Notify target and verify all observers are called
 */
TEST(reaction, test_multiple_observers) {
  // ============ Construct Function Inputs ============

  // Input: Name for the target node
  const std::string targetName = "TargetNode";
  
  // Input: Names for observer nodes
  const std::vector<std::string> observerNames = {"Observer1", "Observer2", "Observer3"};

  // ============ Call Function to Get Return Value ============
  const auto [totalCallCount, allNotified] = test_multiple_observers(targetName, observerNames);

  // ============ Assert to Verify Return Value ============

  EXPECT_EQ(totalCallCount, 3);  // All three observers should be called once
  EXPECT_TRUE(allNotified);      // All observers should be notified
}

}  // namespace test_reaction

