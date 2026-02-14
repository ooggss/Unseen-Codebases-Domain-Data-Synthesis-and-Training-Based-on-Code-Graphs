

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

#include "test_operators_function_implementation_2.hpp"

using namespace operator_test_functions;

/**
 * @brief Test operators with floating point numbers
 */
TEST(OperatorTest, FloatingPointOperators) {
    double initial = 3.14;

    auto result = run_floating_point_sequence(initial);

    EXPECT_DOUBLE_EQ(result.after_plus_equal, 5.0);
    EXPECT_DOUBLE_EQ(result.after_minus_equal, 4.0);
    EXPECT_DOUBLE_EQ(result.after_mul_equal, 2.0);
    EXPECT_DOUBLE_EQ(result.after_div_equal, 1.0);
    EXPECT_DOUBLE_EQ(result.after_pre_increment, 2.0);
    EXPECT_DOUBLE_EQ(result.after_post_increment_value, 3.0);
    EXPECT_DOUBLE_EQ(result.post_increment_old_value, 2.0);

    std::cout << "✅ Floating point operators test passed" << std::endl;
}

