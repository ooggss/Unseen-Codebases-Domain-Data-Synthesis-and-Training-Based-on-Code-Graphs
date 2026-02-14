#pragma once

#include <reaction/reaction.h>
#include <cstdint>

namespace test_reaction {

struct AtomicCompoundSnapshot {
    int afterAddition;
    int afterMultiplication;
    int afterBitwiseAnd;
    int afterShift;
    int postIncrementReturn;
    int finalValue;
    int calcEvaluations;
};

/**
 * Function: Demonstrate atomic compound assignments on a reactive counter.
 *
 * @return AtomicCompoundSnapshot Snapshot with values after each compound operation.
 */
inline AtomicCompoundSnapshot test_atomic_compound_assign() {
    using namespace reaction;

    auto counter = var(2);

    int evaluationCount = 0;
    auto tracker = calc([&](int value) {
        ++evaluationCount;
        return value;
    }, counter);

    counter += 3;
    const int afterAddition = tracker();

    counter *= 4;
    const int afterMultiplication = tracker();

    counter &= 0xF;
    const int afterBitwiseAnd = tracker();

    counter <<= 2;
    const int afterShift = tracker();

    const int postIncrementReturn = counter++;
    const int finalValue = tracker();

    return AtomicCompoundSnapshot{
        .afterAddition = afterAddition,
        .afterMultiplication = afterMultiplication,
        .afterBitwiseAnd = afterBitwiseAnd,
        .afterShift = afterShift,
        .postIncrementReturn = postIncrementReturn,
        .finalValue = finalValue,
        .calcEvaluations = evaluationCount,
    };
}

}  // namespace test_reaction


