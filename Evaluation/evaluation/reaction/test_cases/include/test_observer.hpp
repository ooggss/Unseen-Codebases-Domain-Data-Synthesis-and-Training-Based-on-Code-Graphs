#pragma once

#include <reaction/core/observer_node.h>
#include <reaction/graph/observer_graph.h>
#include <reaction/concurrency/thread_manager.h>
#include <memory>
#include <string>

namespace test_reaction {

// ============================================
// Data model definitions
// ============================================

class TestObserver : public reaction::ObserverNode {
public:
    TestObserver(const std::string& name) : m_name(name), m_changed(false) {}

    void valueChanged(bool changed = true) override {
        m_changed = changed;
        m_callCount++;
    }

    bool wasChanged() const { return m_changed; }
    int getCallCount() const { return m_callCount; }
    const std::string& getName() const { return m_name; }

private:
    std::string m_name;
    bool m_changed;
    int m_callCount = 0;
};

// ============================================
// Function implementations
// ============================================

/**
 * Function: Create observer relationship and test notification
 *
 * @param observerName Name for the observer node
 * @param targetName Name for the target node
 * @return std::pair<bool, int> Pair of whether observer was notified and call count
 */
std::pair<bool, int> test_observer_notification(const std::string& observerName, const std::string& targetName) {
    using namespace reaction;

    // Create observer nodes
    auto observer = std::make_shared<TestObserver>(observerName);
    auto target = std::make_shared<TestObserver>(targetName);

    // Get observer graph instance
    auto& graph = ObserverGraph::getInstance();

    // Add observer relationship: observer watches target
    graph.addObserver(observer, target);

    // Notify target of change
    target->notify(true);

    // Return notification status
    return {observer->wasChanged(), observer->getCallCount()};
}

}  // namespace test_reaction