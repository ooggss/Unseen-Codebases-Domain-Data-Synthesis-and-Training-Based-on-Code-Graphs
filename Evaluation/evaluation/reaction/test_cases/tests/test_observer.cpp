#include <gtest/gtest.h>

#include "test_observer.hpp"

namespace test_reaction {

/**
 * Test Case: Test observer notification functionality
 *
 * Test Scenario:
 * - Create two observer nodes
 * - Set up observer relationship
 * - Notify target and verify observer is called
 */
TEST(reaction, test_observer_notification) {
  // ============ Construct Function Inputs ============

  // Input: Names for observer and target
  const std::string observerName = "Observer1";
  const std::string targetName = "Target1";

  // ============ Call Function to Get Return Value ============
  const auto [wasChanged, callCount] = test_observer_notification(observerName, targetName);

  // ============ Assert to Verify Return Value ============

  EXPECT_TRUE(wasChanged);
  EXPECT_EQ(callCount, 1);
}

}  // namespace test_reaction