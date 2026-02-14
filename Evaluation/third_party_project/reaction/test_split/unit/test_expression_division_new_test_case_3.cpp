

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_expression_division_function_implementation_3.hpp"

using namespace reaction;

namespace expression_division_tests {

TEST(ExpressionDivisionTest, TestComplexExpressionChains) {
    // ============ Construct Function Inputs & Call Function ============
    auto [a, b, c, complexExpr1, complexExpr2, complexExpr3] =
        expression_division_impl::create_complex_expression_chain_divisions();

    // ============ Assert to Verify Behavior ============

    // Initial values: a=10, b=3, c=2
    // Test (a / b) + c - using expression templates
    EXPECT_DOUBLE_EQ(complexExpr1.get(), 10.0 / 3.0 + 2.0);

    // Test a / (b + c) - using expression templates
    EXPECT_DOUBLE_EQ(complexExpr2.get(), 10.0 / 5.0);

    // Test (a / b) / c - using expression templates
    EXPECT_DOUBLE_EQ(complexExpr3.get(), (10.0 / 3.0) / 2.0);

    // Update values and verify recalculation
    a.value(15);
    b.value(4);
    c.value(3);

    EXPECT_DOUBLE_EQ(complexExpr1.get(), 15.0 / 4.0 + 3.0);
    EXPECT_DOUBLE_EQ(complexExpr2.get(), 15.0 / 7.0);
    EXPECT_DOUBLE_EQ(complexExpr3.get(), (15.0 / 4.0) / 3.0);
}

}  // namespace expression_division_tests

