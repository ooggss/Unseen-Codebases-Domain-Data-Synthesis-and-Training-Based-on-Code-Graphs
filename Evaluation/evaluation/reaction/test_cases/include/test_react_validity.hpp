#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

struct ValiditySnapshot {
    bool firstValidBeforeClose;
    bool firstValidAfterClose;
    bool copiesEqualBeforeClose;
    bool copiesEqualAfterClose;
    bool equalityCheckFailedAfterClose;
};

/**
 * Function: Demonstrate React::operator bool and operator== for validity tracking.
 *
 * @param initialValue Initial value stored inside the reactive variable
 * @return ValiditySnapshot Snapshot describing validity/equality before and after close
 */
inline ValiditySnapshot test_react_validity(int initialValue) {
    using namespace reaction;

    auto source = var(initialValue);
    React copy = source;  // copy constructor retains same node

    const bool beforeValid = static_cast<bool>(source);
    const bool equalBefore = (source == copy);

    source.close();

    const bool afterValid = static_cast<bool>(source);

    bool equalAfter = false;
    bool equalityFailedAfterClose = false;
    try {
        equalAfter = (source == copy);
    } catch (const std::exception &) {
        equalityFailedAfterClose = true;
    }

    return ValiditySnapshot{
        .firstValidBeforeClose = beforeValid,
        .firstValidAfterClose = afterValid,
        .copiesEqualBeforeClose = equalBefore,
        .copiesEqualAfterClose = equalAfter,
        .equalityCheckFailedAfterClose = equalityFailedAfterClose,
    };
}

}  // namespace test_reaction

