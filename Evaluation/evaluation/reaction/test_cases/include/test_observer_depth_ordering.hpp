#pragma once

#include <reaction/core/observer_node.h>
#include <reaction/graph/batch.h>
#include <reaction/concurrency/thread_manager.h>
#include <memory>

namespace test_reaction {

struct DepthOrderingSnapshot {
    bool initialComparatorResult;
    bool shallowBeforeDeep;
    bool deepBeforeShallow;
    bool nullComesFirst;
};

/**
 * Function: Demonstrate ObserverNode::updateDepth cooperating with BatchCompare ordering.
 *
 * @return DepthOrderingSnapshot Comparator outcomes after adjusting node depths.
 */
inline DepthOrderingSnapshot test_observer_depth_ordering() {
    using namespace reaction;

    class DepthProbeNode : public ObserverNode {
    public:
        void valueChanged(bool changed = true) override {
            ObserverNode::valueChanged(changed);
        }
    };

    auto &tm = ThreadManager::getInstance();
    tm.resetForTesting();
    tm.enableThreadSafety();

    auto shallow = std::make_shared<DepthProbeNode>();
    auto deep = std::make_shared<DepthProbeNode>();

    NodeWeak shallowWeak = shallow;
    NodeWeak deepWeak = deep;
    BatchCompare comparator;

    const bool initialComparatorResult = comparator(shallowWeak, deepWeak);

    shallow->updateDepth(1);
    deep->updateDepth(4);
    const bool shallowBeforeDeep = comparator(shallowWeak, deepWeak);

    shallow->updateDepth(6);
    const bool deepBeforeShallow = comparator(deepWeak, shallowWeak);

    NodeWeak nullWeak;
    const bool nullComesFirst = comparator(nullWeak, shallowWeak);

    return DepthOrderingSnapshot{
        .initialComparatorResult = initialComparatorResult,
        .shallowBeforeDeep = shallowBeforeDeep,
        .deepBeforeShallow = deepBeforeShallow,
        .nullComesFirst = nullComesFirst,
    };
}

}  // namespace test_reaction


