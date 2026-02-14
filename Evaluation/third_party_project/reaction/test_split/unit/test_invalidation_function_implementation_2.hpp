

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace invalidation_test_impl {

// Encapsulate the original "TestLastHandle" logic into a function
// Return final values of dsB and dsC both before and after 'a' changes.
struct LastHandleResult {
    int dsB_initial;
    int dsC_initial;
    int dsB_after_a_change;
    int dsC_after_a_change;
};

LastHandleResult runLastHandleScenario() {
    auto a = reaction::var(1).setName("a");

    auto dsB = reaction::calc([](auto aa) { return aa; }, a).setName("dsB");
    auto dsC = reaction::calc([](auto aa) { return aa; }, a).setName("dsC");

    {
        auto dsA = reaction::calc<reaction::ChangeTrig, reaction::LastHandle>(
                       [](int aa) { return aa; }, a)
                       .setName("dsA");

        dsB.reset([](int aa, int AA) { return aa + AA; }, a, dsA);
        dsC.reset([](int aa, int AA, int BB) { return aa + AA + BB; }, a, dsA, dsB);
    }

    LastHandleResult result{};
    // Initial values
    result.dsB_initial = dsB.get();
    result.dsC_initial = dsC.get();

    // Change a and record resulting values
    a.value(10);
    result.dsB_after_a_change = dsB.get();
    result.dsC_after_a_change = dsC.get();

    return result;
}

}  // namespace invalidation_test_impl

