#include <gtest/gtest.h>

#include "test_generic_cache_base.hpp"

namespace test_reaction {

/**
 * Test Case: Validate CacheBase-level hit/miss tracking and invalidation.
 *
 * Test Scenario:
 * - Perform an initial lookup on an empty cache and confirm it misses
 * - Insert a value via cacheValue and confirm the next lookup hits
 * - Invalidate all entries and ensure the cache reports zero entries with sane stats
 */
TEST(reaction, test_generic_cache_base) {
  const auto snapshot = test_generic_cache_base();

  EXPECT_EQ(snapshot.entriesBefore, 0u);
  EXPECT_EQ(snapshot.entriesAfterInsert, 1u);
  EXPECT_EQ(snapshot.entriesAfterInvalidate, 0u);

  EXPECT_TRUE(snapshot.firstLookupWasMiss);
  EXPECT_TRUE(snapshot.secondLookupWasHit);

  EXPECT_GE(snapshot.missCount, 1u);
  EXPECT_GE(snapshot.hitCount, 1u);
  EXPECT_GE(snapshot.hitRatio, 0.0);
  EXPECT_LE(snapshot.hitRatio, 1.0);
}

}  // namespace test_reaction


