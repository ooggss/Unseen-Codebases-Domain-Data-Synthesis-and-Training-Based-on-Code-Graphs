

#include <reaction/reaction.h>

using namespace reaction;

/**
 * @brief Helper function to trigger a DependencyCycleException.
 *
 * @param source Name of the source node.
 * @param target Name of the target node.
 */
void trigger_dependency_cycle_exception(
    const std::string& source,
    const std::string& target) {
    REACTION_THROW_DEPENDENCY_CYCLE(source.c_str(), target.c_str());
}

