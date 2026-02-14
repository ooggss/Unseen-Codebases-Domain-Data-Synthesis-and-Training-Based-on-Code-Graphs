#include <gtest/gtest.h>

#include "test_observer_naming.hpp"

namespace test_reaction {

/**
 * Test Case: Test observer naming functionality
 *
 * Test Scenario:
 * - Create an observer node
 * - Set a name for the node
 * - Verify the name can be retrieved
 */
TEST(reaction, test_observer_naming) {
  // ============ Construct Function Inputs ============

  // Input: Name for the observer node
  const std::string nodeName = "TestObserver";

  // ============ Call Function to Get Return Value ============
  const std::string retrievedName = test_observer_naming(nodeName);

  // ============ Assert to Verify Return Value ============

  EXPECT_EQ(retrievedName, nodeName);
}

}  // namespace test_reaction