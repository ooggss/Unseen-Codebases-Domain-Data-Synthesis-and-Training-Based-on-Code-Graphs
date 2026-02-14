#pragma once

#include <reaction/core/observer_node.h>
#include <reaction/graph/observer_graph.h>
#include <memory>

namespace test_reaction {

class CountingObserver : public reaction::ObserverNode {
public:
    void valueChanged(bool changed = true) override {
        if (changed) {
            ++m_notifications;
        }
        ObserverNode::valueChanged(changed);
    }

    int notifications() const { return m_notifications; }

private:
    int m_notifications = 0;
};

struct ObserverNodeLinkSnapshot {
    int firstNotificationsAfterInitial;
    int firstNotificationsAfterUpdate;
    int secondNotificationsAfterUpdate;
    int thirdNotificationsAfterUpdate;
};

/**
 * Function: Demonstrate ObserverNode::addOneObserver and updateObservers.
 *
 * @return ObserverNodeLinkSnapshot Notification counts before/after observer update
 */
inline ObserverNodeLinkSnapshot test_observer_node_links() {
    using namespace reaction;

    auto counting = std::make_shared<CountingObserver>();
    auto sourceA = std::make_shared<ObserverNode>();
    auto sourceB = std::make_shared<ObserverNode>();
    auto sourceC = std::make_shared<ObserverNode>();

    auto &graph = ObserverGraph::getInstance();
    graph.addNode(counting);
    graph.addNode(sourceA);
    graph.addNode(sourceB);
    graph.addNode(sourceC);

    counting->addOneObserver(sourceA);
    sourceA->notify(true);
    const int afterInitial = counting->notifications();

    counting->updateObservers(sourceB, sourceC);
    sourceA->notify(true);
    const int afterOldSource = counting->notifications();

    sourceB->notify(true);
    const int afterSecondSource = counting->notifications();

    sourceC->notify(true);
    const int afterThirdSource = counting->notifications();

    graph.closeNode(counting);
    graph.closeNode(sourceA);
    graph.closeNode(sourceB);
    graph.closeNode(sourceC);

    return ObserverNodeLinkSnapshot{
        .firstNotificationsAfterInitial = afterInitial,
        .firstNotificationsAfterUpdate = afterOldSource,
        .secondNotificationsAfterUpdate = afterSecondSource,
        .thirdNotificationsAfterUpdate = afterThirdSource,
    };
}

}  // namespace test_reaction

