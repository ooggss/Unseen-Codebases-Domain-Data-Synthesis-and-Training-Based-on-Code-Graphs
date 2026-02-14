

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

#include "test_expression_operators_function_implementation_4.hpp"

TEST(ExpressionOperatorsTest, TestOperatorsWithDifferentTypes) {
    using namespace expression_operators_impl;

    const auto result = run_operators_different_types_scenario();

    EXPECT_TRUE(result.mixed_expr1_initial); // 5 > 3.14 is true
    EXPECT_TRUE(result.mixed_expr2);         // true && (5>0) is true
    EXPECT_TRUE(result.mixed_expr3_initial); // 2.5 > 2.0 is true

    EXPECT_FALSE(result.mixed_expr1_after_update); // 1 > 3.14 is false
    EXPECT_FALSE(result.mixed_expr3_after_update); // 0.5 > 2.0 is false
}

