

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

#include "test_expression_operators_function_implementation_2.hpp"

TEST(ExpressionOperatorsTest, TestUnaryOperators) {
    using namespace expression_operators_impl;

    const auto result = run_unary_operators_scenario();

    EXPECT_EQ(result.neg_expr1_initial, -5);
    EXPECT_EQ(result.neg_expr2, 3);

    EXPECT_FALSE(result.not_expr1_initial);
    EXPECT_FALSE(result.not_expr2);

    EXPECT_EQ(result.bitnot_expr, ~10);

    EXPECT_EQ(result.neg_expr1_after_update, 10);

    EXPECT_TRUE(result.not_expr1_after_update);
}

