#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

struct BatchLifecycleResult {
    bool closedInitially;
    bool closedAfterClose;
    int recomputeCountAfterExecute;
};

/**
 * Function: Exercise manual Batch lifecycle controls
 *
 * @param initialValue Starting value for the reactive variable
 * @param updatedValue Value assigned inside the batch lambda
 * @return BatchLifecycleResult Snapshot of lifecycle flags and recompute count
 */
BatchLifecycleResult test_batch_manual_lifecycle(int initialValue, int updatedValue) {
    using namespace reaction;

    auto reactiveValue = var(initialValue);

    int recomputeCount = 0;
    auto doubled = calc([&](int value) {
        ++recomputeCount;
        return value * 2;
    }, reactiveValue);

    auto batchObject = batch([&]() {
        reactiveValue.value(updatedValue);
    });

    const bool closedInitially = batchObject.isClosed();

    batchObject.execute();
    const int recomputeAfterExecute = recomputeCount;

    batchObject.close();
    const bool closedAfterClose = batchObject.isClosed();

    (void)doubled.get();

    return BatchLifecycleResult{
        .closedInitially = closedInitially,
        .closedAfterClose = closedAfterClose,
        .recomputeCountAfterExecute = recomputeAfterExecute,
    };
}

}  // namespace test_reaction


