#include <gtest/gtest.h>

#include "test_reactive_create_factory.hpp"

namespace test_reaction {

/**
 * Test Case: Verify create() factory overload behavior
 *
 * Test Scenario:
 * - Instantiate a reactive variable via create(value)
 * - Build an expression via create(expression template)
 * - Build a calculation via create(lambda, react)
 * - Update the variable and ensure dependent nodes recompute
 */
TEST(reaction, test_reactive_create_factory) {
  const int baseValue = 4;
  const int increment = 5;

  const auto result = test_reactive_create_factory(baseValue, increment);

  EXPECT_EQ(result.initialExpressionValue, 18);   // (4 + 2) * 3
  EXPECT_EQ(result.updatedExpressionValue, 33);   // (9 + 2) * 3
  EXPECT_EQ(result.squaredValueAfterUpdate, 81);  // 9 * 9
}

}  // namespace test_reaction


