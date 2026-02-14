

#include <reaction/reaction.h>

using namespace reaction;

/**
 * @brief Convert a list of error codes to their string representations.
 *
 * @param codes Vector of error codes to convert.
 * @return std::vector<std::string> String representations for each code.
 */
std::vector<std::string> convert_error_codes_to_strings(
    const std::vector<ReactionException::ErrorCode>& codes) {
    std::vector<std::string> result;
    result.reserve(codes.size());
    for (auto code : codes) {
        result.push_back(ReactionException::errorCodeToString(code));
    }
    return result;
}

