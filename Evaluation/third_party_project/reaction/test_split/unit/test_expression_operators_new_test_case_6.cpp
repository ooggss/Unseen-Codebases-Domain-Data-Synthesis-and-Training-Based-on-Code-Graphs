

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

#include "test_expression_operators_function_implementation_6.hpp"

TEST(ExpressionOperatorsTest, TestOperatorsInBatchOperations) {
    using namespace expression_operators_impl;

    const auto r = run_operators_batch_scenario();

    EXPECT_EQ(r.triggerCount, 1); // Should trigger only once
    EXPECT_TRUE(r.result_value);  // (20>10) && (20/10==2) is true
}

