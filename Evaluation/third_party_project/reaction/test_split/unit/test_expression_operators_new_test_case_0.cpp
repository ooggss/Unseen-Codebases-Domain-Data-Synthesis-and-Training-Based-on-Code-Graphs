

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Include function implementation (normally via header)
#include "test_expression_operators_function_implementation_0.hpp"

TEST(ExpressionOperatorsTest, TestComparisonOperators) {
    using namespace expression_operators_impl;

    const auto result = run_comparison_operators_scenario();

    EXPECT_TRUE(result.eq_expr);
    EXPECT_FALSE(result.neq_expr);

    EXPECT_TRUE(result.ne_expr);
    EXPECT_FALSE(result.ne_expr2);

    EXPECT_TRUE(result.lt_expr_initial);
    EXPECT_FALSE(result.lt_expr2_initial);

    EXPECT_TRUE(result.gt_expr_initial);
    EXPECT_FALSE(result.gt_expr2_initial);

    EXPECT_TRUE(result.le_expr);
    EXPECT_TRUE(result.le_expr2);

    EXPECT_TRUE(result.ge_expr);
    EXPECT_TRUE(result.ge_expr2);

    EXPECT_FALSE(result.lt_expr_after_update); // 7 < 5 is false
    EXPECT_TRUE(result.gt_expr2_after_update); // 7 > 5 is true
}

