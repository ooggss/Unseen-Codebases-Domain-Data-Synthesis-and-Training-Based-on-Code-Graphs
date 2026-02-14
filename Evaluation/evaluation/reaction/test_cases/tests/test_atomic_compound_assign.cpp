#include <gtest/gtest.h>

#include "test_atomic_compound_assign.hpp"

namespace test_reaction {

/**
 * Test Case: Validate atomic compound assignment helpers on React variables.
 *
 * Test Scenario:
 * - Start from base value 2
 * - Apply +=, *=, &=, <<= and post-increment operations
 * - Ensure each operation yields expected intermediate values and triggers calc evaluations
 */
TEST(reaction, test_atomic_compound_assign) {
  const auto snapshot = test_atomic_compound_assign();

  EXPECT_EQ(snapshot.afterAddition, 5);
  EXPECT_EQ(snapshot.afterMultiplication, 20);
  EXPECT_EQ(snapshot.afterBitwiseAnd, 4);
  EXPECT_EQ(snapshot.afterShift, 16);
  EXPECT_EQ(snapshot.postIncrementReturn, 16);
  EXPECT_EQ(snapshot.finalValue, 17);
  EXPECT_EQ(snapshot.calcEvaluations, 6);
}

}  // namespace test_reaction


