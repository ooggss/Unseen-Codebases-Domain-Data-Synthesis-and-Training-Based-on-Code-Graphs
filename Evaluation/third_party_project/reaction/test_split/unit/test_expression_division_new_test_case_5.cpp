

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_expression_division_function_implementation_5.hpp"

using namespace reaction;

namespace expression_division_tests {

TEST(ExpressionDivisionTest, TestDivisionEdgeCases) {
    // ============ Construct Function Inputs & Call Function ============
    auto [a, b, zeroDiv] =
        expression_division_impl::create_division_edge_case_expression();

    // ============ Assert to Verify Behavior ============

    // Zero divided by number using expression templates
    EXPECT_DOUBLE_EQ(zeroDiv.get(), 0.0);

    // Test very small integer division
    a.value(1);
    b.value(1000);
    EXPECT_DOUBLE_EQ(zeroDiv.get(), 0.001);

    // Test negative numbers
    a.value(-10);
    b.value(3);
    EXPECT_DOUBLE_EQ(zeroDiv.get(), -10.0 / 3.0);

    a.value(10);
    b.value(-4);
    EXPECT_DOUBLE_EQ(zeroDiv.get(), -2.5);
}

}  // namespace expression_division_tests

