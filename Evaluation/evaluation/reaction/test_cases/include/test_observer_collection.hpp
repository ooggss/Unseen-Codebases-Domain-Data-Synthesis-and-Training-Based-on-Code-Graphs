#pragma once

#include <reaction/reaction.h>
#include <string>

namespace test_reaction {

class NamedObserverNode : public reaction::ObserverNode {
public:
    explicit NamedObserverNode(std::string name) : m_name(std::move(name)) {}

    const std::string &name() const { return m_name; }

private:
    std::string m_name;
};

struct ObserverCollectionSummary {
    std::size_t totalObservers;
    bool containsDirectObserver;
    bool containsTransitiveObserver;
};

/**
 * Function: Collect observer graph metrics for a given source node
 *
 * @return ObserverCollectionSummary Counts and membership flags
 */
ObserverCollectionSummary test_observer_collection() {
    using namespace reaction;

    auto source = std::make_shared<NamedObserverNode>("source");
    auto directObserver = std::make_shared<NamedObserverNode>("direct");
    auto transitiveObserver = std::make_shared<NamedObserverNode>("transitive");

    auto &graph = ObserverGraph::getInstance();
    graph.addNode(source);
    graph.addNode(directObserver);
    graph.addNode(transitiveObserver);

    graph.addObserver(directObserver, source);
    graph.addObserver(transitiveObserver, directObserver);

    NodeSet collected;
    graph.collectObservers(source, collected, 1);

    auto contains = [&](const std::shared_ptr<NamedObserverNode> &candidate) {
        for (const auto &weakNode : collected) {
            if (auto locked = weakNode.lock()) {
                if (locked.get() == candidate.get()) {
                    return true;
                }
            }
        }
        return false;
    };

    return ObserverCollectionSummary{
        .totalObservers = collected.size(),
        .containsDirectObserver = contains(directObserver),
        .containsTransitiveObserver = contains(transitiveObserver),
    };
}

}  // namespace test_reaction


