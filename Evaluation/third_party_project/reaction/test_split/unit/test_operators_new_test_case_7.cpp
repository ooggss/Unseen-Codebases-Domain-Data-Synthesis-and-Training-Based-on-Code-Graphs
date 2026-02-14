

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

#include "test_operators_function_implementation_7.hpp"

using namespace operator_test_functions;

/**
 * @brief Test operators with different numeric types
 */
TEST(OperatorTest, MixedNumericTypes) {
    int int_initial = 10;
    double double_initial = 3.5;

    auto result = run_mixed_numeric_types_sequence(int_initial, double_initial);

    // Behavior of int += double may truncate; original test does not assert on it.
    // We keep that behavior unasserted.
    EXPECT_DOUBLE_EQ(result.double_after_plus_equal_int, 4.5);
    EXPECT_DOUBLE_EQ(result.double_after_mul_equal_int, 9.0);

    std::cout << "✅ Mixed numeric types test passed" << std::endl;
}

