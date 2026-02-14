

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Include function definitions (in a real project, via a header)
#include "test_operators_function_implementation_0.hpp"

using namespace operator_test_functions;

/**
 * @brief Test increment operators (++ and --)
 */
TEST(OperatorTest, IncrementDecrementOperators) {
    // ============ Construct Function Inputs ============
    int initial = 5;

    // ============ Call Function ============
    auto result = run_increment_decrement_sequence(initial);

    // ============ Assertions ============
    EXPECT_EQ(result.initial_value, 5);
    EXPECT_EQ(result.after_pre_increment, 6);
    EXPECT_EQ(result.value_after_post_increment, 7);
    EXPECT_EQ(result.post_increment_old_value, 6);
    EXPECT_EQ(result.after_pre_decrement, 6);
    EXPECT_EQ(result.value_after_post_decrement, 5);
    EXPECT_EQ(result.post_decrement_old_value, 6);

    std::cout << "✅ Increment/Decrement operators test passed" << std::endl;
}

