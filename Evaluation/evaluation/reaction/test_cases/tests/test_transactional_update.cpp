#include <gtest/gtest.h>

#include "test_transactional_update.hpp"

namespace test_reaction {

/**
 * Test Case: Test transactional observer update functionality
 *
 * Test Scenario:
 * - Create observer nodes
 * - Set up initial relationships
 * - Attempt transactional update that would create a cycle (should fail and rollback)
 * - Verify original relationships are preserved
 */
TEST(reaction, test_transactional_update) {
  // ============ Construct Function Inputs ============

  // Input: Name for the node to update
  const std::string nodeName = "TestNode";

  // ============ Call Function to Get Return Value ============
  const bool updateSuccessful = test_transactional_update(nodeName);

  // ============ Assert to Verify Return Value ============

  EXPECT_TRUE(updateSuccessful);
}

}  // namespace test_reaction