#include <gtest/gtest.h>

#include "test_thread_manager.hpp"

namespace test_reaction {

/**
 * Test Case: Test thread manager registration functionality
 *
 * Test Scenario:
 * - Register thread and check thread safety status
 * - Enable thread safety if requested
 * - Verify thread safety state
 */
TEST(reaction, test_thread_manager_registration) {
  // ============ Construct Function Inputs ============

  // Input: Whether to enable thread safety
  const bool enableSafety = true;

  // ============ Call Function to Get Return Value ============
  const bool isSafetyEnabled = test_thread_manager_registration(enableSafety);

  // ============ Assert to Verify Return Value ============

  EXPECT_TRUE(isSafetyEnabled);
}

}  // namespace test_reaction