

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <gtest/gtest.h>

// Include function implementation (normally via header)
#include "test_reset_consistency_function_implementation_5.hpp"

TEST(ResetConsistencyTest, ResetVoidExpressionConsistency) {
    auto a = reaction::var(1);
    auto b = reaction::var(2);

    // Create calculations that will form a cycle
    auto calc1 = reaction::calc([](int x) { return x; }, a);
    auto calc2 = reaction::calc([](int y) { return y; }, b);

    // First, make calc1 depend on calc2
    calc1.reset([&]() { return calc2() + 1; });
    EXPECT_EQ(calc1.get(), 3); // b(2) + 1 = 3

    // Now attempt to make calc2 depend on calc1, creating a cycle
    EXPECT_THROW(calc2.reset([&]() { return calc1() + 1; }), std::runtime_error);

    // Verify calc2 is still in a consistent state
    EXPECT_EQ(calc2.get(), 2);

    // Verify calc2's dependencies are still intact
    b.value(5);
    EXPECT_EQ(calc2.get(), 5);

    auto result = run_ResetVoidExpressionConsistency_scenario();
    EXPECT_EQ(result.final_calc2_value, 5);
    EXPECT_EQ(result.final_b_value, 5);
}

