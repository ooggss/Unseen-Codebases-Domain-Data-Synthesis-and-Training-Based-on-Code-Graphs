#include <gtest/gtest.h>

#include "test_observer_cache_stats.hpp"

namespace test_reaction {

/**
 * Test Case: Trigger cache stats reporting and cleanup in ObserverGraph
 *
 * Test Scenario:
 * - Build a two-level observer chain
 * - Collect observers to populate caches
 * - Trigger cache cleanup and inspect resulting statistics
 */
TEST(reaction, test_observer_cache_stats) {
  const auto snapshot = test_observer_cache_stats();

  EXPECT_GE(snapshot.graphEntriesBeforeCleanup, 1u);
  EXPECT_GE(snapshot.graphEntriesAfterCleanup, 0u);
  EXPECT_GE(snapshot.graphHitRatioAfterCleanup, 0.0);
  EXPECT_LE(snapshot.graphHitRatioAfterCleanup, 1.0);
}

}  // namespace test_reaction


