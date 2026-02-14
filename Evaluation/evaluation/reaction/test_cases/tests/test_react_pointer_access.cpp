#include <gtest/gtest.h>

#include "test_react_pointer_access.hpp"

namespace test_reaction {

/**
 * Test Case: Ensure React::operator-> provides stable pointer access to the stored object.
 *
 * Test Scenario:
 * - Initialize a reactive Counter
 * - Invoke pointer-like access twice to mutate the stored value
 * - Verify pointer identity stability and accumulated value
 */
TEST(reaction, test_react_pointer_access) {
  const int initialValue = 4;
  const int delta = 3;

  const auto snapshot = test_react_pointer_access(initialValue, delta);

  EXPECT_EQ(snapshot.valueAfterFirstAdd, initialValue + delta);
  EXPECT_EQ(snapshot.valueAfterSecondAdd, initialValue + delta * 2);
  EXPECT_TRUE(snapshot.pointerStable);
}

}  // namespace test_reaction

