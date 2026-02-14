#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

class TrackingFieldNode : public reaction::ObserverNode {
public:
    explicit TrackingFieldNode(std::string name) : m_name(std::move(name)) {}

    void valueChanged(bool changed = true) override {
        if (changed) {
            ++m_notifications;
        }
        reaction::ObserverNode::valueChanged(changed);
    }

    int notifications() const { return m_notifications; }

    void clear() { m_notifications = 0; }

private:
    std::string m_name;
    int m_notifications = 0;
};

struct FieldGraphCleanupResult {
    bool notifiedBeforeDelete;
    bool notifiedAfterDelete;
};

/**
 * Function: Demonstrate FieldGraph::deleteObj preventing future bindings.
 *
 * @param objectId Identifier whose field nodes will be deleted
 * @return FieldGraphCleanupResult Snapshot before/after deleteObj
 */
inline FieldGraphCleanupResult test_field_graph_cleanup(uint64_t objectId) {
    using namespace reaction;

    auto owner = std::make_shared<TrackingFieldNode>("owner");
    auto field = std::make_shared<TrackingFieldNode>("field");

    auto &graph = ObserverGraph::getInstance();
    graph.addNode(owner);
    graph.addNode(field);

    auto &fieldGraph = FieldGraph::getInstance();
    fieldGraph.addObj(objectId, field);
    fieldGraph.bindField(objectId, owner);

    field->notify(true);
    const bool beforeDelete = owner->notifications() == 1;

    owner->clear();
    graph.resetNode(owner);

    fieldGraph.deleteObj(objectId);
    fieldGraph.bindField(objectId, owner);

    field->notify(true);
    const bool afterDelete = owner->notifications() == 1;

    graph.closeNode(owner);
    graph.closeNode(field);

    return FieldGraphCleanupResult{
        .notifiedBeforeDelete = beforeDelete,
        .notifiedAfterDelete = afterDelete,
    };
}

}  // namespace test_reaction

