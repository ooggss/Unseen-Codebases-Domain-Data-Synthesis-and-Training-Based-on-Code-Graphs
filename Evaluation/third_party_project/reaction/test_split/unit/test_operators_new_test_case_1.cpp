

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

#include "test_operators_function_implementation_1.hpp"

using namespace operator_test_functions;

/**
 * @brief Test compound assignment operators (+=, -=, *=, /=, %=)
 */
TEST(OperatorTest, CompoundAssignmentOperators) {
    int initial = 10;

    auto result = run_compound_assignment_sequence(initial);

    EXPECT_EQ(result.after_plus_equal, 15);
    EXPECT_EQ(result.after_minus_equal, 12);
    EXPECT_EQ(result.after_mul_equal, 24);
    EXPECT_EQ(result.after_div_equal, 6);
    EXPECT_EQ(result.after_mod_equal, 2);

    std::cout << "✅ Compound assignment operators test passed" << std::endl;
}

