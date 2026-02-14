

#include <reaction/reaction.h>

using namespace reaction;

/**
 * @brief Helper function to trigger a ThreadSafetyViolationException.
 *
 * @param operation Description of the unsafe operation.
 */
void trigger_thread_safety_violation_exception(
    const std::string& operation) {
    REACTION_THROW_THREAD_SAFETY_VIOLATION(operation.c_str());
}

