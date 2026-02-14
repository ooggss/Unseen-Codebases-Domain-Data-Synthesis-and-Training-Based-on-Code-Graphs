#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

struct AlwaysTriggerResult {
    int recomputeCountAfterInit;
    int recomputeCountAfterDuplicateWrite;
};

/**
 * Function: Demonstrate calc<AlwaysTrig> recomputing even for identical updates
 *
 * @param initialValue Initial value for the tracked variable
 * @return AlwaysTriggerResult Recompute counters before and after duplicate assignment
 */
AlwaysTriggerResult test_always_trigger(int initialValue) {
    using namespace reaction;

    auto source = var(initialValue);

    int recomputeCount = 0;
    auto doubled = calc<AlwaysTrig>([&](int value) {
        ++recomputeCount;
        return value * 2;
    }, source);

    const int countAfterInit = recomputeCount;

    source.value(initialValue);  // Same value written again
    const int countAfterDuplicate = recomputeCount;

    // Force evaluation to avoid unused variable warnings
    (void)doubled.get();

    return AlwaysTriggerResult{
        .recomputeCountAfterInit = countAfterInit,
        .recomputeCountAfterDuplicateWrite = countAfterDuplicate,
    };
}

}  // namespace test_reaction


