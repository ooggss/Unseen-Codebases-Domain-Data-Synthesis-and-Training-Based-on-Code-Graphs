#include <gtest/gtest.h>

#include "test_react_validity.hpp"

namespace test_reaction {

/**
 * Test Case: Validate React::operator bool and operator==.
 *
 * Test Scenario:
 * - Create a reactive variable and copy it
 * - Verify validity/equality before closing
 * - Close the source and ensure operator bool reflects invalid state while equality remains true
 */
TEST(reaction, test_react_validity) {
  const int initialValue = 12;

  const auto snapshot = test_react_validity(initialValue);

  EXPECT_TRUE(snapshot.firstValidBeforeClose);
  EXPECT_FALSE(snapshot.firstValidAfterClose);
  EXPECT_TRUE(snapshot.copiesEqualBeforeClose);
  EXPECT_FALSE(snapshot.copiesEqualAfterClose);
  EXPECT_TRUE(snapshot.equalityCheckFailedAfterClose);
}

}  // namespace test_reaction

