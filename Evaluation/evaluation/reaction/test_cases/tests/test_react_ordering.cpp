#include <gtest/gtest.h>

#include "test_react_ordering.hpp"

namespace test_reaction {

/**
 * Test Case: Verify React::operator< sorts reactive handles by name.
 *
 * Test Scenario:
 * - Create three reactive vars with distinct names
 * - Insert them into std::set (which relies on operator<)
 * - Ensure iteration order matches lexicographical ordering of names
 */
TEST(reaction, test_react_ordering) {
  const auto snapshot = test_react_ordering("beta", "alpha", "gamma");

  ASSERT_EQ(snapshot.orderedNames.size(), 3u);
  EXPECT_EQ(snapshot.orderedNames[0], "alpha");
  EXPECT_EQ(snapshot.orderedNames[1], "beta");
  EXPECT_EQ(snapshot.orderedNames[2], "gamma");
  EXPECT_TRUE(snapshot.allUnique);
}

}  // namespace test_reaction

