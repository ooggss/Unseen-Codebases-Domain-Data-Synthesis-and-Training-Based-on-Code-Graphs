#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

// ============================================
// Helper types
// ============================================

/**
 * @brief Observer node that records how many times it was notified.
 */
class FieldOwnerNode : public reaction::ObserverNode {
public:
    void valueChanged(bool changed = true) override {
        if (changed) {
            ++m_notificationCount;
        }
        ObserverNode::valueChanged(changed);
    }

    int getNotificationCount() const { return m_notificationCount; }

private:
    int m_notificationCount = 0;
};

/**
 * @brief Sample domain model that exposes two reactive fields.
 */
class ProfileFields : public reaction::FieldBase {
public:
    ProfileFields(int initialScore, bool initialStatus)
        : m_score(field(initialScore)), m_active(field(initialStatus)) {}

    reaction::Var<int> &score() { return m_score; }
    reaction::Var<bool> &active() { return m_active; }

private:
    reaction::Var<int> m_score;
    reaction::Var<bool> m_active;
};

/**
 * @brief Aggregated metrics after binding fields to an owner node.
 */
struct FieldBindingResult {
    int notificationsAfterScoreUpdate;
    int notificationsAfterStatusUpdate;
};

// ============================================
// Function implementation
// ============================================

/**
 * Function: Bind reactive fields to an owner node and record notifications
 *
 * @param initialScore Initial numeric score
 * @param scoreDelta Value added to the score field
 * @return FieldBindingResult Notification counts after each update
 */
FieldBindingResult test_field_binding(int initialScore, int scoreDelta) {
    using namespace reaction;

    ProfileFields fields(initialScore, true);
    auto owner = std::make_shared<FieldOwnerNode>();

    auto &graph = ObserverGraph::getInstance();
    graph.addNode(owner);

    FieldGraph::getInstance().bindField(fields.getId(), owner);

    fields.score().value(initialScore + scoreDelta);
    const int afterScoreUpdate = owner->getNotificationCount();

    fields.active().value(false);
    const int afterStatusUpdate = owner->getNotificationCount();

    return FieldBindingResult{afterScoreUpdate, afterStatusUpdate};
}

}  // namespace test_reaction


