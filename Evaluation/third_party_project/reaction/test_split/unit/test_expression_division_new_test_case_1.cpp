

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_expression_division_function_implementation_1.hpp"

using namespace reaction;

namespace expression_division_tests {

TEST(ExpressionDivisionTest, TestMixedTypeDivision) {
    // ============ Construct Function Inputs & Call Function ============
    auto [intVar, floatVar, intByFloat, floatByInt] =
        expression_division_impl::create_mixed_type_division_expressions();

    // ============ Assert to Verify Behavior ============

    // Integer divided by float - mixed type expressions work naturally
    EXPECT_DOUBLE_EQ(intByFloat.get(), 2.5);

    // Float divided by integer - mixed type expressions work naturally
    EXPECT_DOUBLE_EQ(floatByInt.get(), 0.4);

    // Update values
    intVar.value(10);
    floatVar.value(4.0);
    EXPECT_DOUBLE_EQ(intByFloat.get(), 2.5);
    EXPECT_DOUBLE_EQ(floatByInt.get(), 0.4);
}

}  // namespace expression_division_tests

