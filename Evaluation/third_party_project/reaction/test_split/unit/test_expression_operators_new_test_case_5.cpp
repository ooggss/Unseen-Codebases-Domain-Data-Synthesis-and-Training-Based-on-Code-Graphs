

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

#include "test_expression_operators_function_implementation_5.hpp"

TEST(ExpressionOperatorsTest, TestOperatorPrecedence) {
    using namespace expression_operators_impl;

    const auto result = run_operator_precedence_scenario();

    EXPECT_TRUE(result.prec_expr1);  // 2 + (3*4) = 14 > 10 is true
    EXPECT_EQ(result.prec_expr2, 1); // (-2) + 3 = 1
    EXPECT_TRUE(result.prec_expr3);  // true || (false && true) = true
}

