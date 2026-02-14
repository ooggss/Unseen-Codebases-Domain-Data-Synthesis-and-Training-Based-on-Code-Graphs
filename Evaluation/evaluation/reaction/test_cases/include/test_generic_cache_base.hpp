#pragma once

#include <reaction/cache/cache_base.h>
#include <memory>
#include <chrono>

namespace test_reaction {

struct GenericCacheStatsSnapshot {
    std::size_t entriesBefore;
    std::size_t entriesAfterInsert;
    std::size_t entriesAfterInvalidate;
    std::size_t hitCount;
    std::size_t missCount;
    double hitRatio;
    bool firstLookupWasMiss;
    bool secondLookupWasHit;
};

/**
 * Function: Demonstrate CacheBase hit/miss accounting and invalidation.
 *
 * This function wraps the low-level CacheBase APIs in a small concrete cache and then:
 * - Performs an initial lookup for a missing key (recording a miss and zero entries)
 * - Inserts a value via cacheValue and looks it up again (recording a hit and one entry)
 * - Calls invalidateAllEntries and verifies that subsequent lookups miss and entries drop to zero
 *
 * @return GenericCacheStatsSnapshot Snapshot of cache statistics and lookup outcomes.
 */
inline GenericCacheStatsSnapshot test_generic_cache_base() {
    using namespace reaction;

    class IntCache : public CacheBase<int, int> {
    public:
        IntCache(std::size_t maxSize, std::chrono::minutes ttl)
            : CacheBase(maxSize, ttl) {}

        using CacheBase::getCachedValue;
        using CacheBase::cacheValue;
        using CacheBase::invalidateAllEntries;
        using CacheBase::getStatsInternal;
        using CacheBase::triggerCleanupInternal;
    };

    IntCache cache(/*maxSize=*/8, std::chrono::minutes(5));

    const auto statsBefore = cache.getStatsInternal();
    const bool firstMiss = (cache.getCachedValue(1) == nullptr);

    cache.cacheValue(1, 42);
    const bool secondHit = (cache.getCachedValue(1) != nullptr);
    const auto statsAfterInsert = cache.getStatsInternal();

    cache.invalidateAllEntries();
    cache.triggerCleanupInternal();
    const auto statsAfterInvalidate = cache.getStatsInternal();

    return GenericCacheStatsSnapshot{
        .entriesBefore = statsBefore.totalEntries,
        .entriesAfterInsert = statsAfterInsert.totalEntries,
        .entriesAfterInvalidate = statsAfterInvalidate.totalEntries,
        .hitCount = statsAfterInvalidate.hitCount,
        .missCount = statsAfterInvalidate.missCount,
        .hitRatio = statsAfterInvalidate.hitRatio,
        .firstLookupWasMiss = firstMiss,
        .secondLookupWasHit = secondHit,
    };
}

}  // namespace test_reaction


