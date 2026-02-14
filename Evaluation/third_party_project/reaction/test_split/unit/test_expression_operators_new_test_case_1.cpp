

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

#include "test_expression_operators_function_implementation_1.hpp"

TEST(ExpressionOperatorsTest, TestLogicalOperators) {
    using namespace expression_operators_impl;

    const auto result = run_logical_operators_scenario();

    EXPECT_TRUE(result.and_expr1);
    EXPECT_FALSE(result.and_expr2_initial);

    EXPECT_TRUE(result.or_expr1);
    EXPECT_FALSE(result.or_expr2_initial);

    EXPECT_TRUE(result.complex_expr);

    EXPECT_TRUE(result.and_expr2_after_update); // true && true is true
    EXPECT_TRUE(result.or_expr2_after_update);  // true || true is true
}

