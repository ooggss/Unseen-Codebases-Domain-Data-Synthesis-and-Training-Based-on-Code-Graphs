#pragma once

#include <reaction/core/observer_node.h>
#include <reaction/graph/observer_graph.h>
#include <memory>
#include <string>

namespace test_reaction {

// ============================================
// Function Implementation
// ============================================

/**
 * Function: Test observer node naming functionality
 *
 * @param name Name to set for the observer node
 * @return std::string The retrieved name from the observer graph
 */
std::string test_observer_naming(const std::string& name) {
    using namespace reaction;

    // Create an observer node
    auto node = std::make_shared<ObserverNode>();

    // Get observer graph instance
    auto& graph = ObserverGraph::getInstance();

    // Set name for the node
    graph.setName(node, name);

    // Get and return the name
    return graph.getName(node);
}

}  // namespace test_reaction