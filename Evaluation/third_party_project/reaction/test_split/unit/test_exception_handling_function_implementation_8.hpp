

#include <reaction/reaction.h>

using namespace reaction;

/**
 * @brief Helper function to trigger a BatchOperationConflictException.
 *
 * @param description Description of the conflicting operations.
 */
void trigger_batch_operation_conflict_exception(
    const std::string& description) {
    REACTION_THROW_BATCH_CONFLICT(description.c_str());
}

