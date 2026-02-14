

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <gtest/gtest.h>

// Include function implementation (normally via header)
#include "test_reset_consistency_function_implementation_0.hpp"

TEST(ResetConsistencyTest, ResetCycleDependencyRollback) {
    auto a = reaction::var(1);
    auto b = reaction::var(2);

    // Create a valid calculation first
    auto calc = reaction::calc([](int x, int y) { return x + y; }, a, b);
    EXPECT_EQ(calc.get(), 3);

    // Change values and verify calculation still works
    a.value(10);
    EXPECT_EQ(calc.get(), 12);

    // Attempt to reset with a cycle dependency (should fail and rollback)
    EXPECT_THROW(calc.reset([&]() { return a() + calc(); }), std::runtime_error);

    // Verify the node is still in a consistent state
    EXPECT_EQ(calc.get(), 12); // Value should be unchanged

    // Verify dependencies are still intact by changing inputs
    a.value(20);
    EXPECT_EQ(calc.get(), 22);
    b.value(5);
    EXPECT_EQ(calc.get(), 25);

    // Additionally check the extracted scenario function behaves consistently
    auto result = run_ResetCycleDependencyRollback_scenario();
    EXPECT_EQ(result.final_calc_value, 25);
    EXPECT_EQ(result.final_a_value, 20);
    EXPECT_EQ(result.final_b_value, 5);
}

