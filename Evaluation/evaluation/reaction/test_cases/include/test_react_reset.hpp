#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

struct ResetBehaviorSnapshot {
    int beforeResetValue;
    int afterResetValue;
    bool safetyEnabledDuringReset;
};

/**
 * Function: Demonstrate React::reset under thread-safe mode.
 *
 * @param initialValue Initial value assigned to the source var
 * @param multiplier Multiplication factor applied after reset
 * @return ResetBehaviorSnapshot Captures values before/after reset and safety flag
 */
inline ResetBehaviorSnapshot test_react_reset_behavior(int initialValue, int multiplier) {
    using namespace reaction;

    auto &tm = ThreadManager::getInstance();
    tm.resetForTesting();

    auto source = var(initialValue);
    auto factor = var(multiplier);
    auto projection = calc([](int value) {
        return value + 10;
    }, source);

    const int beforeReset = projection.get();

    tm.enableThreadSafety();
    const bool safetyEnabled = tm.isThreadSafetyEnabled();

    projection.reset([](int value, int factorValue) {
        return value * factorValue;
    }, source, factor);

    source.value(initialValue + multiplier);
    const int afterReset = projection.get();

    return ResetBehaviorSnapshot{
        .beforeResetValue = beforeReset,
        .afterResetValue = afterReset,
        .safetyEnabledDuringReset = safetyEnabled,
    };
}

}  // namespace test_reaction

