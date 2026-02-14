

#include <reaction/reaction.h>

using namespace reaction;

/**
 * @brief Helper function to trigger a SelfObservationException.
 *
 * @param node_name Name of the node that observes itself.
 */
void trigger_self_observation_exception(
    const std::string& node_name) {
    REACTION_THROW_SELF_OBSERVATION(node_name.c_str());
}

