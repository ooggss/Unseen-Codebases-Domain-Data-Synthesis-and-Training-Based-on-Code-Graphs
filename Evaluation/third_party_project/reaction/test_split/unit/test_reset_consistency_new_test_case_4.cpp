

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <gtest/gtest.h>

// Include function implementation (normally via header)
#include "test_reset_consistency_function_implementation_4.hpp"

TEST(ResetConsistencyTest, SuccessfulResetAfterFailedReset) {
    auto a = reaction::var(1);
    auto b = reaction::var(2);

    // Create a valid calculation
    auto calc = reaction::calc([](int x, int y) { return x + y; }, a, b);
    EXPECT_EQ(calc.get(), 3);

    // Attempt a failed reset
    EXPECT_THROW(calc.reset([&]() { return calc() + a(); }), std::runtime_error);

    // Verify still consistent
    EXPECT_EQ(calc.get(), 3);

    // Now do a successful reset
    calc.reset([&]() { return a() * b(); });
    EXPECT_EQ(calc.get(), 2);

    // Verify new calculation works
    a.value(3);
    EXPECT_EQ(calc.get(), 6);
    b.value(4);
    EXPECT_EQ(calc.get(), 12);

    auto result = run_SuccessfulResetAfterFailedReset_scenario();
    EXPECT_EQ(result.final_calc_value, 12);
    EXPECT_EQ(result.final_a_value, 3);
    EXPECT_EQ(result.final_b_value, 4);
}

