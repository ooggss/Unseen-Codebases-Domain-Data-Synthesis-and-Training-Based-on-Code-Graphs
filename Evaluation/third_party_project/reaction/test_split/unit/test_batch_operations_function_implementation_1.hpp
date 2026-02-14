

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Function implementation extracted from:
// TEST(BatchOperationsTest, TestRepeatDependency2)
namespace batch_operations_impl {

struct RepeatDependency2Result {
    int triggerCount_after_a3;
    int ds_after_a3;
    int triggerCount_after_batch;
    int ds_after_batch;
    int triggerCount_after_a1;
    int ds_after_a1;
};

/**
 * Simulate a more complex repeated dependency scenario:
 * - ds depends on A, B, C
 * - A, B depend on a
 *
 * @return RepeatDependency2Result with trigger counts and ds values
 *         at different stages.
 */
RepeatDependency2Result runRepeatDependencyScenario2() {
    // ds → A, ds → B, ds → C, A → a, B → a
    int triggerCount = 0;
    auto a = reaction::var(1).setName("a");
    auto A = reaction::calc([&]() { return a() + 1; }).setName("A");
    auto B = reaction::calc([&]() { return a() + 2; }).setName("B");
    auto C = reaction::calc([&]() { return 5; }).setName("C");
    auto ds = reaction::calc([&]() {
        ++triggerCount;
        return A() + B() + C();
    }).setName("ds");

    auto ba = reaction::batch([&]() { a.value(2); });

    triggerCount = 0;
    a.value(3);
    int triggerCount_after_a3 = triggerCount;
    int ds_after_a3 = ds.get();

    triggerCount = 0;
    ba.execute();
    int triggerCount_after_batch = triggerCount;
    int ds_after_batch = ds.get();

    triggerCount = 0;
    a.value(1);
    int triggerCount_after_a1 = triggerCount;
    int ds_after_a1 = ds.get();

    RepeatDependency2Result result{
        .triggerCount_after_a3 = triggerCount_after_a3,
        .ds_after_a3 = ds_after_a3,
        .triggerCount_after_batch = triggerCount_after_batch,
        .ds_after_batch = ds_after_batch,
        .triggerCount_after_a1 = triggerCount_after_a1,
        .ds_after_a1 = ds_after_a1,
    };
    return result;
}

} // namespace batch_operations_impl

