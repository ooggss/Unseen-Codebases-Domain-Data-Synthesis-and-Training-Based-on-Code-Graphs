

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Function implementation extracted from:
// TEST(BatchOperationsTest, TestRepeatDependency4)
namespace batch_operations_impl {

struct RepeatDependency4Result {
    int triggerCountA;
    int ds_a_value;
    int triggerCountB;
    int ds_b_value;
    int triggerCountC;
    int ds_c_value;
};

/**
 * Scenario with repeat nodes dependented by others:
 * - ds_a and ds_b both depend on A, B, C
 * - ds_c depends on ds_a and ds_b
 *
 * @return RepeatDependency4Result with trigger counts and ds values.
 */
RepeatDependency4Result runRepeatDependencyScenario4() {
    int triggerCountA = 0;
    int triggerCountB = 0;
    int triggerCountC = 0;

    auto a = reaction::var(1).setName("a");
    auto A = reaction::calc([&]() { return a() + 1; }).setName("A");
    auto B = reaction::calc([&]() { return a() + 2; }).setName("B");
    auto C = reaction::calc([&]() { return 5; }).setName("C");
    auto ds_a = reaction::calc([&]() {
        ++triggerCountA;
        return A() + B() + C();
    }).setName("ds_a");
    auto ds_b = reaction::calc([&]() {
        ++triggerCountB;
        return A() + B() + C();
    }).setName("ds_b");
    auto ds_c = reaction::calc([&]() {
        ++triggerCountC;
        return ds_a() + ds_b();
    }).setName("ds_c");

    triggerCountA = 0;
    triggerCountB = 0;
    triggerCountC = 0;

    reaction::batchExecute([&]() { a.value(2); });

    RepeatDependency4Result result{
        .triggerCountA = triggerCountA,
        .ds_a_value = ds_a.get(),
        .triggerCountB = triggerCountB,
        .ds_b_value = ds_b.get(),
        .triggerCountC = triggerCountC,
        .ds_c_value = ds_c.get(),
    };
    return result;
}

} // namespace batch_operations_impl

