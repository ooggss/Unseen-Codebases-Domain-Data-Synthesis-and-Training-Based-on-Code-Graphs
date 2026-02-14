#include <gtest/gtest.h>

#include "test_unary_expression_builders.hpp"

namespace test_reaction {

/**
 * Test Case: Validate unary expression builders and operators on reactive variables.
 *
 * Test Scenario:
 * - Build a negated sum using make_binary_op + make_unary_op and wrap it via expr
 * - Flip a reactive boolean and observe logical negation through expr(!flag)
 * - Apply bitwise NOT to a reactive integer and read the result through expr(~bits)
 */
TEST(reaction, test_unary_expression_builders) {
  const int a = 2;
  const int b = 5;

  const auto snapshot = test_unary_expression_builders(a, b);

  EXPECT_EQ(snapshot.initialNegatedSum, -(a + b));
  EXPECT_EQ(snapshot.updatedNegatedSum, -((a + 1) + b));
  EXPECT_TRUE(snapshot.logicalNotAfterFlip);
  EXPECT_EQ(snapshot.bitwiseNotValue, ~0x0F);
}

}  // namespace test_reaction


