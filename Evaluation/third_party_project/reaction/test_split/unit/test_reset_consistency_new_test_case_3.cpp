

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <gtest/gtest.h>

// Include function implementation (normally via header)
#include "test_reset_consistency_function_implementation_3.hpp"

TEST(ResetConsistencyTest, ResetWithExceptionInEvaluationRollback) {
    auto a = reaction::var(1);

    // Create a valid calculation
    auto calc = reaction::calc([](int x) { return x * 2; }, a);
    EXPECT_EQ(calc.get(), 2);

    // Attempt to reset with a function that throws during evaluation
    EXPECT_THROW(
        calc.reset([&]() {
            if (a() == 1) {
                throw std::runtime_error("Test exception during evaluation");
            }
            return a() * 3;
        }),
        std::runtime_error);

    // Verify the node is still in a consistent state
    EXPECT_EQ(calc.get(), 2);

    // Verify dependencies are still intact
    a.value(5);
    EXPECT_EQ(calc.get(), 10);

    auto result = run_ResetWithExceptionInEvaluationRollback_scenario();
    EXPECT_EQ(result.final_calc_value, 10);
    EXPECT_EQ(result.final_a_value, 5);
}

