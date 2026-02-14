

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Function implementation extracted from:
// TEST(BatchOperationsTest, TestMultipleBatchesWithSharedDependencies)
namespace batch_operations_impl {

struct MultipleBatchesResult {
    // Initial values
    int X0, Y0, Z0, obs10, obs20, obs30, obs40, obs50, obs60;

    // State and counters before any batch execute
    int a_before, b_before, c_before, obs6_before;
    int triggerX_before, triggerA_before;

    // After batch1
    int a1, b1, c1;
    int X1, Y1, Z1, obs11, obs21, obs31, obs41, obs51, obs61;
    int triggerX1, triggerY1, triggerZ1;
    int triggerA1, triggerB1, triggerC1;

    // After batch2
    int a2, b2, c2;
    int X2, Y2, Z2, obs12, obs22, obs32, obs42, obs52, obs62;
    int triggerX2, triggerY2, triggerZ2;
    int triggerA2, triggerB2, triggerC2;

    // After batch3
    int a3, b3, c3;
    int X3, Y3, Z3, obs13, obs23, obs33, obs43, obs53, obs63;
    int triggerX3, triggerY3, triggerZ3;
    int triggerA3, triggerB3, triggerC3;
};

/**
 * Multiple batches with shared dependencies:
 * - Creates three batches and executes them sequentially
 * - Tracks values and trigger counts.
 *
 * @return MultipleBatchesResult containing all snapshots.
 */
MultipleBatchesResult runMultipleBatchesWithSharedDependenciesScenario() {
    MultipleBatchesResult r{};

    // Create shared data sources
    auto a = reaction::var(1).setName("a");
    auto b = reaction::var(2).setName("b");
    auto c = reaction::var(3).setName("c");

    // Create computed values with complex dependencies
    auto X = reaction::calc([&]() { return a() + b(); }).setName("X");
    auto Y = reaction::calc([&]() { return b() * c(); }).setName("Y");
    auto Z = reaction::calc([&]() { return X() + Y(); }).setName("Z");

    // Trackers for computed values
    int triggerCountX = 0, triggerCountY = 0, triggerCountZ = 0;
    int triggerCountA = 0, triggerCountB = 0, triggerCountC = 0;

    // Observers
    auto obs1 = reaction::calc([&]() {
        triggerCountX++;
        return X() + c();
    }).setName("obs1");

    auto obs2 = reaction::calc([&]() {
        triggerCountY++;
        return Y() + a();
    }).setName("obs2");

    auto obs3 = reaction::calc([&]() {
        triggerCountZ++;
        return Z() + obs1() + obs2();
    }).setName("obs3");

    auto obs4 = reaction::calc([&]() {
        triggerCountA++;
        return a() + obs3();
    }).setName("obs4");

    auto obs5 = reaction::calc([&]() {
        triggerCountB++;
        return b() + obs4();
    }).setName("obs5");

    auto obs6 = reaction::calc([&]() {
        triggerCountC++;
        return c() + obs5() + obs3();
    }).setName("obs6");

    // Precompute initial values
    r.X0 = X.get();
    r.Y0 = Y.get();
    r.Z0 = Z.get();
    r.obs10 = obs1.get();
    r.obs20 = obs2.get();
    r.obs30 = obs3.get();
    r.obs40 = obs4.get();
    r.obs50 = obs5.get();
    r.obs60 = obs6.get();

    // Reset counters
    triggerCountX = triggerCountY = triggerCountZ = 0;
    triggerCountA = triggerCountB = triggerCountC = 0;

    // Create batches
    auto batch1 = reaction::batch([&]() {
        a.value(10);
    });

    auto batch2 = reaction::batch([&]() {
        b.value(20);
        c.value(30);
    });

    auto batch3 = reaction::batch([&]() {
        a.value(100);
        c.value(300);
    });

    // State before executing any batch
    r.a_before = a.get();
    r.b_before = b.get();
    r.c_before = c.get();
    r.obs6_before = obs6.get();
    r.triggerX_before = triggerCountX;
    r.triggerA_before = triggerCountA;

    // Execute batch1
    batch1.execute();

    r.a1 = a.get();
    r.b1 = b.get();
    r.c1 = c.get();
    r.X1 = X.get();
    r.Y1 = Y.get();
    r.Z1 = Z.get();
    r.obs11 = obs1.get();
    r.obs21 = obs2.get();
    r.obs31 = obs3.get();
    r.obs41 = obs4.get();
    r.obs51 = obs5.get();
    r.obs61 = obs6.get();

    r.triggerX1 = triggerCountX;
    r.triggerY1 = triggerCountY;
    r.triggerZ1 = triggerCountZ;
    r.triggerA1 = triggerCountA;
    r.triggerB1 = triggerCountB;
    r.triggerC1 = triggerCountC;

    // Reset counters for next batch
    triggerCountX = triggerCountY = triggerCountZ = 0;
    triggerCountA = triggerCountB = triggerCountC = 0;

    // Execute batch2
    batch2.execute();

    r.a2 = a.get();
    r.b2 = b.get();
    r.c2 = c.get();
    r.X2 = X.get();
    r.Y2 = Y.get();
    r.Z2 = Z.get();
    r.obs12 = obs1.get();
    r.obs22 = obs2.get();
    r.obs32 = obs3.get();
    r.obs42 = obs4.get();
    r.obs52 = obs5.get();
    r.obs62 = obs6.get();

    r.triggerX2 = triggerCountX;
    r.triggerY2 = triggerCountY;
    r.triggerZ2 = triggerCountZ;
    r.triggerA2 = triggerCountA;
    r.triggerB2 = triggerCountB;
    r.triggerC2 = triggerCountC;

    // Reset counters for next batch
    triggerCountX = triggerCountY = triggerCountZ = 0;
    triggerCountA = triggerCountB = triggerCountC = 0;

    // Execute batch3
    batch3.execute();

    r.a3 = a.get();
    r.b3 = b.get();
    r.c3 = c.get();
    r.X3 = X.get();
    r.Y3 = Y.get();
    r.Z3 = Z.get();
    r.obs13 = obs1.get();
    r.obs23 = obs2.get();
    r.obs33 = obs3.get();
    r.obs43 = obs4.get();
    r.obs53 = obs5.get();
    r.obs63 = obs6.get();

    r.triggerX3 = triggerCountX;
    r.triggerY3 = triggerCountY;
    r.triggerZ3 = triggerCountZ;
    r.triggerA3 = triggerCountA;
    r.triggerB3 = triggerCountB;
    r.triggerC3 = triggerCountC;

    return r;
}

} // namespace batch_operations_impl

