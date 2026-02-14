

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

#include "test_operators_function_implementation_3.hpp"

using namespace operator_test_functions;

/**
 * @brief Test bitwise operators with integers
 */
TEST(OperatorTest, BitwiseOperators) {
    int initial = 0b1010; // 10 in binary

    auto result = run_bitwise_sequence(initial);

    EXPECT_EQ(result.after_and_equal, 0b1000);
    EXPECT_EQ(result.after_or_equal, 0b1111);
    EXPECT_EQ(result.after_xor_equal, 0b1100);
    EXPECT_EQ(result.after_shift_left_equal, 0b11000);
    EXPECT_EQ(result.after_shift_right_equal, 0b110);

    std::cout << "✅ Bitwise operators test passed" << std::endl;
}

