#pragma once

#include <reaction/concurrency/global_state.h>

namespace test_reaction {

struct GlobalStateSnapshot {
    bool trackingActiveBefore;
    bool batchActiveBefore;
    bool batchFunActiveBefore;

    bool trackingActiveInRegGuard;
    bool batchFunActiveInBatchGuard;
    bool batchActiveInBatchExeGuard;

    bool trackingActiveAfter;
    bool batchActiveAfter;
    bool batchFunActiveAfter;
};

/**
 * Function: Demonstrate ScopedValue-based global state guards in reaction.
 *
 * This function exercises RegFunGuard, BatchFunGuard, BatchExeGuard and the
 * associated query helpers isDependencyTrackingActive, isBatchFunctionActive,
 * isBatchActive together with resetGlobalState.
 *
 * @return GlobalStateSnapshot Snapshot of boolean flags before, during and after guards.
 */
inline GlobalStateSnapshot test_global_state_scoped_guards() {
    using namespace reaction;

    resetGlobalState();

    GlobalStateSnapshot snapshot{};
    snapshot.trackingActiveBefore = isDependencyTrackingActive();
    snapshot.batchActiveBefore = isBatchActive();
    snapshot.batchFunActiveBefore = isBatchFunctionActive();

    {
        RegFunGuard guard([](const NodePtr &) {});
        snapshot.trackingActiveInRegGuard = isDependencyTrackingActive();
    }

    {
        BatchFunGuard guard([](const NodePtr &) {});
        snapshot.batchFunActiveInBatchGuard = isBatchFunctionActive();
    }

    {
        BatchExeGuard guard(true);
        snapshot.batchActiveInBatchExeGuard = isBatchActive();
    }

    resetGlobalState();
    snapshot.trackingActiveAfter = isDependencyTrackingActive();
    snapshot.batchActiveAfter = isBatchActive();
    snapshot.batchFunActiveAfter = isBatchFunctionActive();

    return snapshot;
}

}  // namespace test_reaction


