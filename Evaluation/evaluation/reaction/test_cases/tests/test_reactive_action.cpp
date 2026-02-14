#include <gtest/gtest.h>

#include "test_reactive_action.hpp"

namespace test_reaction {

/**
 * Test Case: Test reactive action functionality
 *
 * Test Scenario:
 * - Create a reactive variable
 * - Create an action that captures side effects when variable changes
 * - Update the variable and verify action is triggered
 */
TEST(reaction, test_reactive_action) {
  // ============ Construct Function Inputs ============

  // Input: Initial value and new value
  const int initialValue = 10;
  const int newValue = 25;

  // ============ Call Function to Get Return Value ============
  const int capturedValue = test_reactive_action(initialValue, newValue);

  // ============ Assert to Verify Return Value ============

  EXPECT_EQ(capturedValue, newValue);  // Action should capture the new value
}

}  // namespace test_reaction

