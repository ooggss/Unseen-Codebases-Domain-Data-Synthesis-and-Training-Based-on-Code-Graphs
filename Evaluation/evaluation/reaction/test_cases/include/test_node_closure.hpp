#pragma once

#include <reaction/core/observer_node.h>
#include <reaction/graph/observer_graph.h>
#include <memory>
#include <string>

namespace test_reaction {

// ============================================
// Data model definitions
// ============================================

class TestObserverClosure : public reaction::ObserverNode {
public:
    TestObserverClosure(const std::string& name) : m_name(name), m_changed(false) {}

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
    int m_callCount = 0;
};

// ============================================
// Function implementations
// ============================================

/**
 * Function: Test node closure functionality
 *
 * @param nodeName Name for the observer node
 * @return bool Whether node closure worked correctly (relationships cleaned up)
 */
bool test_node_closure(const std::string& nodeName) {
    using namespace reaction;

    // Create observer nodes
    auto observer = std::make_shared<TestObserverClosure>(nodeName);
    auto target = std::make_shared<TestObserverClosure>("Target");

    // Get observer graph instance
    auto& graph = ObserverGraph::getInstance();

    // Add observer relationship: observer watches target
    graph.addObserver(observer, target);

    // Notify target - observer should be called
    target->notify(true);
    bool notifiedBeforeClosure = observer->wasChanged() && observer->getCallCount() == 1;

    // Reset observer state
    observer->reset();

    // Close the observer node
    graph.closeNode(observer);

    // Notify target again - observer should NOT be called since relationship was cleaned up
    target->notify(true);
    bool notNotifiedAfterClosure = !observer->wasChanged() && observer->getCallCount() == 0;

    // Return true if notification worked before closure and stopped after closure
    return notifiedBeforeClosure && notNotifiedAfterClosure;
}

}  // namespace test_reaction