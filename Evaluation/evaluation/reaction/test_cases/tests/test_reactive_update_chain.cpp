#include <gtest/gtest.h>

#include "test_reactive_update_chain.hpp"

namespace test_reaction {

/**
 * Test Case: Test reactive update chain functionality
 *
 * Test Scenario:
 * - Create reactive variables and dependent calculations
 * - Create a calculation chain: sum depends on vars, product depends on sum
 * - Update a variable and verify the entire chain updates correctly
 */
TEST(reaction, test_reactive_update_chain) {
  // ============ Construct Function Inputs ============

  // Input: Initial values and new value
  const int a = 5;
  const int b = 3;
  const int newA = 10;

  // ============ Call Function to Get Return Value ============
  const int result = test_reactive_update_chain(a, b, newA);

  // ============ Assert to Verify Return Value ============

  EXPECT_EQ(result, 26);  // (10 + 3) * 2 = 26
}

}  // namespace test_reaction

