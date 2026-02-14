

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace trigger_test_filter_trig {

/**
 * Function: run_filter_trigger_scenario
 *
 * Scenario extracted from TriggerTest.TestFilterTrig:
 * - Create three reactive variables a, b, c
 * - Create ds = a + b
 * - Create dds with FilterTrig: dds = c + ds
 * - Apply a sequence of updates and a filter to dds
 *
 * @return std::pair<int,int> Final values of (ds.get(), dds.get())
 */
std::pair<int, int> run_filter_trigger_scenario() {
    auto a = reaction::var(1);
    auto b = reaction::var(2);
    auto c = reaction::var(3);

    auto ds = reaction::calc(
        [](int aa, double bb) {
            return aa + bb;
        },
        a, b
    );

    auto dds = reaction::calc<reaction::FilterTrig>(
        [](auto cc, auto dsds) {
            return cc + dsds;
        },
        c, ds
    );

    a.value(2);
    // EXPECT_EQ(ds.get(), 4);
    // EXPECT_EQ(dds.get(), 7);

    dds.filter([&]() { return c() + ds() < 10; });

    a.value(3);
    // EXPECT_EQ(dds.get(), 8);

    a.value(5);
    // EXPECT_EQ(dds.get(), 8);

    return {ds.get(), dds.get()};
}

}  // namespace trigger_test_filter_trig

