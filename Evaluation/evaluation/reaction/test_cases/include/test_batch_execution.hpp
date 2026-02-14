#pragma once

#include <reaction/reaction.h>
#include <tuple>

namespace test_reaction {

// ============================================
// Function implementations
// ============================================

/**
 * Function: Test batch execution reduces recomputation count
 *
 * @param initialA Initial value for variable a
 * @param initialB Initial value for variable b
 * @param nonBatchA Value to set a without batching
 * @param nonBatchB Value to set b without batching
 * @param batchA Value to set a within batch
 * @param batchB Value to set b within batch
 * @return std::tuple<int, int, int> {final sum, count after non-batch updates, count after batch updates}
 */
std::tuple<int, int, int> test_batch_execution(int initialA,
                                               int initialB,
                                               int nonBatchA,
                                               int nonBatchB,
                                               int batchA,
                                               int batchB) {
    using namespace reaction;

    auto varA = var(initialA);
    auto varB = var(initialB);

    int recomputeCount = 0;

    auto sumCalc = calc([&](int x, int y) {
        ++recomputeCount;
        return x + y;
    }, varA, varB);

    // Non-batch updates trigger recompute each time
    varA.value(nonBatchA);
    varB.value(nonBatchB);
    const int countAfterNonBatch = recomputeCount;

    // Batch updates should trigger recompute only once for both changes
    auto updateBatch = batch([&] {
        varA.value(batchA);
        varB.value(batchB);
    });
    updateBatch.execute();
    const int countAfterBatch = recomputeCount;

    return {sumCalc.get(), countAfterNonBatch, countAfterBatch};
}

}  // namespace test_reaction

