#pragma once

#include <reaction/core/exception.h>
#include <string>
#include <vector>

namespace test_reaction {

/**
 * Function: Map ReactionException error codes to descriptive strings.
 *
 * @param codes List of ReactionException::ErrorCode values to describe
 * @return std::vector<std::string> Human-readable names for each code
 */
inline std::vector<std::string> describe_error_codes(
    const std::vector<reaction::ReactionException::ErrorCode> &codes) {
    std::vector<std::string> descriptions;
    descriptions.reserve(codes.size());

    for (auto code : codes) {
        descriptions.push_back(reaction::ReactionException::errorCodeToString(code));
    }

    return descriptions;
}

}  // namespace test_reaction

