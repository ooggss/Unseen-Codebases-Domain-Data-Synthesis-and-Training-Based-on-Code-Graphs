#pragma once

#include <reaction/core/observer_node.h>
#include <reaction/graph/observer_graph.h>
#include <memory>

namespace test_reaction {

// ============================================
// Function Implementation
// ============================================

/**
 * Function: Test batch operations on observer nodes
 *
 * @return bool Whether batch operations work correctly
 */
bool test_batch_operations() {
    using namespace reaction;

    // Create observer nodes
    auto node1 = std::make_shared<ObserverNode>();
    auto node2 = std::make_shared<ObserverNode>();

    // Get observer graph instance
    auto& graph = ObserverGraph::getInstance();

    // Create a batch ID
    const void* batchId = &batchId;

    // Register nodes to active batch
    graph.registerActiveBatch(batchId, {node1, node2});

    // Check if nodes are in active batch
    bool node1InBatch = graph.isNodeInActiveBatch(node1);
    bool node2InBatch = graph.isNodeInActiveBatch(node2);

    // Unregister the batch
    graph.unregisterActiveBatch(batchId);

    // Check if nodes are no longer in active batch
    bool node1NotInBatch = !graph.isNodeInActiveBatch(node1);
    bool node2NotInBatch = !graph.isNodeInActiveBatch(node2);

    // Return true if all operations succeeded
    return node1InBatch && node2InBatch && node1NotInBatch && node2NotInBatch;
}

}  // namespace test_reaction