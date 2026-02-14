#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

class CacheProbeNode : public reaction::ObserverNode {
public:
    void valueChanged(bool changed = true) override {
        reaction::ObserverNode::valueChanged(changed);
    }
};

struct CacheStatsSnapshot {
    size_t graphEntriesBeforeCleanup;
    size_t graphEntriesAfterCleanup;
    double graphHitRatioAfterCleanup;
};

/**
 * Function: Inspect ObserverGraph cache stats before/after cleanup
 *
 * @return CacheStatsSnapshot Cache entry counts and hit ratio
 */
CacheStatsSnapshot test_observer_cache_stats() {
    using namespace reaction;

    auto source = std::make_shared<CacheProbeNode>();
    auto direct = std::make_shared<CacheProbeNode>();
    auto transitive = std::make_shared<CacheProbeNode>();

    auto &graph = ObserverGraph::getInstance();
    graph.addNode(source);
    graph.addNode(direct);
    graph.addNode(transitive);

    graph.addObserver(direct, source);
    graph.addObserver(transitive, direct);

    NodeSet collected;
    graph.collectObservers(source, collected, 1);

    const auto statsBefore = graph.getCacheStats();

    graph.triggerCacheCleanup();
    const auto statsAfter = graph.getCacheStats();

    graph.closeNode(transitive);
    graph.closeNode(direct);
    graph.closeNode(source);

    return CacheStatsSnapshot{
        .graphEntriesBeforeCleanup = statsBefore.graphStats.totalEntries,
        .graphEntriesAfterCleanup = statsAfter.graphStats.totalEntries,
        .graphHitRatioAfterCleanup = statsAfter.graphStats.hitRatio,
    };
}

}  // namespace test_reaction


