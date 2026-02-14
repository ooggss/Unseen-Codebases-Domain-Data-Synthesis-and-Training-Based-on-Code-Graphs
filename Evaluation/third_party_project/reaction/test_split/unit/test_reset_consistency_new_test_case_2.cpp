

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <gtest/gtest.h>

// Include function implementation (normally via header)
#include "test_reset_consistency_function_implementation_2.hpp"

TEST(ResetConsistencyTest, ResetWithMultipleDependenciesPartialFailure) {
    auto a = reaction::var(1);
    auto b = reaction::var(2);

    // Create two calculations
    auto calc1 = reaction::calc([](int x) { return x * 2; }, a);
    auto calc2 = reaction::calc([](int y) { return y + 1; }, b);

    // Make calc1 depend on calc2
    calc1.reset([&]() { return calc2() * 2; });
    EXPECT_EQ(calc1.get(), 6); // (2+1) * 2 = 6

    // Now attempt to make calc2 depend on calc1, creating a cycle
    EXPECT_THROW(calc2.reset([&]() { return calc1() + 1; }), std::runtime_error);

    // Verify calc2 is still in a consistent state
    EXPECT_EQ(calc2.get(), 3); // b(2) + 1 = 3

    // Verify calc2's dependencies are still intact
    b.value(10);
    EXPECT_EQ(calc2.get(), 11); // 10 + 1

    auto result = run_ResetWithMultipleDependenciesPartialFailure_scenario();
    EXPECT_EQ(result.final_calc2_value, 11);
    EXPECT_EQ(result.final_b_value, 10);
}

