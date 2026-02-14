

#include <reaction/reaction.h>

using namespace reaction;

/**
 * @brief Helper function to trigger a NullPointerAccessException.
 *
 * @param context Description of the null pointer access context.
 */
void trigger_null_pointer_access_exception(
    const std::string& context) {
    REACTION_THROW_NULL_POINTER(context.c_str());
}

