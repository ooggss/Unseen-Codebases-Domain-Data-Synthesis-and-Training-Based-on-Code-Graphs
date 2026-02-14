#include <gtest/gtest.h>

#include "test_raw_expression_builders.hpp"

namespace test_reaction {

/**
 * Test Case: Test raw expression builders (make_binary_expr / make_unary_expr).
 *
 * Test Scenario:
 * - Create three reactive integers A, B, C.
 * - Build expressions using low-level helpers:
 *     sum      = A + B
 *     negated  = -(A + B)
 *     chained  = -(A + B) * C
 * - Update A and C and verify all expression values update as expected.
 */
TEST(reaction, test_raw_expression_builders) {
  const int a = 2;
  const int b = 5;
  const int c = 3;

  const auto snapshot = test_raw_expression_builders(a, b, c);

  // Initial expectations:
  // sum      = a + b
  // negated  = -(a + b)
  // chained  = -(a + b) * c
  EXPECT_EQ(snapshot.initialSum, a + b);
  EXPECT_EQ(snapshot.initialNegatedSum, -(a + b));
  EXPECT_EQ(snapshot.initialChainedValue, -(a + b) * c);

  // After update:
  // A'       = a + 1
  // C'       = c + 1
  // sum'     = (a + 1) + b
  // negated' = -((a + 1) + b)
  // chained' = -((a + 1) + b) * (c + 1)
  EXPECT_EQ(snapshot.updatedSum, (a + 1) + b);
  EXPECT_EQ(snapshot.updatedNegatedSum, -((a + 1) + b));
  EXPECT_EQ(snapshot.updatedChainedValue,
            -((a + 1) + b) * (c + 1));
}

}  // namespace test_reaction


