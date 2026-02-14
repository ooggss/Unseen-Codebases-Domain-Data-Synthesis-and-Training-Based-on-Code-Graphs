

#include <gtest/gtest.h>

// Include function implementation
#include "test_sbo_function_implementation_8.hpp"

class SBOTest : public ::testing::Test {};

TEST_F(SBOTest, ReactiveVariablesWithSBO) {
    auto r = run_reactive_variables_with_sbo();
    EXPECT_TRUE(r.placeholder);
}

