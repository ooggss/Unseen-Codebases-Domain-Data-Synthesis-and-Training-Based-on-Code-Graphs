#include <gtest/gtest.h>

#include "test_observer_collection.hpp"

namespace test_reaction {

/**
 * Test Case: Collect direct and transitive observers for a source node
 *
 * Test Scenario:
 * - Build a two-level observer chain
 * - Invoke ObserverGraph::collectObservers
 * - Ensure both direct and transitive observers are returned
 */
TEST(reaction, test_observer_collection) {
  const auto summary = test_observer_collection();

  EXPECT_EQ(summary.totalObservers, 2);
  EXPECT_TRUE(summary.containsDirectObserver);
  EXPECT_TRUE(summary.containsTransitiveObserver);
}

}  // namespace test_reaction


