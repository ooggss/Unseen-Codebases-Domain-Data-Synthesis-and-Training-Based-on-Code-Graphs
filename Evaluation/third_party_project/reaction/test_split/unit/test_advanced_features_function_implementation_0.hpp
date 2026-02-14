

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

/**
 * Function: execute_action_test_flow
 *
 * This function encapsulates the core logic of the original
 * `AdvancedFeaturesTest.TestAction` test:
 * - create reactive variables `a` and `b`
 * - create an action `at` that depends on `a` and `b`
 * - create another action `att` that depends on `at` and flips `trigger`
 *   when `at` is triggered
 * - update `a` so that the reaction graph is executed
 *
 * @return bool Whether the trigger action has been fired after updating `a`.
 */
bool execute_action_test_flow() {
    auto a = reaction::var(1);
    auto b = reaction::var(3.14);
    auto at = reaction::action(
        [](int aa, double bb) {
            std::cout << "a = " << aa << '\t' << "b = " << bb << '\t';
        },
        a, b);

    bool trigger = false;
    auto att = reaction::action(
        [&]([[maybe_unused]] auto atat) {
            trigger = true;
            std::cout << "at trigger " << std::endl;
        },
        at);

    trigger = false;

    a.value(2);

    return trigger;
}

