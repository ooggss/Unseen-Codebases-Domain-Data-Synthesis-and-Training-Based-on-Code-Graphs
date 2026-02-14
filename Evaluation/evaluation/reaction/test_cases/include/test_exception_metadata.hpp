#pragma once

#include <reaction/core/exception.h>
#include <string>

namespace test_reaction {

struct ExceptionInfo {
    std::string formattedMessage;
    std::string originalMessage;
    std::string file;
    int line;
    std::string function;
    std::string codeName;
};

/**
 * Function: Capture metadata from a ReactionException instance.
 *
 * @param message Error message to embed
 * @param code ReactionException error code
 * @param file Source file metadata
 * @param line Line number metadata
 * @param function Function name metadata
 * @return ExceptionInfo Snapshot of stored information
 */
inline ExceptionInfo capture_exception_info(const std::string &message,
    reaction::ReactionException::ErrorCode code,
    const std::string &file,
    int line,
    const std::string &function) {
    reaction::ReactionException ex(message, code, file, line, function);

    ExceptionInfo info;
    info.formattedMessage = ex.what();
    info.originalMessage = ex.getOriginalMessage();
    info.file = ex.getFile();
    info.line = ex.getLine();
    info.function = ex.getFunction();
    info.codeName = reaction::ReactionException::errorCodeToString(ex.getErrorCode());
    return info;
}

}  // namespace test_reaction

