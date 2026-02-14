

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_expression_division_function_implementation_4.hpp"

using namespace reaction;

namespace expression_division_tests {

TEST(ExpressionDivisionTest, TestDivisionWithCalculations) {
    // ============ Construct Function Inputs & Call Function ============
    auto [x, y, sum, diff, ratio] =
        expression_division_impl::create_division_with_calculations();

    (void)sum;
    (void)diff;

    // ============ Assert to Verify Behavior ============

    // Initial values x=6, y=4:
    EXPECT_DOUBLE_EQ(ratio.get(), 10.0 / 2.0); // (6+4) / (6-4) = 10/2 = 5.0

    // Test with different values
    x.value(12);
    y.value(3);
    EXPECT_DOUBLE_EQ(ratio.get(), 15.0 / 9.0); // (12+3) / (12-3) = 15/9
}

}  // namespace expression_division_tests

