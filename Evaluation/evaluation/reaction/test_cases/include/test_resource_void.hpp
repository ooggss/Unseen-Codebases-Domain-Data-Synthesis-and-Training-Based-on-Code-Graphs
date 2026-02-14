#pragma once

#include <reaction/core/resource.h>
#include <reaction/graph/observer_graph.h>
#include <memory>
#include <string>
#include <type_traits>

namespace test_reaction {

struct VoidResourceSnapshot {
    bool retrievedIsVoid;
    bool usesSboStorage;
    bool nameAssigned;
    bool nameClearedAfterClose;
};

/**
 * Function: Demonstrate Resource<Void> behavior and graph integration.
 *
 * @param nodeName Name to assign while the node is registered
 * @return VoidResourceSnapshot Snapshot of SBO usage and naming lifecycle
 */
inline VoidResourceSnapshot test_resource_void_behavior(const std::string &nodeName) {
    using namespace reaction;

    auto voidResource = std::make_shared<Resource<Void>>();
    const bool usesSboStorage = voidResource->isUsingSBO();

    const auto value = voidResource->getValue();
    const bool retrievedIsVoid =
        std::is_same_v<std::remove_cvref_t<decltype(value)>, Void>;

    auto &graph = ObserverGraph::getInstance();
    graph.addNode(voidResource);
    graph.setName(voidResource, nodeName);
    const bool nameAssigned = graph.getName(voidResource) == nodeName;

    graph.closeNode(voidResource);
    const bool nameClearedAfterClose = graph.getName(voidResource).empty();

    return VoidResourceSnapshot{
        .retrievedIsVoid = retrievedIsVoid,
        .usesSboStorage = usesSboStorage,
        .nameAssigned = nameAssigned,
        .nameClearedAfterClose = nameClearedAfterClose,
    };
}

}  // namespace test_reaction

