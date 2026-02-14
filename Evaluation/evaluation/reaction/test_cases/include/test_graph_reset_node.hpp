#pragma once

#include <reaction/core/observer_node.h>
#include <reaction/graph/observer_graph.h>
#include <memory>
#include <string>

namespace test_reaction {

class ResetAwareNode : public reaction::ObserverNode {
public:
    explicit ResetAwareNode(std::string name) : m_name(std::move(name)) {}

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

struct ResetNodeResult {
    bool notifiedBeforeReset;
    bool notifiedAfterReset;
};

/**
 * Function: Demonstrate ObserverGraph::resetNode removing dependencies.
 *
 * @param sourceName Name for the source node
 * @param targetName Name for the target node
 * @return ResetNodeResult Snapshot describing notification counts around resetNode
 */
inline ResetNodeResult test_graph_reset_node(const std::string &sourceName,
                                             const std::string &targetName) {
    using namespace reaction;

    auto source = std::make_shared<ResetAwareNode>(sourceName);
    auto target = std::make_shared<ResetAwareNode>(targetName);

    auto &graph = ObserverGraph::getInstance();
    graph.addNode(source);
    graph.addNode(target);
    graph.addObserver(target, source);

    source->notify(true);
    const bool before = target->notifications() == 1;

    target->clear();
    graph.resetNode(target);

    source->notify(true);
    const bool after = target->notifications() == 1;

    graph.closeNode(target);
    graph.closeNode(source);

    return ResetNodeResult{
        .notifiedBeforeReset = before,
        .notifiedAfterReset = after,
    };
}

}  // namespace test_reaction

