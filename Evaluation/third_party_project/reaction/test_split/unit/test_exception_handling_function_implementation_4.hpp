

#include <reaction/reaction.h>

using namespace reaction;

/**
 * @brief Helper function to trigger a ResourceNotInitializedException.
 *
 * @param resource_type The type/name of the resource not initialized.
 */
void trigger_resource_not_initialized_exception(
    const std::string& resource_type) {
    REACTION_THROW_RESOURCE_NOT_INITIALIZED(resource_type.c_str());
}

