

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_expression_division_function_implementation_2.hpp"

using namespace reaction;

namespace expression_division_tests {

TEST(ExpressionDivisionTest, TestFloatingPointDivision) {
    // ============ Construct Function Inputs & Call Function ============
    auto [a, b, division] =
        expression_division_impl::create_floating_point_division_expression();

    // ============ Assert to Verify Behavior ============

    EXPECT_DOUBLE_EQ(division.get(), 1.57);

    // Test with different values
    a.value(7.5);
    b.value(2.5);
    EXPECT_DOUBLE_EQ(division.get(), 3.0);
}

}  // namespace expression_division_tests

