#include <gtest/gtest.h>

#include "test_reactive_expression.hpp"

namespace test_reaction {

/**
 * Test Case: Test reactive expression functionality
 *
 * Test Scenario:
 * - Create reactive variables
 * - Create a reactive expression using expr API with operator syntax
 * - Verify the expression result updates correctly
 */
TEST(reaction, test_reactive_expression) {
  // ============ Construct Function Inputs ============

  // Input: Two values for expression
  const int a = 5;
  const int b = 3;

  // ============ Call Function to Get Return Value ============
  const int result = test_reactive_expression(a, b);

  // ============ Assert to Verify Return Value ============

  EXPECT_EQ(result, 16);  // (5 + 3) * 2 = 16
}

}  // namespace test_reaction

