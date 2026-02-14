#pragma once

#include <reaction/cache/graph_cache.h>
#include <reaction/core/observer_node.h>
#include <memory>

namespace test_reaction {

struct NodeMetricsCacheSnapshot {
    std::size_t entriesBefore;
    std::size_t entriesAfterCache;
    std::size_t entriesAfterInvalidate;
    std::size_t hitCount;
    std::size_t missCount;
    double hitRatio;
    bool metricsCachedExists;
    bool metricsClearedAfterInvalidate;
};

/**
 * Function: Demonstrate NodeMetricsCache behavior on cache hits, misses, and invalidation.
 *
 * This function exercises the low-level cache subsystem used by ObserverGraph by:
 * - Querying metrics for a node before anything is cached (miss)
 * - Caching a NodeMetrics entry and querying again (hit)
 * - Invalidating all entries and confirming subsequent lookups miss
 *
 * @return NodeMetricsCacheSnapshot Snapshot of cache stats and lookup results.
 */
inline NodeMetricsCacheSnapshot test_node_metrics_cache() {
    using namespace reaction;

    NodeMetricsCache cache;

    auto node = std::make_shared<ObserverNode>();

    const auto statsBefore = cache.getStats();
    const auto *metricsBefore = cache.getCachedNodeMetrics(node);

    cache.cacheNodeMetrics(node, /*exists=*/true, /*observerCount=*/2, /*dependentCount=*/1, /*maxDepth=*/3);
    const auto *metricsAfterCache = cache.getCachedNodeMetrics(node);
    const auto statsAfterCache = cache.getStats();

    cache.invalidateAll();
    const auto *metricsAfterInvalidate = cache.getCachedNodeMetrics(node);
    const auto statsAfterInvalidate = cache.getStats();

    return NodeMetricsCacheSnapshot{
        .entriesBefore = statsBefore.totalEntries,
        .entriesAfterCache = statsAfterCache.totalEntries,
        .entriesAfterInvalidate = statsAfterInvalidate.totalEntries,
        .hitCount = statsAfterInvalidate.hitCount,
        .missCount = statsAfterInvalidate.missCount,
        .hitRatio = statsAfterInvalidate.hitRatio,
        .metricsCachedExists = metricsAfterCache && metricsAfterCache->exists,
        .metricsClearedAfterInvalidate = metricsAfterInvalidate == nullptr && metricsBefore == nullptr,
    };
}

}  // namespace test_reaction


