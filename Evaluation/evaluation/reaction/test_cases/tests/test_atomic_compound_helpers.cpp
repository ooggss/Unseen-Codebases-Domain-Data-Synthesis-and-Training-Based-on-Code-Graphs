#include <gtest/gtest.h>

#include "test_atomic_compound_helpers.hpp"

namespace test_reaction {

/**
 * Test Case: Test low-level atomic compound helper functions.
 *
 * Test Scenario:
 * - Start from an initial integer value.
 * - Apply atomicCompoundAssign<AddAssignOp>, atomicMultiplyAssign,
 *   atomicBitwiseAndAssign, atomicLeftShiftAssign, and atomicIncrement
 *   on a simple IntAtomicImpl object.
 * - Verify the final value and that each helper reported a change.
 */
TEST(reaction, test_atomic_compound_helpers) {
  const int32_t initial = 5;

  const auto snapshot = test_atomic_compound_helpers(initial);

  // Step-by-step expectation:
  // after add:       5 + 3   = 8
  // after multiply:  8 * 2   = 16
  // after AND 0xFF:  16 & FF = 16
  // after shift:     16 << 1 = 32
  // after increment: 33
  EXPECT_EQ(snapshot.finalValue, 33);

  EXPECT_TRUE(snapshot.addReportedChange);
  EXPECT_TRUE(snapshot.multiplyReportedChange);
  EXPECT_FALSE(snapshot.andReportedChange);
  EXPECT_TRUE(snapshot.leftShiftReportedChange);
  EXPECT_TRUE(snapshot.incrementReportedChange);
}

}  // namespace test_reaction


