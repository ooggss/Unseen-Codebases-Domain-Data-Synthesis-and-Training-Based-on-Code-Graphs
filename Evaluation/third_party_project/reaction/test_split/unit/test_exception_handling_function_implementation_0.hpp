

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include <reaction/reaction.h>

using namespace reaction;

/**
 * @brief Helper function to trigger a basic ReactionException.
 *
 * @param message The message used when throwing the exception.
 * @param code    The error code used when throwing the exception.
 *
 * This function always throws a ReactionException using the REACTION_THROW macro.
 */
void trigger_basic_reaction_exception(
    const std::string& message,
    ReactionException::ErrorCode code) {
    REACTION_THROW(ReactionException, message.c_str(), code);
}

