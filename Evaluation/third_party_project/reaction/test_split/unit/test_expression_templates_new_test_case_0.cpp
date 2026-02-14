

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Include function definition (in an actual project, prefer including a header)
#include "test_expression_templates_function_implementation_0.hpp"

namespace expression_templates_test {

// Test expression templates with reactive values
TEST(ExpressionTemplatesTest, TestExpr) {
    // ============ Call Function to Get Return Value ============
    const auto [ds_val, expr_val] = compute_expr_result();

    // ============ Assert to Verify Return Value ============
    EXPECT_EQ(ds_val, 4);
    ASSERT_FLOAT_EQ(expr_val, -3.86);
}

}  // namespace expression_templates_test

