

#include <reaction/reaction.h>

using namespace reaction;

/**
 * @brief Helper function to trigger a TypeMismatchException.
 *
 * @param expected The expected type name.
 * @param actual   The actual type name encountered.
 */
void trigger_type_mismatch_exception(
    const std::string& expected,
    const std::string& actual) {
    REACTION_THROW_TYPE_MISMATCH(expected.c_str(), actual.c_str());
}

