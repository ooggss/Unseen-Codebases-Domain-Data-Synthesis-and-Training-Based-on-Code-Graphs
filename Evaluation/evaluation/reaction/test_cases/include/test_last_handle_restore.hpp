#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

struct LastHandleSnapshot {
    int initialValue;
    int afterUpdate;
    int afterSourceClose;
};

/**
 * Function: Verify LastHandle preserves the last computed result after closing the source node.
 *
 * @param initialValue Starting value of the reactive variable
 * @param updatedValue Value assigned before closing the source
 * @return LastHandleSnapshot Recorded calculation results across each phase
 */
LastHandleSnapshot test_last_handle_restore(int initialValue, int updatedValue) {
    using namespace reaction;

    auto source = var(initialValue);

    auto guardedCalc = calc<ChangeTrig, LastHandle>([](int value) {
        return value * 2;
    }, source);

    const int initialResult = guardedCalc.get();

    source.value(updatedValue);
    const int updatedResult = guardedCalc.get();

    source.close();
    const int restoredResult = guardedCalc.get();

    return LastHandleSnapshot{
        .initialValue = initialResult,
        .afterUpdate = updatedResult,
        .afterSourceClose = restoredResult,
    };
}

}  // namespace test_reaction


