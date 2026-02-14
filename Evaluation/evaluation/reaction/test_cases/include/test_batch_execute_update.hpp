#pragma once

#include <reaction/reaction.h>
#include <tuple>

namespace test_reaction {

struct BatchExecuteResult {
    int recomputeCountBeforeBatch;
    int recomputeCountAfterBatch;
    int finalValue;
};

/**
 * Function: Verify batchExecute aggregates multiple updates
 *
 * @param baseValue Initial value for the reactive variable
 * @param deltaA First increment applied inside batch
 * @param deltaB Second increment applied inside batch
 * @return BatchExecuteResult Recompute counts and final calculation value
 */
BatchExecuteResult test_batch_execute_update(int baseValue, int deltaA, int deltaB) {
    using namespace reaction;

    auto reactiveValue = var(baseValue);

    int recomputeCount = 0;
    auto doubled = calc([&](int value) {
        ++recomputeCount;
        return value * 2;
    }, reactiveValue);

    const int beforeBatch = recomputeCount;

    batchExecute([&]() {
        reactiveValue.value(baseValue + deltaA);
        reactiveValue.value(baseValue + deltaA + deltaB);
    });

    const int afterBatch = recomputeCount;

    return BatchExecuteResult{
        .recomputeCountBeforeBatch = beforeBatch,
        .recomputeCountAfterBatch = afterBatch,
        .finalValue = doubled.get(),
    };
}

}  // namespace test_reaction


