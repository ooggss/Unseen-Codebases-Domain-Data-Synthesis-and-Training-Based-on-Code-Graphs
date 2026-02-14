#include <gtest/gtest.h>

#include "test_const_var_propagation.hpp"

namespace test_reaction {

/**
 * Test Case: Verify constVar participates in calculations without needing updates
 *
 * Test Scenario:
 * - Create a mutable var and a constVar
 * - Build a calc that sums both
 * - Update only the mutable var and ensure the total reflects the change
 */
TEST(reaction, test_const_var_propagation) {
  const int baseValue = 5;
  const int constValue = 10;
  const int delta = 4;

  const auto result = test_const_var_propagation(baseValue, constValue, delta);

  EXPECT_EQ(result.initialSum, baseValue + constValue);
  EXPECT_EQ(result.updatedSum, baseValue + delta + constValue);
}

}  // namespace test_reaction


