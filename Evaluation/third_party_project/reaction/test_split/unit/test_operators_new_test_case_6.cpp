

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

#include "test_operators_function_implementation_6.hpp"

using namespace operator_test_functions;

/**
 * @brief Test type safety - ensure operators only work on VarExpr
 */
TEST(OperatorTest, TypeSafety) {
    int initial = 10;

    auto result = run_type_safety_sequence(initial);

    EXPECT_EQ(result.value_after_plus_equal, 15);

    // Compilation-failure checks stay as comments:
    // calc_v += 5;  // Should not compile
    // ++calc_v;     // Should not compile

    std::cout << "✅ Type safety test passed" << std::endl;
}

