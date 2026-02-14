#include <gtest/gtest.h>

#include "test_unique_id_sequence.hpp"

namespace test_reaction {

/**
 * Test Case: Validate UniqueID generates distinct, strictly increasing values.
 */
TEST(reaction, test_unique_id_sequence) {
  const auto sequence = test_unique_id_sequence();

  EXPECT_TRUE(sequence.strictlyIncreasing);
  EXPECT_LT(sequence.firstValue, sequence.secondValue);
  EXPECT_LT(sequence.secondValue, sequence.thirdValue);
}

}  // namespace test_reaction


