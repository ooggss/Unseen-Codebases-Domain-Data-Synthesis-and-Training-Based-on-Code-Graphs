

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace invalidation_test_impl {

// Encapsulate the original "TestCloseHandle" logic into a function
// Return a simple struct capturing all values needed for assertions.
struct CloseHandleResult {
    bool dsB_valid;
    bool dsC_valid;
    bool dsD_valid;
    bool dsE_valid;
    bool dsF_valid;
    bool dsG_valid;
};

CloseHandleResult runCloseHandleScenario() {
    auto a = reaction::var(1).setName("a");
    auto b = reaction::var(2).setName("b");

    auto dsB = reaction::calc([](auto aa) { return aa; }, a).setName("dsB");
    auto dsC = reaction::calc([](auto aa) { return aa; }, a).setName("dsC");
    auto dsD = reaction::calc([](auto aa) { return aa; }, a).setName("dsD");
    auto dsE = reaction::calc([](auto aa) { return aa; }, a).setName("dsE");
    auto dsF = reaction::calc([](auto aa) { return aa; }, a).setName("dsF");
    auto dsG = reaction::calc([](auto aa) { return aa; }, a).setName("dsG");

    {
        auto dsA = reaction::calc<reaction::ChangeTrig, reaction::CloseHandle>(
                       [](int aa) { return aa; }, a)
                       .setName("dsA");
        dsB.reset([&]() { return a() + dsA(); });
        dsC.reset([&]() { return a() + dsA() + dsB(); });
        dsD.reset([&]() { return dsA() + dsB() + dsC(); });
        dsE.reset([&]() { return dsB() * dsC() + dsD(); });
        dsF.reset([&]() { return a() + b(); });
        dsG.reset([&]() { return dsA() + dsF(); });
    }

    CloseHandleResult result{
        .dsB_valid = static_cast<bool>(dsB),
        .dsC_valid = static_cast<bool>(dsC),
        .dsD_valid = static_cast<bool>(dsD),
        .dsE_valid = static_cast<bool>(dsE),
        .dsF_valid = static_cast<bool>(dsF),
        .dsG_valid = static_cast<bool>(dsG),
    };
    return result;
}

}  // namespace invalidation_test_impl

