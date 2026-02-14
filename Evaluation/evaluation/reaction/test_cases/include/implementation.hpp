#pragma once

#include <reaction/core/observer_node.h>
#include <reaction/graph/observer_graph.h>
#include <reaction/concurrency/thread_manager.h>
#include <memory>
#include <string>

namespace test_reaction {

// ============================================
// 数据模型定义
// ============================================

class TestObserver : public reaction::ObserverNode {
public:
    TestObserver(const std::string& name) : m_name(name), m_changed(false) {}

    void valueChanged(bool changed = true) override {
        m_changed = changed;
        m_callCount++;
        // Call base class to propagate notification to observers
        ObserverNode::valueChanged(changed);
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
// 函数实现
// ============================================

/**
 * Function: Create observer relationship and test notification
 *
 * @param observerName Name for the observer node
 * @param targetName Name for the target node
 * @return std::pair<bool, int> Pair of whether observer was notified and call count
 */
std::pair<bool, int> test_observer_notification(const std::string& observerName, const std::string& targetName) {
    // Create observer and target nodes
    auto observer = std::make_shared<TestObserver>(observerName);
    auto target = std::make_shared<TestObserver>(targetName);
    
    // Reset initial state
    observer->valueChanged(false);
    target->valueChanged(false);
    
    // Create observer relationship using the reaction library
    target->addOneObserver(observer);
    
    // Trigger notification on target
    target->valueChanged(true);
    
    // Return whether observer was notified and the call count
    return {observer->wasChanged(), observer->getCallCount()};
}

}  // namespace test_reaction