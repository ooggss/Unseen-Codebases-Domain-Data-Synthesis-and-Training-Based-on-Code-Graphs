#include <gtest/gtest.h>

#include "test_node_metrics_cache.hpp"

namespace test_reaction {

/**
 * Test Case: Inspect NodeMetricsCache hit/miss accounting and invalidation.
 *
 * Test Scenario:
 * - Query metrics for a fresh node (expect a miss and zero entries)
 * - Cache NodeMetrics and query again (expect hit and one entry)
 * - Call invalidateAll and ensure subsequent lookup misses and entries drop to zero
 */
TEST(reaction, test_node_metrics_cache) {
  const auto snapshot = test_node_metrics_cache();

  EXPECT_EQ(snapshot.entriesBefore, 0u);
  EXPECT_EQ(snapshot.entriesAfterCache, 1u);
  EXPECT_EQ(snapshot.entriesAfterInvalidate, 0u);
  EXPECT_TRUE(snapshot.metricsCachedExists);
  EXPECT_TRUE(snapshot.metricsClearedAfterInvalidate);
  EXPECT_GE(snapshot.missCount, 1u);
  EXPECT_GE(snapshot.hitCount, 1u);
  EXPECT_GE(snapshot.hitRatio, 0.0);
  EXPECT_LE(snapshot.hitRatio, 1.0);
}

}  // namespace test_reaction


