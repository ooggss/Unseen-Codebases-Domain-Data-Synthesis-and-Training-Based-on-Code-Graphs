#include <gtest/gtest.h>

#include "test_observer_node_links.hpp"

namespace test_reaction {

/**
 * Test Case: Validate ObserverNode::addOneObserver and updateObservers.
 *
 * Test Scenario:
 * - Attach a first observer via addOneObserver and trigger a notification
 * - Replace observers using updateObservers and trigger again
 * - Ensure only new observers receive notifications after update
 */
TEST(reaction, test_observer_node_links) {
  const auto snapshot = test_observer_node_links();

  EXPECT_EQ(snapshot.firstNotificationsAfterInitial, 1);
  EXPECT_EQ(snapshot.firstNotificationsAfterUpdate, 1);
  EXPECT_EQ(snapshot.secondNotificationsAfterUpdate, 2);
  EXPECT_EQ(snapshot.thirdNotificationsAfterUpdate, 3);
}

}  // namespace test_reaction

