#pragma once

#include <reaction/core/observer_node.h>
#include <reaction/graph/observer_graph.h>
#include <memory>
#include <string>

namespace test_reaction {

// ============================================
// Data model definitions
// ============================================

class TestChainedObserver : public reaction::ObserverNode {
public:
    TestChainedObserver(const std::string& name) : m_name(name), m_changed(false) {}

    void valueChanged(bool changed = true) override {
        m_changed = changed;
        m_callCount++;
        // Call base class to propagate notification to observers
        ObserverNode::valueChanged(changed);
    }

    bool wasChanged() const { return m_changed; }
    int getCallCount() const { return m_callCount; }
    const std::string& getName() const { return m_name; }

    void reset() {
        m_changed = false;
        m_callCount = 0;
    }

private:
    std::string m_name;
    bool m_changed;
    int m_callCount = 0;
};

// ============================================
// Function implementations
// ============================================

/**
 * Function: Test chained observer relationships
 *
 * @param targetName Name for the target node
 * @param observer1Name Name for the first observer node
 * @param observer2Name Name for the second observer node (observes observer1)
 * @return std::pair<int, bool> Pair of total call count and whether chain notification worked correctly
 */
std::pair<int, bool> test_chained_observers(const std::string& targetName, 
                                            const std::string& observer1Name, 
                                            const std::string& observer2Name) {
    using namespace reaction;

    // Create nodes: target, observer1 (observes target), observer2 (observes observer1)
    auto target = std::make_shared<TestChainedObserver>(targetName);
    auto observer1 = std::make_shared<TestChainedObserver>(observer1Name);
    auto observer2 = std::make_shared<TestChainedObserver>(observer2Name);

    // Get observer graph instance
    auto& graph = ObserverGraph::getInstance();

    // Set up chain: observer1 watches target, observer2 watches observer1
    graph.addObserver(observer1, target);
    graph.addObserver(observer2, observer1);

    // Notify target of change
    target->notify(true);

    // Verify chain notification:
    // - observer1 should be notified (callCount = 1)
    // - observer2 should be notified because observer1 was notified (callCount = 1)
    bool observer1Notified = observer1->wasChanged() && observer1->getCallCount() == 1;
    bool observer2Notified = observer2->wasChanged() && observer2->getCallCount() == 1;
    int totalCallCount = observer1->getCallCount() + observer2->getCallCount();

    // Return total call count and whether chain notification worked
    return {totalCallCount, observer1Notified && observer2Notified};
}

}  // namespace test_reaction

