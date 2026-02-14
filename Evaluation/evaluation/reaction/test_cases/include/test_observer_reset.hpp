#pragma once

#include <reaction/core/observer_node.h>
#include <reaction/graph/observer_graph.h>
#include <memory>
#include <string>

namespace test_reaction {

// ============================================
// Data model definitions
// ============================================

class TestObserverReset : public reaction::ObserverNode {
public:
    TestObserverReset(const std::string& name) : m_name(name), m_changed(false), m_callCount(0) {}

    void valueChanged(bool changed = true) override {
        m_changed = changed;
        m_callCount++;
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
    int m_callCount;
};

// ============================================
// Function implementations
// ============================================

/**
 * Function: Test observer reset functionality
 *
 * @param observerName Name for the observer node
 * @param targetName Name for the target node
 * @return bool Whether observer reset worked correctly (observer no longer notified after reset)
 */
bool test_observer_reset(const std::string& observerName, const std::string& targetName) {
    using namespace reaction;

    // Create observer nodes
    auto observer = std::make_shared<TestObserverReset>(observerName);
    auto target = std::make_shared<TestObserverReset>(targetName);

    // Get observer graph instance
    auto& graph = ObserverGraph::getInstance();

    // Add observer relationship: observer watches target
    graph.addObserver(observer, target);

    // Notify target of change - observer should be called
    target->notify(true);
    bool notifiedBeforeReset = observer->wasChanged() && observer->getCallCount() == 1;

    // Record the call count before reset
    int callCountBeforeReset = observer->getCallCount();

    // Reset the observer node (removes all its dependencies)
    // This should remove the observer relationship, so observer won't be notified anymore
    graph.resetNode(observer);

    // Notify target again - observer should NOT be called since dependency was removed
    target->notify(true);
    
    // Check that call count did not increase (observer was not notified)
    bool notNotifiedAfterReset = observer->getCallCount() == callCountBeforeReset;

    // Return true if reset worked correctly
    return notifiedBeforeReset && notNotifiedAfterReset;
}

}  // namespace test_reaction