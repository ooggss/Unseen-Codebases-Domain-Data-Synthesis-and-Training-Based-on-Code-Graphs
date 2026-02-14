

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Function implementation extracted from:
// TEST(BatchOperationsTest, TestRepeatDependency3)
namespace batch_operations_impl {

struct RepeatDependency3Result {
    int triggerCount_after_batch;
    int ds_after_batch;
    int ds_after_resetA1;
};

/**
 * Simulate deep nested dependency scenarios:
 * - ds depends on A, B
 * - A depends on A1, A1 on A2, A2 on a
 * - B depends on B1, B1 on a
 *
 * @return RepeatDependency3Result capturing trigger count and ds values.
 */
RepeatDependency3Result runRepeatDependencyScenario3() {
    // ds → A, ds → B, A → A1, A1 → A2, A2 → a, B → B1, B1 → a
    auto a = reaction::var(1).setName("a");
    auto b = reaction::var(1).setName("b");

    int triggerCount = 0;
    auto A2 = reaction::calc([&]() { return a() * 2; }).setName("A2");
    auto A1 = reaction::calc([&]() { return A2() + 1; }).setName("A1");
    auto A = reaction::calc([&]() { return A1() - 1; }).setName("A");

    auto B1 = reaction::calc([&]() { return a() - 1; }).setName("B1");
    auto B = reaction::calc([&]() { return B1() + 1; }).setName("B");

    auto ds = reaction::calc([&]() { ++triggerCount; return A() + B(); }).setName("ds");
    triggerCount = 0;

    reaction::batchExecute([&]() { a.value(2); });

    int triggerCount_after_batch = triggerCount;
    int ds_after_batch = ds.get();

    A1.reset([&]() { return b(); });
    int ds_after_resetA1 = ds.get();

    RepeatDependency3Result result{
        .triggerCount_after_batch = triggerCount_after_batch,
        .ds_after_batch = ds_after_batch,
        .ds_after_resetA1 = ds_after_resetA1,
    };
    return result;
}

} // namespace batch_operations_impl

