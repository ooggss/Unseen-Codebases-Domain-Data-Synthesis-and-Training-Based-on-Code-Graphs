#include <gtest/gtest.h>

#include "test_observer_depth_ordering.hpp"

namespace test_reaction {

/**
 * Test Case: Validate depth-based ordering with ObserverNode::updateDepth and BatchCompare.
 *
 * Test Scenario:
 * - Compare two fresh nodes (same depth) to confirm comparator stays false
 * - Raise depths to ensure ordering flips when one becomes deeper
 * - Confirm null weak pointers are ranked before valid nodes
 */
TEST(reaction, test_observer_depth_ordering) {
  const auto snapshot = test_observer_depth_ordering();

  EXPECT_FALSE(snapshot.initialComparatorResult);
  EXPECT_TRUE(snapshot.shallowBeforeDeep);
  EXPECT_TRUE(snapshot.deepBeforeShallow);
  EXPECT_TRUE(snapshot.nullComesFirst);
}

}  // namespace test_reaction


