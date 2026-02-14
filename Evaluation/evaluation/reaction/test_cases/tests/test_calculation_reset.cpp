#include <gtest/gtest.h>

#include "test_calculation_reset.hpp"

namespace test_reaction {

/**
 * Test Case: Test calculation reset functionality
 *
 * Test Scenario:
 * - Create reactive variables and a calculation
 * - Reset the calculation to use different dependencies
 * - Verify the calculation result updates correctly
 */
TEST(reaction, test_calculation_reset) {
  // ============ Construct Function Inputs ============

  // Input: Three values for testing
  const int a = 5;
  const int b = 3;
  const int c = 7;

  // ============ Call Function to Get Return Value ============
  const int result = test_calculation_reset(a, b, c);

  // ============ Assert to Verify Return Value ============

  EXPECT_EQ(result, 10);  // After reset: b + c = 3 + 7 = 10
}

}  // namespace test_reaction

