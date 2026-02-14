#pragma once

#include <reaction/core/observer_node.h>
#include <reaction/graph/observer_graph.h>
#include <memory>
#include <string>
#include <vector>

namespace test_reaction {

// ============================================
// Data model definitions
// ============================================

class TestMultipleObserver : public reaction::ObserverNode {
public:
    TestMultipleObserver(const std::string& name) : m_name(name), m_changed(false) {}

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
 * Function: Test multiple observers watching a single target
 *
 * @param targetName Name for the target node
 * @param observerNames Vector of names for observer nodes
 * @return std::pair<int, bool> Pair of total call count and whether all observers were notified
 */
std::pair<int, bool> test_multiple_observers(const std::string& targetName, const std::vector<std::string>& observerNames) {
    using namespace reaction;

    // Create target node
    auto target = std::make_shared<TestMultipleObserver>(targetName);

    // Create observer nodes
    std::vector<std::shared_ptr<TestMultipleObserver>> observers;
    for (const auto& name : observerNames) {
        observers.push_back(std::make_shared<TestMultipleObserver>(name));
    }

    // Get observer graph instance
    auto& graph = ObserverGraph::getInstance();

    // Add all observers to watch the target
    for (const auto& observer : observers) {
        graph.addObserver(observer, target);
    }

    // Notify target of change
    target->notify(true);

    // Count total notifications and check if all observers were notified
    int totalCallCount = 0;
    bool allNotified = true;
    for (const auto& observer : observers) {
        totalCallCount += observer->getCallCount();
        if (!observer->wasChanged() || observer->getCallCount() != 1) {
            allNotified = false;
        }
    }

    // Return total call count and whether all observers were notified
    return {totalCallCount, allNotified};
}

}  // namespace test_reaction

