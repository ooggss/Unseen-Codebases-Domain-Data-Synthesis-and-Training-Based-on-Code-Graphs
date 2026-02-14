#include <gtest/gtest.h>

#include "test_observer_reset.hpp"

namespace test_reaction {

/**
 * Test Case: Test observer reset functionality
 *
 * Test Scenario:
 * - Create observer relationship
 * - Verify observer is notified when target changes
 * - Reset observer node (removes dependencies)
 * - Verify observer is no longer notified
 */
TEST(reaction, test_observer_reset) {
  // ============ Construct Function Inputs ============

  // Input: Names for observer and target
  const std::string observerName = "ObserverToReset";
  const std::string targetName = "TargetNode";

  // ============ Call Function to Get Return Value ============
  const bool resetSuccessful = test_observer_reset(observerName, targetName);

  // ============ Assert to Verify Return Value ============

  EXPECT_TRUE(resetSuccessful);
}

}  // namespace test_reaction