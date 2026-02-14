

#include <reaction/reaction.h>

using namespace reaction;

/**
 * @brief Helper function to trigger an InvalidStateException.
 *
 * @param current  Current state description.
 * @param required Required state description.
 */
void trigger_invalid_state_exception(
    const std::string& current,
    const std::string& required) {
    REACTION_THROW_INVALID_STATE(current.c_str(), required.c_str());
}

