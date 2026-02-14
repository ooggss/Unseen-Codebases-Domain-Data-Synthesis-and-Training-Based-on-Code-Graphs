

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Function implementation extracted from:
// TEST(BatchOperationsTest, TestRepeatDependency)
namespace batch_operations_impl {

struct RepeatDependencyResult {
    int triggerCount;
    int dsB_value;
};

/**
 * Simulate a dependency graph with repeated dependencies:
 * - dsA depends on a, b
 * - dsB depends on a and dsA
 *
 * @return RepeatDependencyResult containing trigger count and dsB value
 */
RepeatDependencyResult runRepeatDependencyScenario() {
    // ds → A, ds → a, A → a
    auto a = reaction::var(1).setName("a");
    auto b = reaction::var(2).setName("b");

    int triggerCount = 0;
    auto dsA = reaction::calc([&]() { return a() + b(); }).setName("dsA");

    auto dsB = reaction::calc([&]() { ++triggerCount; return a() + dsA(); }).setName("dsB");

    triggerCount = 0;

    reaction::batchExecute([&]() { a.value(2); });

    RepeatDependencyResult result{
        .triggerCount = triggerCount,
        .dsB_value = dsB.get(),
    };
    return result;
}

} // namespace batch_operations_impl

