

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

#include "test_operators_function_implementation_4.hpp"

using namespace operator_test_functions;

/**
 * @brief Test operators with string type
 */
TEST(OperatorTest, StringOperators) {
    std::string initial = "Hello";

    auto result = run_string_sequence(initial);

    EXPECT_EQ(result.after_first_plus_equal, "Hello World");
    EXPECT_EQ(result.after_second_plus_equal, "Hello World!");

    std::cout << "✅ String operators test passed" << std::endl;
}

