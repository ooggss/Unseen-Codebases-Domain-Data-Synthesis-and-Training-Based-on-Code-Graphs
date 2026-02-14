

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

#include "test_operators_function_implementation_8.hpp"

using namespace operator_test_functions;

/**
 * @brief Test edge cases and boundary conditions
 */
TEST(OperatorTest, EdgeCases) {
    int zero_initial = 0;
    int neg_initial = -5;
    int test_initial = 100;

    auto result = run_edge_cases_sequence(zero_initial, neg_initial, test_initial);

    EXPECT_EQ(result.zero_after_pre_increment, 1);
    EXPECT_EQ(result.zero_after_pre_decrement, 0);

    EXPECT_EQ(result.neg_after_plus_equal, 5);
    EXPECT_EQ(result.neg_after_mul_equal, -5);

    EXPECT_EQ(result.post_inc_old1, 100);
    EXPECT_EQ(result.post_dec_old2, 101);
    EXPECT_EQ(result.final_v_test_value, 100);

    std::cout << "✅ Edge cases test passed" << std::endl;
}

