#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

// ============================================
// Helper types
// ============================================

/**
 * @brief Observer node that tracks how many times valueChanged is invoked.
 */
class RecordingNode : public reaction::ObserverNode {
public:
    void valueChanged(bool changed = true) override {
        if (changed) {
            ++m_notifications;
        }
        ObserverNode::valueChanged(changed);
    }

    int notificationCount() const { return m_notifications; }

private:
    int m_notifications = 0;
};

/**
 * @brief Result object describing notification counts before/after rollback.
 */
struct RollbackObservation {
    int notificationsAfterSecondBinding;
    int notificationsAfterRollback;
};

// ============================================
// Function implementation
// ============================================

/**
 * Function: Demonstrate transactional dependency updates with rollback support
 *
 * @return RollbackObservation Notification metrics for the observing node
 */
RollbackObservation test_observer_state_rollback() {
    using namespace reaction;

    auto sensorA = std::make_shared<RecordingNode>();
    auto sensorB = std::make_shared<RecordingNode>();
    auto aggregator = std::make_shared<RecordingNode>();

    auto &graph = ObserverGraph::getInstance();
    graph.addNode(sensorA);
    graph.addNode(sensorB);
    graph.addNode(aggregator);

    graph.addObserver(aggregator, sensorA);

    auto rollback = graph.saveNodeStateForRollback(aggregator);

    graph.updateObserversTransactional(aggregator, sensorB);

    sensorB->valueChanged();
    const int afterSecondBinding = aggregator->notificationCount();

    rollback();

    sensorA->valueChanged();
    const int afterRollback = aggregator->notificationCount();

    return RollbackObservation{
        afterSecondBinding,
        afterRollback,
    };
}

}  // namespace test_reaction


