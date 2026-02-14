#include <gtest/gtest.h>

#include "test_atomic_operations.hpp"

namespace test_reaction {

/**
 * Test Case: Test atomic operations on reactive variables
 *
 * Test Scenario:
 * - Create a reactive variable
 * - Perform atomic addition
 * - Verify the final value
 */
TEST(reaction, test_atomic_operations) {
  // ============ Construct Function Inputs ============

  // Input: Initial value and value to add
  const int initialValue = 10;
  const int addValue = 5;

  // ============ Call Function to Get Return Value ============
  const int finalValue = test_atomic_operations(initialValue, addValue);

  // ============ Assert to Verify Return Value ============

  EXPECT_EQ(finalValue, 15);
}

}  // namespace test_reaction