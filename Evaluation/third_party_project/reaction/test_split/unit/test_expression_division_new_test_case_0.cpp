

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_expression_division_function_implementation_0.hpp"

using namespace reaction;

namespace expression_division_tests {

TEST(ExpressionDivisionTest, TestIntegerDivisionPromotion) {
    // ============ Construct Function Inputs ============
    // No external inputs required; construction is encapsulated in the helper function

    // ============ Call Function to Get Objects ============
    auto [a, b, division] =
        expression_division_impl::create_integer_division_promotion_expression();

    // ============ Assert to Verify Behavior ============

    // Test basic integer division that should return floating-point result
    EXPECT_DOUBLE_EQ(division.get(), 0.5);
    EXPECT_NE(division.get(), 0); // Ensure it's not integer division

    // Test with larger integers
    a.value(7);
    b.value(3);
    EXPECT_DOUBLE_EQ(division.get(), 7.0 / 3.0);

    // Test division by larger number
    a.value(1);
    b.value(10);
    EXPECT_DOUBLE_EQ(division.get(), 0.1);
}

}  // namespace expression_division_tests

