#include <gtest/gtest.h>

#include "test_reactive_calculation.hpp"

namespace test_reaction {

/**
 * Test Case: Test reactive calculation functionality
 *
 * Test Scenario:
 * - Create reactive variables and calculation
 * - Verify the calculation result updates correctly
 */
TEST(reaction, test_reactive_calculation) {
  // ============ Construct Function Inputs ============

  // Input: Two values for calculation
  const int a = 3;
  const int b = 4;

  // ============ Call Function to Get Return Value ============
  const int result = test_reactive_calculation(a, b);

  // ============ Assert to Verify Return Value ============

  EXPECT_EQ(result, 14);  // (3 + 4) * 2 = 14
}

}  // namespace test_reaction