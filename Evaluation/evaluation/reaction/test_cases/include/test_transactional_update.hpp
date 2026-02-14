#pragma once

#include <reaction/core/observer_node.h>
#include <reaction/graph/observer_graph.h>
#include <reaction/core/exception.h>
#include <memory>
#include <string>

namespace test_reaction {

// ============================================
// Data model definitions
// ============================================

class TestTransactionalObserver : public reaction::ObserverNode {
public:
    TestTransactionalObserver(const std::string& name) : m_name(name), m_changed(false) {}

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
 * Function: Test transactional observer updates
 *
 * @param nodeName Name for the node to update
 * @return bool Whether transactional update succeeded (no cycle created)
 */
bool test_transactional_update(const std::string& nodeName) {
    using namespace reaction;

    // Create observer nodes
    auto nodeA = std::make_shared<TestTransactionalObserver>(nodeName);
    auto nodeB = std::make_shared<TestTransactionalObserver>("NodeB");

    // Get observer graph instance
    auto& graph = ObserverGraph::getInstance();

    // Set up initial relationship: A observes B
    graph.addObserver(nodeA, nodeB);

    // Test initial relationship: notify B, A should be called
    nodeB->notify(true);
    bool initialRelationshipWorks = nodeA->wasChanged() && nodeA->getCallCount() == 1;

    // Reset A for next test
    nodeA->reset();

    // Attempt transactional update that would create a cycle: make B observe A
    // This should fail due to cycle detection and rollback
    bool cycleDetected = false;
    try {
        graph.updateObserversTransactional(nodeB, nodeA);
    } catch (const DependencyCycleException&) {
        cycleDetected = true;
    }

    // Test that original relationship still works after failed transaction
    nodeB->notify(true);
    bool originalRelationshipPreserved = nodeA->wasChanged() && nodeA->getCallCount() == 1;

    // Return true if initial relationship worked, cycle was detected, and original preserved
    return initialRelationshipWorks && cycleDetected && originalRelationshipPreserved;
}

}  // namespace test_reaction