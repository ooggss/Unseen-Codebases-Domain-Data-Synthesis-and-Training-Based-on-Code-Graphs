

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

#include "test_expression_operators_function_implementation_3.hpp"

TEST(ExpressionOperatorsTest, TestComplexOperatorCombinations) {
    using namespace expression_operators_impl;

    const auto result = run_complex_operators_scenario();

    EXPECT_FALSE(result.complex1_initial); // (4+2) > 6 is false
    EXPECT_EQ(result.complex2_initial, -2); // -(4-2) = -2
    EXPECT_TRUE(result.complex3); // (4>2) && (6/2==3) is true
    EXPECT_TRUE(result.complex4); // 2 < 4 < 6

    EXPECT_TRUE(result.complex1_after_update);   // (8+2) > 6 is true
    EXPECT_EQ(result.complex2_after_update, -6); // -(8-2) = -6
}

